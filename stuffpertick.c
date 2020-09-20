#include "enum.h"
#include "funcs.h"
#include "header.h"

void stuffpertick(){
    int x,y,i;
    TICK++;
    for(i=0;i<((MAP_W*MAP_H)/1000);i++){
        do{
            x=rand()%MAP_W;
            y=rand()%MAP_H;
        }while(!isinmap(x, y));
        switch(getmaptiledata(x, y).type){
            case TILE_TYPE_DIRT:
                y--;
                if(isinmap(x, y)){
                    if(!getmapid(x, y)){
                        putmapid(x, y, TILE_GRASS);
                    };
                };
                break;
            case TILE_TYPE_GRASS:
                y++;
                if(isinmap(x, y)){
                    if(!getmapid(x, y)){
                        putmapid(x, y-1,TILE_AIR);
                    };
                };
                break;
            case TILE_TYPE_OAK_SAPLING:
                break;
            case TILE_TYPE_PINE_SAPLING:
                break;
        };
    };
};