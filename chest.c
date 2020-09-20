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
void drawchest(COORDS s,COORDS c,char f){
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
    move(c.y+2,c.x+(c.x>=10)+1);
    drawchestitem(c,A_REVERSE);
    if(f){
        move(s.y+2,s.x+(s.x>=10)+1);
        drawchestitem(s,A_REVERSE);
    }
};
void chestitemswap(COORDS a,COORDS b){
    ITEM (*item1);
    ITEM (*item2);
    ITEM (*item)=malloc_throw(sizeof(ITEM));
    if(a.x>10){
        item1=cheststorage[a.x-10][a.y];
    }else{
        item1=&(player.i[a.x][a.y]);
    };
    if(b.x>=10){
        item2=cheststorage[b.x-10][b.y];
    }else{
        item2=&(player.i[b.x][b.y]);
    };
    *item=*item2;
    *item2=*item1;
    *item1=*item;
    free(item);
    clear();
    printw("%s %s",ITEMS[(*item1).id].name,ITEMS[(*item2).id].name);
    getch();
};
void chest(int x,int y){
    int selected=1;
    cheststorage=&getmaptile(x,y).storage;
    chestitemswap((COORDS){0,0},(COORDS){10,0});
    drawchest((COORDS){0,0},(COORDS){0,0},selected);
    getch();
};