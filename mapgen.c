#include "funcs.h"
#include "header.h"

void mktree(){

};

COORDS genplains(COORDS c,int l){
    int x=c.x;
    for(;c.x<(x+l);c.x++){
        putmapid(c.x, c.x, TILE_DIRT);
    };
};

void mapgen(){
    COORDS c;
    COORDS (*genfuncs[1])(COORDS c)=,int l{genplains};
    for(c.x=0;c.x<MAP_W;c.x++){
        c=(genfuncs[1])(c);
    }
};