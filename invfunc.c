#include "header.h"
#include <curses.h>
void drawitem(ITEMDATA i){
    dtile(i.t);
};
void drawinv(COORDS c){
    int i,j;
    clear();
    attr_set(A_BOLD,0,NULL);
    addstr("Inventory\n");
    for(i=0;i<12;i++){
        addch('-');
    };
    addch('\n');
    for(j=0;j<10;j++){
        addch('|');
        for(i=0;i<10;i++){
            drawitem(ITEMS[player.i[i][j].id]);
        };
        attr_set(A_BOLD,0,NULL);
        addstr("|\n");
    };
    for(i=0;i<12;i++){
        addch('-');
    };
    printw("\n%s",ITEMS[player.i[c.x][c.y].id].name);
    attr_set(A_REVERSE,ITEMS[player.i[i][j].id].t.cp,NULL);
    mvaddch(c.y+2,c.x+1,ITEMS[player.i[c.x][c.y].id].t.c);

};
void inventory(){
    int k,i,j;
    static COORDS c={};
    do{
        drawinv(c);
        k=getch();
        switch(k){
            case 'a':
            case 'A':
            case KEY_LEFT:
                c.x--;
                break;
            case 'd':
            case 'D':
            case KEY_RIGHT:
                c.x++;
                break;
            case 'w':
            case 'W':
            case KEY_UP:
                c.y--;
                break;
            case 'S':
            case 's':
            case KEY_DOWN:
                c.y++;
                break;
        };
        c.x+=(c.x<0)-(c.x>9);
        c.y+=(c.y<0)-(c.y>9);
    }while((k!='q')&&(k!='Q'));
    clear();
};
