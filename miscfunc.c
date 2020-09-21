#include "enum.h"
#include "funcs.h"
#include "header.h"
#include <curses.h>
void die(){
    clear();
    attr_set(0,0,NULL);
    addstr("You died!\nPress any key to continue");
    getch();
};
void gotospawn(){
    player.c.x=WORLD.spawnx;
    player.c.y=WORLD.spawny;
    for(;!getmaptiledata(player.c.x,player.c.y).passable;player.c.y--);
    for(;getmaptiledata(player.c.x,player.c.y+1).fallthrough;player.c.y++);
};
char pause(){
    for(;;){
        clear();
        printw("Paused\n\nS:Save\nQ:quit\nJ or [ENTER]:continue");
        refresh();
        switch(getch()){
            case 'q':
            case '\e':
            case 'Q':
                return 1;
            case 's':
            case 'S':
                saveworld();
                saveplayer();
                clear();
                addstr("Saved!");
                getch();
                break;
            case 'j':
            case 'J':
            case '\n':
                return 0;
        };
    };
};
char *tiletypetostationname(int type){
    switch(type){
        case TILE_TYPE_NONE:
            return "None";
        case TILE_TYPE_CHEST:
            return "Chest";
        case TILE_TYPE_FURNACE:
            return "Furnace";
        case TILE_TYPE_WORKBENCH:
            return "Workbench";
        default:
            return "Unknown";
    };
};
int max(int x,int y){
    if(x>y) return x;
    return y;
};
int min(int x,int y){
    if(x<y) return x;
    return y;
};
void *malloc_throw(size_t size){
    void *p=malloc(size);
    if (!p){
        clear();
        printw("Error:not enough memory");
        getch();
        exit(ERR_OUT_OF_MEM);
    };
    return p;
};
unsigned int facing(){
    //attr_set(A_NORMAL,0,NULL);
    move(0,79);
    if(player.facingx==1){
        return '>';
    }else if(player.facingx==-1){
        return '<';
    }else if(player.facingy==1){
        return 'V';
    }else if(player.facingy==-1){
        return '^';
    }else{
        return '+';
    };
}
char fall(){
    if(isinmap(player.c.x,player.c.y+1)){
        if(getmaptiledata(player.c.x,player.c.y+1).fallthrough && getmaptiledata(player.c.x,player.c.y).fallthrough
         && !SETTINGS.debugmode){
            player.c.y++;
            return 1;
        };
    };
    return 0;
};
void mineblock(){
    ITEM item;
    int x=player.facingx+player.c.x,y=player.facingy+player.c.y,z,health,i,k;
    if(!isinmap(x, y)) return;
    if(fall()) return;
    TILEDATA t=getmaptiledata(x,y);
    if(!t.minable) return;
    if((t.hardlvl>gethelditemdata().minelvl)&&!SETTINGS.debugmode) return;
    if(SETTINGS.debugmode){
        health=1;
    }else{
        health=t.hardness;
    };
    attr_set(A_NORMAL,0,NULL);
    for(i=(rand()%4);;i++){
        if(i==4) i=0;
        if (!getmapid(x,y)) break;
        stuffpertick();
        drawmap(player.c.x-38,player.c.y-10);
        mvprintw(2,0,"Mining block...%c",SPIN[i]);
        health-=gethelditemdata().minepower;
        k=getch();
        if(k!='j' && k!='J') {
            mvprintw(2,0,"                   ");
            return;
        };
        if(health<=0 || SETTINGS.debugmode)putmapid(x, y, 0);
    };
    emptystorage(&(getmaptile(x, y).storage));
    for(x=0;x<5;x++){
        if(!t.drops.id[x]) break;
        if((z=((t.drops.max[x])-(t.drops.low[x])))){
            y=(rand()% z ) + (t.drops.low[x]);
        }else {
            y=t.drops.low[x];
        }
        if((rand()%100)<=t.drops.chance[x]){
            item.id=t.drops.id[x];
            item.num=y;
            invadditem(item);
        };
    };
    mvprintw(2,0,"                           ");
};
void moveplayer(int x,int y){
    if(y==-1){fall();};
    if(isinmap(x+player.c.x,y+player.c.y) && (x || y)){
        if(getmaptiledata(x+player.c.x,y+player.c.y).passable || SETTINGS.debugmode){
            player.c.x+=x;
            player.c.y+=y;
            stuffperticknofall();
        };
    };
    if(y!=-1){fall();};
};
void emptystorage(ITEM (*items)[10][10]){
    int i,j;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            (*items)[i][j]=(ITEM){0,0};
        };
    };
};