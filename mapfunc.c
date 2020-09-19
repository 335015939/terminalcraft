#include "funcs.h"
#include "header.h"

char placeblock(){
    int x=player.facingx+player.c.x,y=player.facingy+player.c.y;
    if (gethelditemdata().type != ITEM_TYPE_PLACABLE){
        return 0;
    };
    TILEDATA t=TILES[gethelditemdata().placetileid];
    if(!isinmap(x, y)) return 0;
    if(!getmaptiledata(x, y).placeover|| (
        x==player.c.x && y==player.c.y &&
        !t.passable
    ))return 0;
    putmapid(x,y,t.id);
    player.i[0][player.holding].num--;
    if(!player.i[0][player.holding].num){
        player.i[0][player.holding].id=0;
    };
    return 1;
};

void drawmap(int startx,int starty){
    int i,j=0,x,y;
    move(3,0);
    for(;j<21;j++){
        for(i=0;i<79;i++){
            if((x=i+startx)>=0 && (y=j+starty)>=0){
                if(x<MAP_W && y<MAP_H){
                    dmaptile(i+startx,j+starty);
                }else{
                    dtile(TILES[0].t);
                    
                };
            }else{
                dtile(TILES[0].t);
            };
        };
        addch('\n');
    };
    dhotbar();
    if ((x=TILES[getmapid(player.c.x,player.c.y)].t.b)){
        init_pair(CP_PLAYER,0,x);
    }else{
        init_pair(CP_PLAYER,0,SKYCOLOR);
    };
    attr_set(A_NORMAL,CP_PLAYER,NULL);
    mvaddch(13,38,'@');
    attr_set(A_NORMAL,0,NULL);
    mvprintw(0,0,"x:%d y:%d tick:%d %c   \n\r%s          ",
    player.c.x,player.c.y,TICK,facing(),getmaptiledata(player.c.x, player.c.y).name);
};