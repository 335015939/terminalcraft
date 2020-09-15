#include "funcs.h"
#include "header.h"

struct {
    int sealvl;
} world;

void mktree(){

};

COORDS genplains(COORDS c,int l){
    int x=c.x+l;
    if (x>=MAP_W){
        x=MAP_W-1;
    };
    for(;c.x<x;c.x++){
        if(c.x>=MAP_W){
            break;
        };
        putmapid(c.x, c.y, TILE_DIRT);
        // if (random()%4){
        //     if(rand()%2){
        //         c.y++;
        //     }else{
        //         c.y--;
        //     };
        //     c.y+=(c.y<=(world.sealvl-5))-(c.y>=(world.sealvl+5));
        // };
    };
    return c;
};

void mapgen(){
    world.sealvl=MAP_H/4;
    COORDS c={0,world.sealvl+(random()%11)-6};
    //COORDS (*genfuncs[1])(COORDS c,int l)={genplains};
    for(c.x=0;c.x<MAP_W;){
        //c=(genfuncs[1])(c,MAP_W);
        c=genplains(c,MAP_W);
    };
};