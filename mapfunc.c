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
    mvprintw(0,0,"x:%d y:%d %2d:%2d %c   \n\r%s          ",
    player.c.x,player.c.y,(TICK/60)%24,TICK%60,facing(),getmaptiledata(player.c.x, player.c.y).name);
    switch((TICK/60)%24){
        case 22 ... 23:
        case 0 ... 3:
            SETTINGS.skycolor=0x10;
            break;
        case 4:
            SETTINGS.skycolor=0x11;
            break;
        case 5:
            SETTINGS.skycolor=0x12;
            break;
        case 6:
            SETTINGS.skycolor=0x13;
            break;
        case 7:
            SETTINGS.skycolor=0x14;
            break;
        case 8:
            SETTINGS.skycolor=0x15;
            break;
        case 9 ... 16:
            SETTINGS.skycolor=0x21;
            break;
        case 17:
            SETTINGS.skycolor=0x15;
            break;
        case 18:
            SETTINGS.skycolor=0x14;
            break;
        case 19:
            SETTINGS.skycolor=0x13;
            break;
        case 20:
            SETTINGS.skycolor=0x12;
            break;
        case 21:
            SETTINGS.skycolor=0x11;
            break;
    };
    if(SETTINGS.oldskycolor!=SETTINGS.skycolor){
        SETTINGS.oldskycolor=SETTINGS.skycolor;
        initmycolorpairs();
    };
};