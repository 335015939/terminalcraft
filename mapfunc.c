#include "header.h"

void drawmap(int startx,int starty){
    int i,j=0,x,y;
    move(3,0);
    for(;j<21;j++){
        for(i=0;i<79;i++){
            if((x=i+startx)>=0 && (y=j+starty)>=0){
                if(x<MAP_W && y<MAP_H){
                    dmaptile(i+startx,j+starty);
                }else{
                    dtile(TILES[0].t);
                };
            }else{
                dtile(TILES[0].t);
            };
        };
        addch('\n');
    };
};