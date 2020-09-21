#include "enum.h"
#include "funcs.h"
#include "header.h"
#include "vars_def.h"
#include <curses.h>

//MAPTILE *map=NULL;
_SETTINGS SETTINGS={
    3000,500,0x21,0x21,1,0
};
PLAYER player={};
_WORLD WORLD={NULL,6*60,3000,500};
int main(){
    int x,k,y,tick=TICK;
    myinit();
    lbl_start:
    titlescr();
    clear();
    

    for(;;){
        
        while (TICK==tick){  
            
            drawmap(player.c.x-38,player.c.y-10);
            x=y=0;
            k=getch();
            switch(k){
                case 'k':
                case 'K':
                    if(isinmap(player.c.x+player.facingx,player.c.y+player.facingy)){
                        switch(getmaptiledata(player.c.x+player.facingx, player.c.y+player.facingy).type){
                            case TILE_TYPE_CHEST:
                                chest(player.c.x+player.facingx,player.c.y+player.facingy);
                                break;
                        };
                    }
                    break;
                case 'Q':
                case 'q':
                    if(SETTINGS.autosave){
                        saveplayer();
                        saveworld();
                    };
                    goto lbl_start;
                case 'a':
                    x--;
                case 'A':
                    player.facingx=-1;
                    player.facingy=0;
                    break;
                case 'd':
                    x++;
                case 'D':
                    player.facingy=0;
                    player.facingx=1;
                    break;
                case 's':
                    y++;
                case 'S':
                    player.facingy=1;
                    player.facingx=0;
                    break;
                case 'w':
                    y--;
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
                case 'p':
                case 'P':
                case '\e':
                    if(pause()){
                        goto lbl_start;
                    };
                    clear();
                    break;
            };
            if(x || y) moveplayer(x,y);
        };
        tick=TICK;
    };
    //lbl_end:
};
