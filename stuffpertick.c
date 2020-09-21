#include "enum.h"
#include "funcs.h"
#include "header.h"
char scanfortrunk(int x,int y){
    int i,j;
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(isinmap(x+i-2, y+j-2)){
                if(getmaptiledata(x+i-2, y+j-2).type==TILE_TYPE_TREE_TRUNK){
                    return 1;
                };
            };
        };
    };
    return 0;
}
void stuffperticknofall(){
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
                    if(getmaptiledata(x, y).type!=TILE_TYPE_DIRT){
                        putmapid(x, y-1,TILE_AIR);
                    };
                };
                break;
            case TILE_TYPE_LEAF:
                if(!scanfortrunk(x,y)){
                    putmapid(x, y, TILE_AIR);
                };
            case TILE_TYPE_OAK_SAPLING:
                break;
            case TILE_TYPE_PINE_SAPLING:
                break;
        };
    };
    if((rand()%100)<=player.regen && player.hp<player.maxhp) player.hp++; 
    entities();
};
void stuffpertick(){
    fall();
    stuffperticknofall();
};