#include "enum.h"
#include "header.h"
#include "vars_def.h"

//MAPTILE *map=NULL;
_SETTINGS SETTINGS={
    3000,500,0x33
};
PLAYER player={{}};
_WORLD WORLD={};
int main(){
    myinit();
    clear();
    mapgen();
    putmapid(1500,200,TILE_STONE);
    player.c.x=MAP_W/2;
    for(;!getmapid(player.c.x,player.c.y) && player.c.y<MAP_H;player.c.y++){};
    drawmap(player.c.x-38,player.c.y-10);
    attr_set(A_NORMAL,0,NULL);
    mvprintw(0,0,"x:%d y:%d",player.c.x,player.c.y);
    getch();
    free(WORLD.map);
    endwin();
};
