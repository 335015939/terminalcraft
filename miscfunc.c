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
    move(0,79);
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
char fall(){
    if(isinmap(player.c.x,player.c.y+1)){
        if(getmaptiledata(player.c.x,player.c.y+1).fallthrough){
            player.c.y++;
            return 1;
        };
    };
    return 0;
};
void mineblock(){
    int k,x=player.facingx+player.c.x,y=player.facingy+player.c.y;
    if(!isinmap(x, y)) return;
    TILEDATA t=getmaptiledata(x,y);
    for(;;){
        
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