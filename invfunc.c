#include "header.h"
#include <curses.h>
void drawitem(ITEMDATA i){

};
void inventory(){
    int k,i,j;
    clear();
    attr_set(A_BOLD,0,NULL);
    addstr("Inventory");
    for(j=0;j<10;j++){
        for(i=0;i<10;i++){
            drawitem(ITEMS[player.i[i][j].id]);
        };
    };
    do{
        k=getch();
    }while((k!='q')&&(k!='Q'));
    clear();
};
