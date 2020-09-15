#include "header.h"
int getmapid(int x,int y){
    return WORLD.map[x+(MAP_W*y)].id;
};
void putmapid(int x,int y,int t){
    WORLD.map[x+(MAP_W*y)].id=t;
};