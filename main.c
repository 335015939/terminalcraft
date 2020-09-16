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
    int x,k;
    myinit();
    clear();
    mapgen();
    player.c.x=MAP_W/2;
    for(;!getmapid(player.c.x,player.c.y) && player.c.y<MAP_H;player.c.y++){};

    putmapid(player.c.x,player.c.y,TILE_OAK_TRUNK);

    for(;;){
        drawmap(player.c.x-38,player.c.y-10);
        attr_set(A_NORMAL,0,NULL);
        mvprintw(0,0,"x:%d y:%d  \n\r%s       ",player.c.x,player.c.y,TILES[getmapid(player.c.x,player.c.y)].name);
        if ((x=TILES[getmapid(player.c.x,player.c.y)].t.b)){
            init_pair(CP_PLAYER,0,x);
        }else{
            init_pair(CP_PLAYER,0,SKYCOLOR);
        };
        attr_set(A_NORMAL,CP_PLAYER,NULL);
        mvaddch(13,38,'@');
        switch((k=getch())){
            case 'Q':
            case 'q':
                goto lbl_end;
            case 'a':
            case 'A':
                if(player.c.x>0)player.c.x--;
                break;
            case 'd':
            case 'D':
                if(player.c.x<(MAP_W-1)) player.c.x++;
                break;
            case 's':
            case 'S':
                if(player.c.y<(MAP_H-1))player.c.y++;
                break;
            case 'w':
            case 'W':
                if(player.c.y>0)player.c.y--;
                break;
        };
    };
    lbl_end:
    for(x=0;x<MAP_W;x++){
        free(MAP[x]);
    };
    free(WORLD.map);
    endwin();
};
