#include "header.h"
#include <curses.h>
void drawitem(ITEMDATA i){
    dtile(i.t);
};
void inventory(){
    int k,i,j;
    static COORDS c;
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
    do{
        k=getch();
        switch(k){
            case 'a':
            case 'A':
            case KEY_LEFT:
            break;
        };
    }while((k!='q')&&(k!='Q'));
    clear();
};
