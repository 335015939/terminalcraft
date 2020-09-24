#include "defines.h"
#include "funcs.h"
#include "header.h"
#include "vars.h"

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
char drawent(int x,int y){
    int id;
    if(!(id=getmaptile(x, y).e.id)) return 0;
    if(getmaptiledata(x, y).t.b){
        init_pair(ENTITIES[id].t.cp,ENTITIES[id].t.b,getmaptiledata(x, y).t.b);
    }else{
        init_pair(ENTITIES[id].t.cp,ENTITIES[id].t.b,SKYCOLOR);
    };
    attr_set(ENTITIES[id].t.a,ENTITIES[id].t.cp,NULL);
    addch(ENTITIES[id].t.c);
    return 1;
};
char drawdropitem(int x,int y){
    int i=0;
    for(i=0;i<5;i++){
        if(getmaptile(x, y).dropped[i].id)
            goto lbl_draw;
    };
    return 0;
    lbl_draw:
    dtile(ITEMS[getmaptile(x, y).dropped[i].id].t);
    return 1;
};
void drawmap(int startx,int starty){
    int i,j=0,x,y;
    move(3,0);
    for(;j<21;j++){
        for(i=0;i<79;i++){
            if((x=i+startx)>=0 && (y=j+starty)>=0){
                if(x<MAP_W && y<MAP_H){
                    if(!drawent(x,y)){
                        if(!drawdropitem(x,y)){
                            dmaptile(i+startx,j+starty);
                        };
                    };
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
    if(SETTINGS.debugmode){
        mvprintw(0,0,"x:%d y:%d %2d:%02d %s %c %d       \n%s "
        "                         \n%s                         ",
        player.c.x,player.c.y,(TICK/60)%24,TICK%60,((char *[2]){"day","night"})[isnight()]
        ,facing(),ENTITIES_IN_WORLD,HIT_MSG,GOT_HIT_MSG);
    }else{
    mvprintw(0,0,"x:%d y:%d %2d:%02d %c %d/%d       \n%s                          \n%s                         ",
        player.c.x,player.c.y,(TICK/60)%24,TICK%60,facing(),player.hp,getmaxhp(),HIT_MSG,GOT_HIT_MSG);
    };
    updateskycolor();
};