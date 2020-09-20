#include "header.h"
#include <string.h>
#include <curses.h>
#define ditem(x) dtile(ITEMS[(x).id].t)
ITEM (*cheststorage)[10][10]=NULL;
ITEM getchestitem(COORDS c){
    if(c.x<10){
        return player.i[c.x][c.y];
    }else{
        return (*cheststorage)[c.x-10][c.y];
    };
}
void drawchestitem(COORDS c,int attr){
    ITEM item;
    item=getchestitem(c);
    attr_set(attr | ITEMS[(item).id].t.a,ITEMS[item.id].t.cp,NULL);
    addch(ITEMS[(item).id].t.c);
};
void putchestitem(COORDS c,ITEM i){
    if(c.x<10){
        player.i[c.x][c.y]=i;
    }else{
        (*cheststorage)[c.x-10][c.y]=i;
    };
};
void drawchest(COORDS s,COORDS c,char f){
    int i,j;
    ITEM item;
    clear();
    attr_set(A_NORMAL,0,NULL);
    item=getchestitem(c);
    mvprintw(13,0,"%s(%d)",ITEMS[item.id].name,item.num);
    move(0,0);
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
        attr_set(A_NORMAL,0,NULL);
        addch('|');
        for(;i<20;i++){
            drawchestitem((COORDS){i,j},A_NORMAL);
        };
        attr_set(A_NORMAL,0,NULL);
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
    };
};
void chestitemswap(COORDS a,COORDS b){
    ITEM item1;
    ITEM item2;
    item1=getchestitem(a);
    item2=getchestitem(b);
    putchestitem(b,item1);
    putchestitem(a,item2);
};
void chest(int x,int y){
    char isselected=0;
    static COORDS selected={};
    COORDS oldselected={};
    cheststorage=&getmaptile(x,y).storage;
    for(;;){
        drawchest(oldselected,selected,isselected);
        switch(getch()){
            case 'w':
            case 'W':
            case KEY_UP:
                selected.y-=(selected.y>0);
                break;
            case 's':
            case 'S':
            case KEY_DOWN:
                selected.y+=(selected.y<9);
                break;
            case 'd':
            case 'D':
            case KEY_RIGHT:
                selected.x+=(selected.x<19);
                break;
            case 'a':
            case 'A':
            case KEY_LEFT:
                selected.x-=(selected.x>0);
                break;
            case 'j':
            case 'J':
            case '\n':
                if(isselected){
                    chestitemswap(selected,oldselected);
                    isselected=0;
                }else{
                    oldselected=selected;
                    isselected=1;
                };
                break;
            case 'q':
            case 'Q':
                clear();
                return;
        };
    };
    getch();
};