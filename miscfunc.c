#include "funcs.h"
#include "header.h"
#include <curses.h>

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
        if(getmaptiledata(player.c.x,player.c.y+1).fallthrough && getmaptiledata(player.c.x,player.c.y).fallthrough){
            player.c.y++;
            return 1;
        };
    };
    return 0;
};
void mineblock(){
    int k,x=player.facingx+player.c.x,y=player.facingy+player.c.y;
    if(!isinmap(x, y)) return;
    if(fall()) return;
    TILEDATA t=getmaptiledata(x,y);
    attr_set(A_NORMAL,0,NULL);
    for(;;){
        if (!getmapid(x,y)) break;
        mvprintw(2,0,"Mining block...");
        putmapid(x, y, 0);
        TICK++;
        k=getch();
    };
    mvprintw(2,0,"                   ");
    drawmap(player.c.x-38,player.c.y-10);
};
void moveplayer(int x,int y){
    if(y==-1){fall();};
    if(isinmap(x+player.c.x,y+player.c.y) && (x || y)){
        if(getmaptiledata(x+player.c.x,y+player.c.y).passable){
            player.c.x+=x;
            player.c.y+=y;
        }else TICK--;
    }else TICK --;
    if(y!=-1){fall();};
};