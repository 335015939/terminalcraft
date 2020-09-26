#include "defines.h"
#include "enum.h"
#include "funcs.h"
#include "header.h"
#include "vars.h"
#define entity_none ((ENTITY){})
COORDS *entityxy=NULL;
void entityattack(int dmg,char *entitymsg){
    dmg-=getdef();
    if(dmg<0)dmg=0;
    player.hp-=dmg;
    GOT_HIT_MSG=entitymsg;
};
char entitydie(int x,int y,ENTITY e){
    if(e.hp<=0){
        dropitems(ENTITIES[e.id].d,xytocoords(x, y),0);
        player.exp+=ENTITIES[e.id].xp;
        return 1;
    };
    return 0;
};
COORDS randc(){
    int x,y;
    lbl_redo:
    do{
        do{
            x =rand()%MAP_W;
            y=rand()%MAP_H;
        }while(!isinmap(x, y));
        if(isinmap(x, y+1)){
            if(getmaptiledata(x, y+1).type==TILE_TYPE_CHEST){
                goto lbl_redo;
            };
        };
    }while(onscreen(x,y) || !nearplayer(x,y) ||(
        (getmaptiledata(x, y).type==TILE_TYPE_BACKGROUND_WALL)||
        (getmaptiledata(x, y).type==TILE_TYPE_FURNACE)||
        (getmaptiledata(x, y).type==TILE_TYPE_WORKBENCH)||
        (getmaptiledata(x, y).type==TILE_TYPE_CHEST)||
        (getmaptiledata(x, y).type==TILE_TYPE_LADDER)));
    return (COORDS){x,y};
};
char entitymove(COORDS *old,COORDS c){
    if(!isinmap(c.x, c.y))return 0;
    if((getmaptiledata(c.x, c.y).type==TILE_TYPE_DOOR)||
    (!getmaptiledata(c.x, c.y).passable)||(getmaptile(c.x, c.y).e.id))return 0;
    *old=c;
    return 1;
};
void entityfall(COORDS *c){
    if(isinmap(c->x, c->y+1)){
        if((getmaptiledata(c->x, c->y).fallthrough&&getmaptiledata(c->x, c->y+1).fallthrough&&
        !getmaptile(c->x, c->y+1).e.id)){
            entitymove(c,(COORDS){c->x,c->y+1});
        };
    };
};
COORDS spawnbat(){
    COORDS c=randc();
    if(!getmaptiledata(c.x, c.y).passable) return c;
    if(!isnight()&&c.y<=(MAP_H/4)) return c;
    if(!isnight()){
        if(ENTITIES_IN_WORLD>10) return c;
    };
    if(rand()%30) return c;
    getmaptile(c.x, c.y).e=(ENTITY){ENTITY_BAT,4+(rand()%2)};
    return c;
};
COORDS spawnzombie(){
    COORDS c=randc();
    if(!getmaptiledata(c.x, c.y).passable) return c;
    if(!isnight()) return c;
    if(c.y<MAP_H-1){
        if(getmaptiledata(c.x, c.y).fallthrough&&
        getmaptiledata(c.x, c.y+1).fallthrough) return c;
    };
    getmaptile(c.x, c.y).e=(ENTITY){ENTITY_ZOMBIE,28+(rand()%4)};
    return c;
};
void ai_zombie(int x){
    COORDS cstart,c=entityxy[x];
    cstart=c;
    ENTITY e=getmaptile(c.x, c.y).e;
    getmaptile(c.x, c.y).e=entity_none;
    if(entitydie(c.x,c.y,e) || !nearplayer(c.x,c.y)) {
        return;
    };
    char restart=1;
    int movex=(c.x<player.c.x)-(c.x>player.c.x);
    int movey=(c.y<player.c.y)-(c.y>player.c.y);
    if((c.x==player.c.x && (c.y<=(player.c.y+1)&&c.y>=(player.c.y-1))) || 
    (c.y==player.c.y && (c.x<=(player.c.x+1)&&c.x>=(player.c.x-1)))){
        entityattack(12+(rand()%2),"You got hit by zombie");
        entityfall(&c);
        goto lbl_end;
    };
    if(isnight()){
        lbl_start:
        if(rand()%2){
            entitymove(&c,(COORDS){c.x+movex,c.y});
            entityfall(&c);
            goto lbl_end;
        }else{
            entityfall(&c);
            entitymove(&c,(COORDS){c.x,c.y+movey});
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
    }else{
        if(!entitymove(&c,(COORDS){c.x-movex,c.y-movey})){
            if(rand()%2){
                entitymove(&c,(COORDS){c.x-movex,c.y-movey});
            }else{
                entitymove(&c,(COORDS){c.x-movex,c.y-movey});
            };  
        };
        entityfall(&c);
        if(!onscreen(c.x, c.y)) return;
    }
    getmaptile(c.x, c.y).e=e;
    entityxy[x]=c;
};
void ai_bat(int x){
    COORDS c=entityxy[x];
    ENTITY e=getmaptile(c.x, c.y).e;
    getmaptile(c.x, c.y).e=entity_none;
    if(entitydie(c.x,c.y,e) || !nearplayer(c.x,c.y)) {
        return;
    };
    int movex=(c.x<player.c.x)-(c.x>player.c.x);
    int movey=(c.y<player.c.y)-(c.y>player.c.y);
    if((c.x==player.c.x && (c.y<=(player.c.y+1)&&c.y>=(player.c.y-1))) || 
    (c.y==player.c.y && (c.x<=(player.c.x+1)&&c.x>=(player.c.x-1)))){
        entityattack(4+(rand()%2),"You got hit by bat");
        entityfall(&c);
        goto lbl_end;
    };
    if(isnight()||c.y>(MAP_H/4)){
        if(!entitymove(&c,(COORDS){c.x+movex,c.y+movey})){
            if(movex&&movey){
                if(rand()%2){
                    entitymove(&c,(COORDS){c.x,c.y+movey});
                }else{
                    entitymove(&c,(COORDS){c.x+movex,c.y});
                };
            }else{
                entitymove(&c,(COORDS){c.x-movex,c.y-movey});
            };
        };
    }else{
        if(!entitymove(&c,(COORDS){c.x-movex,c.y-movey})){
            if(rand()%2){
                entitymove(&c,(COORDS){c.x-movex,c.y-movey});
            }else{
                entitymove(&c,(COORDS){c.x-movex,c.y-movey});
            };
        };
        if(!onscreen(c.x, c.y)) return;
    };
    lbl_end:
    getmaptile(c.x, c.y).e=e;
    entityxy[x]=c;
};
COORDS spawnsnake(){
    COORDS c;
    c=randc();
    if (c.y>=(MAP_H-1)) c.y--;
    if((getmaptiledata(c.x, c.y+1).fallthrough&&getmaptiledata(c.x, c.y).fallthrough)) return c;
    if(!getmaptiledata(c.x, c.y).passable) return c;
    if ((ENTITIES_IN_WORLD > 8) &&
        (!(isnight())))
      return c;
    if(getmaptile(c.x, c.y).e.id) return c;
    getmaptile(c.x, c.y).e=(ENTITY){ENTITY_SNAKE,4};
    return c;
};
void ai_none(int x){
    if(ENTITIES_IN_WORLD<MAX_ENTITY){
        COORDS (*spawn[3])()={spawnsnake,spawnbat,spawnzombie};
        COORDS c;//=entityxy[x];
        c=(*spawn[rand()%3])();
        entityxy[x]=c;
    };
};
void ai_snake(int x){
    COORDS cstart,c=entityxy[x];
    cstart=c;
    ENTITY e=getmaptile(c.x, c.y).e;
    getmaptile(c.x, c.y).e=entity_none;
    if(entitydie(c.x,c.y,e)|| !nearplayer(c.x,c.y)) {
        return;
    };
    char restart=1;
    int movex=(c.x<player.c.x)-(c.x>player.c.x);
    int movey=(c.y<player.c.y)-(c.y>player.c.y);
    if((c.x==player.c.x && (c.y<=(player.c.y+1)&&c.y>=(player.c.y-1))) || 
    (c.y==player.c.y && (c.x<=(player.c.x+1)&&c.x>=(player.c.x-1)))){
        entityattack(2,"You got hit by snake");
        entityfall(&c);
        goto lbl_end;
    };
    lbl_start:
    if(rand()%2){
        entitymove(&c,(COORDS){c.x+movex,c.y});
        entityfall(&c);
        goto lbl_end;
    }else{
        entityfall(&c);
        entitymove(&c,(COORDS){c.x,c.y+movey});
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
    getmaptile(c.x, c.y).e=e;
    entityxy[x]=c;
};
void entities(){
    int i;
    void (*script[])(int x)={ai_none,ai_snake,ai_bat,ai_zombie};
    ENTITIES_IN_WORLD=0;
    for(i=0;i<MAX_ENTITY;i++){
        (*script[getmaptile(entityxy[i].x,entityxy[i].y).e.id])(i);
        if(getmaptile(entityxy[i].x,entityxy[i].y).e.id){
            ENTITIES_IN_WORLD++;
        };
    };
};