#include "defines.h"
#include "funcs.h"
#include "header.h"

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
    entityxy[x]=c;
};
void entities(){
    int i;
    void (*script[])(int x)={ai_none,ai_snake};
    for(i=0;i<MAX_ENTITY;i++){
        (*script[getmaptile(entityxy[i].x,entityxy[i].y).e.id])(i);
    };
};