#include "../header.h"
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
    for(i=0;i<((MAP_W*MAP_H)/2000);i++){
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
                break;
            case TILE_TYPE_OAK_SAPLING:
                mktree((COORDS){x,y},TREE_OAK);
                break;
            case TILE_TYPE_PINE_SAPLING:
                mktree((COORDS){x,y},TREE_PINE);
                break;
        };
    };
    if((rand()%100)<=getregen() && player.hp<getmaxhp()) player.hp++; 
    lvlup();
    entities();
    if(SETTINGS.debugmode){
        player.hp=getmaxhp();
    };
    die();
    if(SETTINGS.autopickup){
        if(hasdroppeditem(player.c.x,player.c.y)){
            pickupitem(player.c.x, player.c.y);
        };
    };
};
void stuffpertick(){
    fall();
    stuffperticknofall();
};