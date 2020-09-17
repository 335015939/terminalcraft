#include "funcs.h"
#include "header.h"

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
void drawfacing(){
    //attr_set(A_NORMAL,0,NULL);
    move(2,0);
    if(player.facingx==1){
        addch('>');
    }else if(player.facingx==-1){
        addch('<');
    }else if(player.facingy==1){
        addch('V');
    }else if(player.facingy==-1){
        addch('^');
    }else{
        addch(ACS_SSSS);
    };
}
void fall(){
    if(isinmap(player.c.x,player.c.y+1)){
        if(getmaptiledata(player.c.x,player.c.y+1).fallthrough){
            player.c.y++;
        };
    };
};
void moveplayer(int x,int y){
    if(!x){fall();};
    if(isinmap(x+player.c.x,y+player.c.y) && (x || y)){
        if(getmaptiledata(x+player.c.x,y+player.c.y).passable){
            player.c.x+=x;
            player.c.y+=y;
            TICK++;
        };
    };
    if(x){fall();};
};