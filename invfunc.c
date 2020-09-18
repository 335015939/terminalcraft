#include "header.h"
#include <curses.h>
void drawitem(ITEMDATA i){
    dtile(i.t);
};
void drawinv(COORDS c,COORDS s,char f){
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
    printw("\n%s(%d)",ITEMS[player.i[c.x][c.y].id].name,player.i[c.x][c.y].num);
    attr_set(A_REVERSE,ITEMS[player.i[c.x][c.y].id].t.cp,NULL);
    mvaddch(c.y+2,c.x+1,ITEMS[player.i[c.x][c.y].id].t.c);
    
    if(f){
        attr_set(A_BLINK | A_REVERSE,ITEMS[player.i[s.x][s.y].id].t.cp,NULL);
        mvaddch(s.y+2,s.x+1,ITEMS[player.i[s.x][s.y].id].t.c);
    };

};
void inventory(){
    int k,i,j;
    static COORDS c={};
    COORDS s={};
    ITEM item;
    char f=0;
    do{
        drawinv(c,s,f);
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
            case 'j':
            case 'J':
            case '\n':
                if (!f){
                    f=1;
                    s=c;
                }else{
                    item=player.i[c.x][c.y];
                    player.i[c.x][c.y]=player.i[s.x][s.y];
                    player.i[s.x][s.y]=item;
                    f=0;
                };
        };
        c.x+=(c.x<0)-(c.x>9);
        c.y+=(c.y<0)-(c.y>9);
    }while((k!='q')&&(k!='Q'));
    clear();
};
