#include "funcs.h"
#include "header.h"

void dtile(TILE t){
    attr_set(t.a,t.cp,NULL);
    addch(t.c);
}
void dhotbar(){
    int i=0;
    ITEMDATA item;
    for(;i<10;i++){
        if(getinvitem(0,i).id){
            mvdtile(i+3,79,ITEMS[getinvitem(0,i).id].t);
        };
    };
    item=ITEMS[getinvitem(0,player.holding).id];
    TILE t={item.t.c,A_REVERSE,0x0,item.t.cp};
    mvdtile(player.holding+3,79,t);
};