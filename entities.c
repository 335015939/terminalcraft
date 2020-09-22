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
    }while(onscreen(x,y) || !nearplayer(x,y) ||(
        (getmaptiledata(x, y).type==TILE_TYPE_BACKGROUND_WALL)||
        (getmaptiledata(x, y).type==TILE_TYPE_FURNACE)||
        (getmaptiledata(x, y).type==TILE_TYPE_WORKBENCH)||
        (getmaptiledata(x, y).type==TILE_TYPE_CHEST)
        ||(!getmaptiledata(x, y).passable)));
    return (COORDS){x,y};
};
void entitymove(COORDS *old,COORDS c){
    if(!isinmap(c.x, c.y))return;
    if((getmaptiledata(c.x, c.y).type==TILE_TYPE_DOOR)||
    (!getmaptiledata(c.x, c.y).passable)||(getmaptile(c.x, c.y).e.id))return;
    *old=c;
};
void entityfall(COORDS *c){
    if(isinmap(c->x, c->y+1)){
        if((getmaptiledata(c->x, c->y).fallthrough&&getmaptiledata(c->x, c->y+1).fallthrough&&
        !getmaptile(c->x, c->y+1).e.id)){
            entitymove(c,(COORDS){c->x,c->y+1});
        };
    };
};
COORDS spawnsnake(){
    COORDS c;
    c=randc();
    if (c.y>=(MAP_H-1)) c.y--;
    if((getmaptiledata(c.x, c.y+1).fallthrough&&getmaptiledata(c.x, c.y).fallthrough)||(rand()%3)) return c;
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
    COORDS cstart,c=entityxy[x];
    cstart=c;
    ENTITY e=getmaptile(c.x, c.y).e;
    getmaptile(c.x, c.y).e=entity_none;
    if(e.hp<=0) return;
    char restart=1;
    int movex=(c.x<player.c.x)-(c.x>player.c.x);
    int movey=(c.y<player.c.y)-(c.y>player.c.y);
    if((c.x==player.c.x && (c.y<=(player.c.y+1)&&c.y>=(player.c.y-1))) || 
    (c.y==player.c.y && (c.x<=(player.c.x+1)&&c.x>=(player.c.x-1)))){
        GOT_HIT_MSG="You were hit by snake";
        player.hp--;
        entityfall(&c);
        goto lbl_end;
    };
    lbl_start:
    if(rand()%2){
        entitymove(&c,(COORDS){c.x+movex,c.y});
        entityfall(&c);
        goto lbl_end;
    }else{
        entitymove(&c,(COORDS){c.x,c.y+movey});
        entityfall(&c);
        goto lbl_end;
    };
    lbl_end:
    if(cstart.x==c.x && cstart.y==c.y && restart){
        restart=0;
        if(movey||movex){
            movey=movey*-1;
            movex=movex*-1;
        }else{
            movex=movey=(2*(rand()%2))-1;
        };
        goto lbl_start;
    };
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