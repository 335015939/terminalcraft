#include "defines.h"
#include "funcs.h"
#include "header.h"

COORDS *entityxy=NULL;
void ai_none(){
    
};
void entities(){
    int i;
    void (*script[])(COORDS c)={ai_none};
    for(i=0;i<MAX_ENTITY;i++){
        (*script[getmaptile(entityxy[i].x,entityxy[i].y).e.id])(entityxy[i]);
    };
};