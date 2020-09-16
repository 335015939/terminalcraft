#include "header.h"

void *malloc_throw(size_t size){
    void *p=malloc(size);
    if (!p){
        clear();
        printw("Error:not enough memory");
        getch();
        exit(ERR_OUT_OF_MEM);
    };
    return p;
};
void moveplayer(int x,int y){
    if(isinmap(x+player.c.x,y+player.c.y) && (x || y)){
        if(getmaptiledata(x+player.c.x,y+player.c.y).passable){
            player.c.x+=x;
            player.c.y+=y;
            TICK++;
        };
    };
};