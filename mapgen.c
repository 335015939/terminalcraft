#include "enum.h"
#include "funcs.h"
#include "header.h"

struct {
    int sealvl;
} world;
void mkorevein(COORDS c,int len,int id){
    int _id=getmapid(c.x, c.y),i;
    char x,y;
    if(_id==TILE_DIRT || _id==TILE_GRASS) return;
    for(i=0;i<len;i++){
        do{
            do{
                x=y=0;
                if((rand()%2)){
                    x=(2*(rand()%2))-1;
                }else{
                    y=(2*(rand()%2))-1;
                };
            }while(!isinmap(c.x+x, c.y+y));
        }while(getmapid(x+c.x, y+c.y)==TILE_DIRT);
        c.x+=x;
        c.y+=y;
        putmapid(c.x, c.y, id);
    };
};
void mkores(){
    COORDS c;
    int i,id,maxchance=0,orenum,temp;
    const int ores[]={TILE_COPPER_ORE,TILE_COAL_ORE,TILE_IRON_ORE,TILE_SILVER_ORE,TILE_GOLD_ORE,TILE_DIAMOND_ORE};
    const int oremindepth[]={0,0,world.sealvl+(75),((2*MAP_H)/5),((3*MAP_H)/5),((MAP_H*4)/5)};
    const unsigned int orechance[]={10,22,30,36,39,41};
    const unsigned int oreminchance[]={0,11,23,31,37,40};
    orenum=sizeof(ores)/sizeof(unsigned int);
    for(i=0;i<orenum;i++){
        maxchance=max(maxchance,orechance[i]);
    };
    for(i=0;i<(MAP_W*MAP_H)/750;i++){
        lbl_redo:
        do{
            do{
                c.x=rand()%MAP_W;
                c.y=rand()%MAP_H;
            }while(!isinmap(c.x,c.y));
        }while(getmapid(c.x, c.y)!=TILE_STONE);
        for(i=0;i<orenum;i++){
            temp=rand()%maxchance;
            id=0;
            if((temp>=oreminchance[i])&&(temp<orechance[i])&&(c.y>oremindepth[i])){
                id=ores[i];
            };
        };
        if(!id) goto lbl_redo;
        mkorevein(c,20,id);
    };
};

void mktree(COORDS c,int type){
    int height,trunk,leaf,i=0,j,x,y,leafheight;
    switch(type){
        case TREE_OAK:
            trunk=TILE_OAK_TRUNK;
            leaf=TILE_OAK_LEAF;
            height=4+(rand()%4);
            leafheight=3+(rand()%3);
            break;
        case TREE_PINE:
            trunk=TILE_PINE_TRUNK;
            leaf=TILE_PINE_LEAF;
            height=6+(rand()%5);
            leafheight=(height-1-(rand()%3));
            break;

    };
    for(;i<height;i++){
        putmapid(c.x,c.y-i,trunk);
    };
    if(!(rand()%2)){
        i++;
        height ++;
    };
    for(j=-1;j<2;j++){
        x=c.x+j;
        y=c.y-i;
        if(x>0&&y>0&&x<MAP_W&&y<MAP_H){
            if(!getmapid(x,y))putmapid(x,y,leaf);
        };
    };
    for(i=1;i<leafheight;i++){
        for(j=-2;j<3;j++){
            x=c.x+j;
            y=c.y+i-height;
            if(x>0&&y>0&&x<MAP_W&&y<MAP_H){
                if(!getmapid(x,y))putmapid(x,y,leaf);
            };
        };
    };
};

void mkunder(COORDS c,int dirt_len){
    int l=c.y+dirt_len,i;
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
        if(!(rand()%32)){
            mktree(c,TREE_OAK);
        };
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

COORDS genforest(COORDS c,int l){
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
        if(!(rand()%3)){
            mktree(c,TREE_OAK+(rand()%2));
        };
        if (!(rand()%4)){
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
        if(!(rand()%11)){
            mktree(c,TREE_OAK);
        };
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
    COORDS (*genfuncs[3])(COORDS c,int l)={genplains,genhills,genforest};
    for(c.x=0;c.x<MAP_W;){
        c=(*genfuncs[rand()%3])(c,(MAP_W/50)+(rand()%10));
    };
    mkores();
};