#include "defines.h"
#include "funcs.h"
#include "header.h"
#define entity_none ((ENTITY){})
COORDS *entityxy=NULL;
void ai_none(int x){
    invadditem((ITEM){ITEM_DIRT,1});
    COORDS c=entityxy[x];
    do{
        c.x=rand()%MAP_W;
        c.y=rand()%MAP_W;
    }while(!isinmap(c.x, c.y));
    getmaptile(c.x, c.y).e.id=1;
    entityxy[x]=c;
};
void ai_snake(int x){
    COORDS c=entityxy[x];
    ENTITY e=getmaptile(c.x, c.y).e;
    getmaptile(c.x, c.y).e=entity_none;
    if(rand()%2){
        c.x+=(c.x<player.c.x)-(c.x>player.c.x);
    }else{
        c.y+=(c.y<player.c.y)-(c.y>player.c.y);
    };
    getmaptile(c.x, c.y).e=e;
    entityxy[x]=c;
};
void entities(){
    int i;
    void (*script[])(int x)={ai_none,ai_snake};
    for(i=0;i<MAX_ENTITY;i++){
        (*script[getmaptile(entityxy[i].x,entityxy[i].y).e.id])(i);
    };
};