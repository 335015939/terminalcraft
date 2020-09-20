#include "header.h"
#define ditem(x) dtile(ITEMS[(x).id].t)
ITEM (*cheststorage)[10][10]=NULL;
void drawchestitem(COORDS c,int attr){
    ITEM item;
    if(c.x<10){
        item=player.i[c.x][c.y];
    }else{
        item=(*cheststorage)[c.x-10][c.y-10];
    };
    attr_set(attr | ITEMS[(item).id].t.a,ITEMS[item.id].t.cp,NULL);
    addch(ITEMS[(item).id].t.c);
};
void drawchest(COORDS s,COORDS c){
    int i,j;
    clear();
    addstr("Inventory   Chest\n");
    for(i=0;i<23;i++){
        addch('=');
    };
    addch('\n'); 
    for(j=0;j<10;j++){
        addch('|');
        for(i=0;i<10;i++){
            drawchestitem((COORDS){i,j},A_NORMAL);
        };
        addch('|');
        for(;i<20;i++){
            drawchestitem((COORDS){i,j},A_NORMAL);
        };
        addstr("|\n");
    };
    for(i=0;i<23;i++){
        addch('=');
    };
};
void chestitemswap(COORDS a,COORDS b){

};
void chest(int x,int y){
    cheststorage=&getmaptile(x,y).storage;
    drawchest((COORDS){0,0},(COORDS){0,0});
    getch();
};