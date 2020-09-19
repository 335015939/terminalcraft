#include "enum.h"
#include "funcs.h"
#include "header.h"
#include "vars_def.h"
#include <curses.h>

//MAPTILE *map=NULL;
_SETTINGS SETTINGS={
    3000,500,0x21,0x21
};
PLAYER player={};
_WORLD WORLD={NULL,6*60};
int main(){
    int x,k,y,tick=TICK;
    myinit();
    clear();
    mapgen();
    player.c.x=MAP_W/2;
    for(;!getmapid(player.c.x,player.c.y) && player.c.y<MAP_H;player.c.y++){};

    invadditem((ITEM){ITEM_WOOD_PICKAXE,1});

    for(;;){
        
        while (TICK==tick){  
            
            drawmap(player.c.x-38,player.c.y-10);
            x=y=0;
            k=getch();
            switch(k){
                case 'Q':
                case 'q':
                    goto lbl_end;
                case 'a':
                    TICK++;
                    x--;
                case 'A':
                    player.facingx=-1;
                    player.facingy=0;
                    break;
                case 'd':
                    x++;
                    TICK++;
                case 'D':
                    player.facingy=0;
                    player.facingx=1;
                    break;
                case 's':
                    y++;
                    TICK++;
                case 'S':
                    player.facingy=1;
                    player.facingx=0;
                    break;
                case 'w':
                    y--;
                    TICK++;
                case 'W':
                    player.facingy=-1;
                    player.facingx=0;
                    break;
                case ' ':
                    player.facingx=player.facingy=0;
                    break;
                case 'j':
                case 'J':
                    switch(gethelditemdata().type){
                        case ITEM_TYPE_PICKAXE:
                            mineblock();
                            break;
                        case ITEM_TYPE_PLACABLE:
                            placeblock();
                            break;
                    };
                    break;
                case 'i':
                case 'I':
                    inventory();
                    break;
                case '0' ... '9':
                    if (k=='0'){
                        k='9'+1;
                    };
                    player.holding=k-'1';
                    break;
                case 'c':
                case 'C':
                    craft();
                    break;
            };
        };
        moveplayer(x,y);
        tick=TICK;
    };
    lbl_end:
    for(x=0;x<MAP_W;x++){
        free(MAP[x]);
    };
    free(WORLD.map);
    endwin();
};
