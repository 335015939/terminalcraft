#include "enum.h"
#include "funcs.h"
#include "header.h"
#include "vars_def.h"

//MAPTILE *map=NULL;
_SETTINGS SETTINGS={
    3000,500,0x33
};
int TICK=0;
PLAYER player={{}};
_WORLD WORLD={};
int main(){
    int x,k,y,tick;
    myinit();
    clear();
    mapgen();
    player.c.x=MAP_W/2;
    for(;!getmapid(player.c.x,player.c.y) && player.c.y<MAP_H;player.c.y++){};

    //putmapid(player.c.x,player.c.y,TILE_OAK_TRUNK);

    for(;;){
        drawmap(player.c.x-38,player.c.y-10);
        attr_set(A_NORMAL,0,NULL);
        drawfacing();
        mvprintw(0,0,"x:%d y:%d tick:%d   \n\r%s          ",player.c.x,player.c.y,TICK,TILES[getmapid(player.c.x,player.c.y)].name);
        if ((x=TILES[getmapid(player.c.x,player.c.y)].t.b)){
            init_pair(CP_PLAYER,0,x);
        }else{
            init_pair(CP_PLAYER,0,SKYCOLOR);
        };
        attr_set(A_NORMAL,CP_PLAYER,NULL);
        mvaddch(13,38,'@');
        while (TICK==tick){  
            x=y=0;
            k=getch();
            switch(k){
                case 'Q':
                case 'q':
                    goto lbl_end;
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
                    mineblock();
                    break;
            };
            moveplayer(x,y);
        };
        tick=TICK;
    };
    lbl_end:
    for(x=0;x<MAP_W;x++){
        free(MAP[x]);
    };
    free(WORLD.map);
    endwin();
};
