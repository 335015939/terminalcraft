#include "../header.h"
#include <string.h>
struct {
    int sealvl;
} world;
typedef struct {
    int id;
    int chance;
    int low;
    int high;
} FILLCHESTCONTENT;
int findnextgrass(int x){
    int y;
    for(y=MAP_H;y>=0;y--){
        if(isinmap(x,y)){
            if(getmapid(x, y)==TILE_GRASS) break;
        };
    };
    return y;
};
void gentrees(){
    int x,y;
    const int treetypes[]={TREE_OAK,TREE_PINE};
    clear();
    for(x=0;x<MAP_W;x++){
        mvprintw(0,0,"Generating trees...%d%%",(100*x)/MAP_W);
        refresh();
        if((y=findnextgrass(x))==-1) continue;
        if(!(rand()%5)){
            mktree((COORDS){x,y},treetypes[rand()%2]);
        };
    };
};
void smoothworld(){
    clear();
    int x;
    for(x=1;x<MAP_W;x++){
        mvprintw(0,0,"Smoothing world...%d%%",(100*x)/MAP_W);
        refresh();
        /*
        copy chunk of grass placement data starting from x to buffer
        check if dramatic changes in grass placement
        check if horizontal blocks
        some stuff goes down
        update map based on whats in buffer
        */
    };
};
void mksinglechest(COORDS c,const FILLCHESTCONTENT* content,int num){
    int i,j,which;
    if(!isinmap(c.x,c.y)) return;
    putmapid(c.x, c.y,TILE_CHEST);
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            which=rand()%num;
            if((rand()%500)<=content[which].chance){
                getmaptile(c.x,c.y).storage[i][j].id=content[which].id;
                if(content[which].high==content[which].low){
                    getmaptile(c.x,c.y).storage[i][j].num=content[which].low;
                }else{
                    getmaptile(c.x,c.y).storage[i][j].num=content[which].low+
                    (rand()%(content[which].high-content[which].low));
                };
            };
        };
    };
};
void mkchests(){
    int i,x,y;
    clear();
    const FILLCHESTCONTENT content_surface[5]={
        {ITEM_MAGIC_MIRROR,3,1,1},
        {ITEM_DIRT,75,4,10},
        {ITEM_STONE,40,2,8},
        {ITEM_COAL,20,1,6},
        {ITEM_WOOD,80,1,7}
    };
    const FILLCHESTCONTENT content_sky[19]={
        {ITEM_IRON_SWORD,4,1,1},
        {ITEM_COPPER_SWORD,4,1,1},
        {ITEM_WOOD_SWORD,4,1,1},
        {ITEM_WOOD_PICKAXE,4,1,1},
        {ITEM_COPPER_PICKAXE,4,1,1},
        {ITEM_IRON_PICKAXE,4,1,1},
        {ITEM_WOOD_HELMET,4,1,1},
        {ITEM_COPPER_HELMET,4,1,1},
        {ITEM_IRON_HELMET,4,1,1},
        {ITEM_WOOD_BREASTPLATE,4,1,1},
        {ITEM_COPPER_BREASTPLATE,4,1,1},
        {ITEM_IRON_BREASTPLATE,4,1,1},
        {ITEM_COPPER_GREAVES,4,1,1},
        {ITEM_IRON_GREAVES,4,1,1},
        {ITEM_COPPER_BOOTS,4,1,1},
        {ITEM_IRON_BOOTS,4,1,1},
        {ITEM_SNAKE_SKIN_CLOAK,3,1,1},
        {ITEM_IRON,4,1,5},
        {ITEM_COPPER,4,1,5},
    };
    const FILLCHESTCONTENT content_underground[7]={
        {ITEM_COPPER_ORE,30,1,10},
        {ITEM_IRON_ORE,21,1,9},
        {ITEM_COAL,60,2,8},
        {ITEM_SILVER_ORE,15,1,7},
        {ITEM_GOLD_ORE,12,1,5},
        {ITEM_STONE,75,2,20},
        {ITEM_WOOD_PICKAXE,10,1,1}
    };
    for(i=0;i<(MAP_W/300);i++){
        mvprintw(0,0,"Generating Chests...1/3 %d%% ",(100*i)/(MAP_W/300));
        refresh();
        do{
            do{
                x=rand()%MAP_W;
                y=rand()%MAP_H;
            }while(!isinmap(x, y));
        }while(getmapid(x, y)!=TILE_GRASS);
        mksinglechest((COORDS){x,y},content_surface,5);
    };
    for(i=0;i<(MAP_W/300);i++){
        mvprintw(0,0,"Generating Chests...2/3 %d%% ",(100*i)/(MAP_W/300));
        refresh();
        do{
            do{
                x=rand()%MAP_W;
                y=rand()%MAP_H;
            }while(!isinmap(x, y));
        }while(getmapid(x, y) || y>(MAP_H/4));
        mksinglechest((COORDS){x,y},content_sky,19);
    };
    for(i=0;i<(MAP_W/300);i++){
        mvprintw(0,0,"Generating Chests...3/3 %d%% ",(100*i)/(MAP_W/300));
        refresh();
        do{
            do{
                x=rand()%MAP_W;
                y=rand()%MAP_H;
            }while(!isinmap(x, y));
        }while(getmapid(x, y)!=TILE_STONE);
        mksinglechest((COORDS){x,y},content_underground,7);
    };
};
void mksinglestructure(const COORDS c,const int h,const int w){
    FILLCHESTCONTENT (*chestcontent);
    int contentnum;
    if(//check if all points are inside map
        !isinmap(c.x,c.y)||
        !isinmap(c.x+w-1,c.y)||
        !isinmap(c.x,c.y+h-1)||
        !isinmap(c.x+h-1,c.y+h-1)
    )return;

    int i,j;

    for(i=0;i<w;i++){//fill with wood walls
        for(j=0;j<h;j++){
            putmapid(c.x+i, c.y+j, TILE_WOOD_WALL);
        };
    };

    for(i=0;i<w;i++){//put walls
        putmapid(c.x+i,c.y,TILE_WOOD);
        putmapid(c.x+i, c.y+h-1,TILE_WOOD);
    };
    for(j=0;j<h;j++){
        putmapid(c.x,c.y+j,TILE_WOOD);
        putmapid(c.x+w-1, c.y+j,TILE_WOOD);
    };
    if(c.y<((MAP_H)/4)+20){//decide what to put into chest
        chestcontent=(FILLCHESTCONTENT[10]){
            {ITEM_DIRT,20,1,5},
            {ITEM_WOOD,80,3,10},
            {ITEM_WOOD_BREASTPLATE,20,1,1},
            {ITEM_WOOD_PICKAXE,45,1,1},
            {ITEM_COPPER_PICKAXE,30,1,1},
            {ITEM_COPPER_SWORD,30,1,1},
            {ITEM_WOOD_SWORD,50,1,1},
            {ITEM_COPPER,40,1,4},
            {ITEM_IRON,30,2,3},
            {ITEM_MAGIC_MIRROR,10,1,1}
        };
        contentnum=10;
    }else{
        chestcontent=(FILLCHESTCONTENT[15]){
            {ITEM_STONE,60,1,5},
            {ITEM_COPPER,60,1,12},
            {ITEM_IRON,63,1,16},
            {ITEM_SILVER,37,1,10},
            {ITEM_GOLD,30,1,7},
            {ITEM_DIAMOND_ORE,9,1,1},
            {ITEM_LADDER,90,3,32},
            {ITEM_WOOD,60,1,18},
            {ITEM_COPPER_ORE,75,2,20},
            {ITEM_IRON_ORE,62,2,10},
            {ITEM_SILVER_ORE,38,1,8},
            {ITEM_GOLD_ORE,34,1,6},
            {ITEM_IRON_PICKAXE,45,1,1},
            {ITEM_COPPER_PICKAXE,55,1,1},
            {ITEM_MAGIC_MIRROR,24,1,1},
        };
        contentnum=15;
    };

    mksinglechest((COORDS){c.x+(w-1)/2,c.y+h-2},chestcontent,contentnum);//create chest

    if(rand()%2){//put doors
        putmapid(c.x, c.y+h-2,TILE_DOOR);
        putmapid(c.x+w-1, c.y+h-2,TILE_DOOR);
    }else{
        if(rand()%2){
            putmapid(c.x+w-1, c.y+h-2,TILE_DOOR);
        }else{
            putmapid(c.x, c.y+h-2,TILE_DOOR);
        };
    };

};
void mkstructures(){
    int i,w,h,x,y;
    for(i=0;i<(MAP_W/300);i++){
        clear();
        printw("Generating structures...1/2 %d%%",(100*i)/(MAP_W/300));
        refresh();
        h=3+rand()%3;
        w=4+rand()%4;
        do{
            do{
                do{
                    x=rand()%MAP_W;
                    y=rand()%(MAP_H/4);
                }while(!isinmap(x-1,y)||!isinmap(x+w,y+h));
            }while((getmaptiledata(x, y+h).passable) || (getmaptiledata(x+w-1, y+h).passable));//make sure its on solid ground
        }while(
            !(getmaptiledata(x-1, y).passable) || !(getmaptiledata(x+w, y).passable)//make sure can get in
        );
        mksinglestructure((COORDS){x,y},h,w);
    };
    for(i=0;i<(MAP_W/600);i++){
        clear();
        printw("Generating structures...2/2 %d%%",(100*i)/(MAP_W/600));
        refresh();
        h=3+rand()%3;
        w=4+rand()%4;
        do{
            do{
                do{
                    x=rand()%MAP_W;
                    y=(MAP_H/4)+(rand()%(3*(MAP_H/4)));
                }while(!isinmap(x-1,y)||!isinmap(x+w,y+h));
            }while((getmaptiledata(x, y+h).passable) || (getmaptiledata(x+w-1, y+h).passable));//make sure its on solid ground
        }while(
            !(getmaptiledata(x-1, y).passable) || !(getmaptiledata(x+w, y).passable)//make sure can get in
        );
        mksinglestructure((COORDS){x,y},h,w);
    };
};
void mksinglecave(COORDS c){
    char direction;
    int x,y,j;
    putmapid(c.x, c.y, TILE_AIR);
        c.x=c.x;
        c.y=c.y+1;
        //mvprintw(10,10,"%d %d",c.x,c.y);
        direction=(2*(rand()%2))-1;
        for(j=0;j<(MAP_H+(rand()%(10*MAP_H)));j++){
            if(!isinmap(c.x,c.y)) break;
            //addch('e');
            putmapid(c.x,c.y,TILE_AIR);
            x=y=0;
            do{
                do{
                    if(rand()%4){
                        if(rand()%8){
                            x=direction;
                        }else{
                            if(rand()%8){
                                x= -direction;
                            }else{
                                direction=-direction;
                                x=direction;
                            };
                        };
                    }else{
                        y++;
                    };
                    if(!isinmap(c.x,c.y+y)) return;
                }while(!isinmap(c.x+x,c.y+y));
            }while(getmapid(x+c.x, c.y+y-1)==TILE_GRASS);
            c.x+=x;
            c.y+=y;
        };
}
void mkcaves(){
    clear();
    int i,x,y;
    for(i=0;i<(MAP_W)/300;i++){
        mvprintw(0,0,"Generating caves:%d%% ",(25*i)/(MAP_W/300));
        refresh();
        //getch();
        do{
            do{
                x=rand()%MAP_W;
                y=rand()%MAP_H;
            }while(!isinmap(x,y));
        }while(getmapid(x, y)!=TILE_GRASS);
        mksinglecave((COORDS){x,y});
    };
    for(;i<4*((MAP_W)/300);i++){
        mvprintw(0,0,"Generating caves:%d%% ",(25*i)/(4*(MAP_W/300)));
        refresh();
        //getch();
        do{
            do{
                x=rand()%MAP_W;
                y=rand()%MAP_H;
            }while(!isinmap(x,y));
        }while(getmapid(x, y)!=TILE_STONE);
        mksinglecave((COORDS){x,y});
    };
};
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
        }while(getmapid(x+c.x, y+c.y)==TILE_DIRT || getmapid(x+c.x, y+c.y)==TILE_AIR);
        c.x+=x;
        c.y+=y;
        putmapid(c.x, c.y, id);
    };
};
void mkores(){
    COORDS c;
    int i,id,maxchance=0,orenum,temp,j;
    const int ores[]={TILE_COPPER_ORE,TILE_COAL_ORE,TILE_IRON_ORE,TILE_SILVER_ORE,TILE_GOLD_ORE,TILE_DIAMOND_ORE};
    const int oremindepth[]={0,0,world.sealvl+(75),((2*MAP_H)/5),((3*MAP_H)/5),((MAP_H*4)/5)};
    const unsigned int orechance[]=   {20,44,64,80,89,94};
    const unsigned int oreminchance[]={0 ,21,45,65,81,90};
    orenum=sizeof(ores)/sizeof(unsigned int);
    for(i=0;i<orenum;i++){
        maxchance=max(maxchance,orechance[i]);
    };
    for(i=0;i<((MAP_W*MAP_H)/375);i++){
        mvprintw(0,0,"Generating Ores:%d%%",(100*i)/((MAP_W*MAP_H)/375));
        refresh();
        lbl_redo:
        do{
            do{
                c.x=rand()%MAP_W;
                c.y=rand()%MAP_H;
            }while(!isinmap(c.x,c.y));
        }while(getmapid(c.x, c.y)!=TILE_STONE);
        id=0;
        for(j=0;j<orenum;j++){
            temp=rand()%maxchance;
            if((temp>=oreminchance[j])&&(temp<orechance[j])&&(c.y>=oremindepth[j])){
                id=ores[j];
                break;
            };
        };
        if(!id) goto lbl_redo;
        mkorevein(c,20,id);
    };
};
void mktree(COORDS c,int type){
    int height,trunk,leaf,i=0,j,x,y,leafheight;
    if(!isinmap(c.x,c.y+1))return;
    if(getmaptiledata(c.x, c.y+1).type!=TILE_TYPE_DIRT) return;
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
    int x=c.x+l,y;
    if (x>MAP_W){
        x=MAP_W;
    };
    for(;c.x<x;c.x++){
        if(!isinmap(c.x,c.y)){
            break;
        };
        putmapid(c.x, c.y, TILE_GRASS);
        mkunder(c,5+(rand()%4));
        if(!(rand()%32)){
            mktree(c,TREE_OAK);
        };
        if (!(rand()%6)){
            y=c.y;
            c.y+=(c.y<=(world.sealvl-2))-(c.y>=(world.sealvl+2));
            if(rand()%2 && y==c.y){
                c.y++;
            }else{
                c.y--;
            };
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
        if(!isinmap(c.x,c.y)){
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
        if(!isinmap(c.x,c.y)){
            break;
        };
        putmapid(c.x, c.y, TILE_GRASS);
        if(!(rand()%11)){
            mktree(c,TREE_OAK);
        };
        mkunder(c,5+(rand()%4));
        if (rand()%2){
            if(direction){
                c.y++;
            }else{
                c.y--;
            };
            if(c.y>=(world.sealvl+7+(rand()%3))){
                direction=!direction;
            }else if(c.y<=(world.sealvl-3-(rand()%3))){
                direction=!direction;
            } ;
            c.y+=(c.y<=(world.sealvl-4))-(c.y>=(world.sealvl+8));
        };
    };
    return c;
};
COORDS genmountains(COORDS c,int l){
    int x=c.x+l,direction=rand()%2;
    if (x>MAP_W){
        x=MAP_W;
    };
    for(;c.x<x;c.x++){
        if(!isinmap(c.x, c.y)){
            break;
        };
        
        if (!(rand()%2)){
            c.x--;
            if(direction){
                c.y+=1;
            }else{
                c.y-=1;
            };
            if(c.y>=(world.sealvl+20+(rand()%4))){
                direction=!direction;
            }else if(c.y<=(world.sealvl-4-(rand()%4))){
                direction=!direction;
            };
            //c.y+=(c.y<=(world.sealvl-4))-(c.y>=(world.sealvl+8));
        }else{
            //c.x++;
            putmapid(c.x, c.y, TILE_GRASS);
            if(!(rand()%11)){
                mktree(c,TREE_OAK);
            };
            mkunder(c,2+(rand()%3));
        };
    };
    return c;
};

void mapgen(){
    world.sealvl=MAP_H/4;
    int x,y;
    MAP=realloc(MAP,sizeof(MAPTILE)*MAP_W*MAP_H);
    memset((char *)MAP,0,sizeof(MAPTILE)*MAP_W*MAP_H);
    COORDS c={0,world.sealvl+(random()%11)-6};
    COORDS (*genfuncs[4])(COORDS c,int l)={genplains,genhills,genforest,genmountains};
    clear();
    WORLD.height=MAP_H;
    WORLD.width=MAP_W;
    attr_set(A_NORMAL,0,NULL);
    for(c.x=0;c.x<MAP_W;){
        mvprintw(0,0,"Generating terrain:%d%% ",(100*c.x)/MAP_W);
        refresh();
        c=(*genfuncs[rand()%4])(c,(MAP_W/50)+(rand()%10));
    };
    clear();
    mkores();
    mkcaves();
    mkstructures();
    mkchests();
    smoothworld();
    gentrees();
    x=MAP_W/2;
    for(y=0;isinmap(x,y+1);y++){
      if (!TILES[getmapid(x, y+1)].passable)
        break;
    };
    WORLD.spawnx=x;
    WORLD.spawny=y;
};