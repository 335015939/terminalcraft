#include "enum.h"
#include "funcs.h"
#include "header.h"

struct {
    int sealvl;
} world;

void mktree(COORDS c,int type){
    int height,trunk,leaf,i=0,j;
    switch(type){
        case TREE_OAK:
            trunk=TILE_OAK_TRUNK;
            leaf=TILE_OAK_LEAF;
            height=5+(rand()%5);
            break;
    };
    for(;i<height;i++){
        putmapid(c.x,c.y+i,trunk);
    };
    for(j=-1;j<2;j++){
        putmapid(c.x+j,c.y+i,trunk);
    };
    for(i=0;i<2;i++){
        for(j=-1;j<2;j++){
            putmapid(c.x+j,c.y+i,trunk);
        };
    };
};

void mkunder(COORDS c,int dirt_len){
    int l=c.y+dirt_len;
    c.y++;
    for(;c.y<l;c.y++){
        putmapid(c.x,c.y,TILE_DIRT);
    };
    for(;c.y<MAP_H;c.y++){
        putmapid(c.x,c.y,TILE_STONE);
    };
};

COORDS genplains(COORDS c,int l){
    int x=c.x+l;
    if (x>MAP_W){
        x=MAP_W;
    };
    for(;c.x<x;c.x++){
        if(c.x>=MAP_W){
            break;
        };
        putmapid(c.x, c.y, TILE_GRASS);
        mkunder(c,5+(rand()%4));
        if (!(rand()%7)){
            if(rand()%2){
                c.y++;
            }else{
                c.y--;
            };
            c.y+=(c.y<=(world.sealvl-2))-(c.y>=(world.sealvl+2));
        };
    };
    return c;
};

COORDS genhills(COORDS c,int l){
    int x=c.x+l,direction=rand()%2;
    if (x>MAP_W){
        x=MAP_W;
    };
    for(;c.x<x;c.x++){
        if(c.x>=MAP_W){
            break;
        };
        putmapid(c.x, c.y, TILE_GRASS);
        mkunder(c,5+(rand()%4));
        if (!(rand()%2)){
            if(direction){
                c.y++;
            }else{
                c.y--;
            };
            if(c.y>=(world.sealvl+8)){
                direction=!direction;
            }else if(c.y<=(world.sealvl-4)){
                direction=!direction;
            } ;
            c.y+=(c.y<=(world.sealvl-4))-(c.y>=(world.sealvl+8));
        };
    };
    return c;
}

void mapgen(){
    world.sealvl=MAP_H/4;
    COORDS c={0,world.sealvl+(random()%11)-6};
    COORDS (*genfuncs[2])(COORDS c,int l)={genplains,genhills};
    for(c.x=0;c.x<MAP_W;){
        c=(*genfuncs[rand()%2])(c,(MAP_W/100)+(rand()%10));
    };
};