#include "enum.h"
#include "funcs.h"
#include "header.h"
#include "vars_def.h"
#include <curses.h>

//MAPTILE *map=NULL;
_SETTINGS SETTINGS={
    3000,500,0x33
};
int TICK=0;
PLAYER player={};
_WORLD WORLD={};
int main(){
    int x,k,y,tick;
    myinit();
    clear();
    mapgen();
    player.c.x=MAP_W/2;
    for(;!getmapid(player.c.x,player.c.y) && player.c.y<MAP_H;player.c.y++){};


ITEM temp={ITEM_DIRT,99};
invadditem(temp);


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
                    mineblock();
                    break;
                case 'i':
                case 'I':
                    inventory();
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
