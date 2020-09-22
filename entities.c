#include "defines.h"
#include "enum.h"
#include "funcs.h"
#include "header.h"
#include "vars.h"
#define entity_none ((ENTITY){})
COORDS *entityxy=NULL;
COORDS randc(){
    int x,y;
    do{
        do{
            x =rand()%MAP_W;
            y=rand()%MAP_H;
        }while(!isinmap(x, y));
    }while(onscreen(x,y) && !nearplayer(x,y));
    return (COORDS){x,y};
};
COORDS spawnsnake(){
    COORDS c;
    do{
        do{
            c=randc();
            if (c.y>=(MAP_H-1)) c.y--;
        }while((getmaptiledata(c.x, c.y).type==TILE_TYPE_BACKGROUND_WALL)||(!getmaptiledata(c.x, c.y).passable));
    }while(getmaptiledata(c.x, c.y+1).fallthrough&&getmaptiledata(c.x, c.y).fallthrough);
    getmaptile(c.x, c.y).e=(ENTITY){ENTITY_SNAKE,2};
    return c;
};
void ai_none(int x){
    COORDS (*spawn[1])()={spawnsnake};
    COORDS c=entityxy[x];
    c=(*spawn[rand()%1])();
    entityxy[x]=c;
};
void ai_snake(int x){
    COORDS c=entityxy[x];
    ENTITY e=getmaptile(c.x, c.y).e;
    getmaptile(c.x, c.y).e=entity_none;
    if(e.hp<=0) return;
    if(isinmap(c.x, c.y+1)){
        if(getmaptiledata(c.x, c.y).fallthrough&&getmaptiledata(c.x, c.y+1).fallthrough&&!getmaptile(c.x, c.y+1).e.id){
            c.y++;
        };
    };
    int movex=(c.x<player.c.x)-(c.x>player.c.x);
    int movey=(c.y<player.c.y)-(c.y>player.c.y);
    if((c.x==player.c.x && (c.y<=(player.c.y+1)&&c.y>=(player.c.y-1))) || 
    (c.y==player.c.y && (c.x<=(player.c.x+1)&&c.x>=(player.c.x-1)))){
        GOT_HIT_MSG="You were hit by snake";
        player.hp--;
        goto lbl_end;
    };
    if(rand()%2){
        lbl_movex:
        if(isinmap(movex+c.x,c.y)){
            if((getmaptiledata(c.x+movex, c.y).type!=TILE_TYPE_DOOR)&&
            getmaptiledata(c.x+movex, c.y).passable&&!getmaptile(c.x+movex, c.y).e.id){
                c.x+=movex;
                goto lbl_end;
            };
        };
    }else{
        lbl_movey:
        if(isinmap(c.x,movey+c.y)){
            if((getmaptiledata(c.x+movex, c.y).type!=TILE_TYPE_DOOR)&&
            getmaptiledata(c.x, c.y+movey).passable&&!getmaptile(c.x, c.y+movey).e.id){
                c.y+=movey;
                goto lbl_end;
            };
        };
    };
    lbl_end:
    if (nearplayer(c.x,c.y)) getmaptile(c.x, c.y).e=e;
    entityxy[x]=c;
};
void entities(){
    int i;
    void (*script[])(int x)={ai_none,ai_snake};
    for(i=0;i<MAX_ENTITY;i++){
        (*script[getmaptile(entityxy[i].x,entityxy[i].y).e.id])(i);
    };
};