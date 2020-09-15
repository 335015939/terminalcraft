#include "header.h"

void mktree(){

};

void mapgen(){
    COORDS c;
    COORDS (*genfuncs[1])(COORDS c)={};
    for(c.x=0;c.x<MAP_W;c.x++){
        c=(genfuncs[1])(c);
    }
};