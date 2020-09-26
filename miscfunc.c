#include "funcs.h"
#include "header.h"
#include "vars.h"
void lvlup(){
    struct{
        int *dest;
        int increaseby;
        char *name;
    }attrs[4]={
        {&player.basedef,1,"Base defence"},
        {&player.basedmg,1,"Base damage"},
        {&player.basemaxhp,3,"Max hp"},
        {&player.baseregen,2,"Base regen"}
    };
    int x;
    for(;;){
        if(player.exp<getexpneeded()) return;

        clear();
        x=rand()%4;
        *attrs[x].dest+=attrs[x].increaseby;
        printw("You leveled up!\nlvl %d-->lvl %d\nYour %s increase by %d",player.lvl,player.lvl+1,
        attrs[x].name,attrs[x].increaseby);
        player.lvl++;
        getch();
    };
};
void showplayerstats(){
    clear();
    printw("Your stats\n\nHealth:%d/%d\nLevel:%d(%d/%d)\nDefence:%d\nBase damage:%d\nRegen chance:%d%%\n",
    player.hp,getmaxhp(),player.lvl,player.exp,getexpneeded(),getdef(),getbasedmg(),getregen());
    getch();
    clear();
};
char dropitems(DROPITEMDATA drops,COORDS c,char putininvfirst){
    int x,y,z;
    ITEM item;
    for(x=0;x<5;x++){
        if(!drops.id[x]) break;
        if((z=((drops.max[x])-(drops.low[x])))){
            y=(rand()% z ) + (drops.low[x]);
        }else {
            y=drops.low[x];
        }
        if((rand()%100)<=drops.chance[x]){
            item.id=drops.id[x];
            item.num=y;
            if(putininvfirst){
                if(!invadditem(item)){
                    dropitem(c.x,c.y,item);
                };
            }else{
                dropitem(c.x,c.y,item);
            };
        };
    };
    return 1;
};
void die(){
    int k;
    if(player.hp<1){
        player.lvl=1;
        player.exp=0;
        player.baseregen=5;
        player.basedef=0;
        player.basedmg=0;
        player.basemaxhp=50;
        player.hp=player.basemaxhp;
        gotospawn();
        clear();
        attr_set(0,0,NULL);
        addstr("You died!\nPress [ENTER] or 'Q' to continue");
        do{
            k=getch();
        }while(k!='\n'&&k!='q'&&k!='Q');
    };
};
void playerattack(){
    ENTITY *ent;
    if(isinmap(player.c.x+player.facingx, player.c.y+player.facingy)){
        if((ent=&getmaptile(player.c.x+player.facingx, 
        player.c.y+player.facingy).e)->id!=0){
            HIT_MSG="You hit something";
            ent->hp-=getdmg(gethelditemdata().damage);
        };
        stuffpertick();
    };
}
void gotospawn(){
    player.c.x=WORLD.spawnx;
    player.c.y=WORLD.spawny;
    for(;!getmaptiledata(player.c.x,player.c.y).passable;player.c.y--);
    for(;getmaptiledata(player.c.x,player.c.y+1).fallthrough;player.c.y++);
};
char pause(){
    for(;;){
        clear();
        printw("Paused\n\nS:Save\nQ:quit\nJ or [ENTER]:continue");
        refresh();
        switch(getch()){
            case 'q':
            case '\e':
            case 'Q':
                return 1;
            case 's':
            case 'S':
                save();
                addstr("Saved!");
                getch();
                break;
            case 'j':
            case 'J':
            case '\n':
                return 0;
        };
    };
};
char *tiletypetostationname(int type){
    switch(type){
        case TILE_TYPE_NONE:
            return "None";
        case TILE_TYPE_CHEST:
            return "Chest";
        case TILE_TYPE_FURNACE:
            return "Furnace";
        case TILE_TYPE_WORKBENCH:
            return "Workbench";
        default:
            return "Unknown";
    };
};
int max(int x,int y){
    if(x>y) return x;
    return y;
};
int min(int x,int y){
    if(x<y) return x;
    return y;
};
void *malloc_throw(size_t size){
    void *p=malloc(size);
    if (!p){
        clear();
        printw("Error:not enough memory");
        getch();
        exit(ERR_OUT_OF_MEM);
    };
    return p;
};
unsigned int facing(){
    //attr_set(A_NORMAL,0,NULL);
    move(0,79);
    if(player.facingx==1){
        return '>';
    }else if(player.facingx==-1){
        return '<';
    }else if(player.facingy==1){
        return 'V';
    }else if(player.facingy==-1){
        return '^';
    }else{
        return '+';
    };
}
char fall(){
    if(isinmap(player.c.x,player.c.y+1)){
        if(getmaptiledata(player.c.x,player.c.y+1).fallthrough && getmaptiledata(player.c.x,player.c.y).fallthrough
         && (!SETTINGS.debugmode || player.canfly)){
            player.c.y++;
            DISTANCE_FALLEN++;
            return 1;
        }else{
            if(!SETTINGS.debugmode && player.falldmg){
                entityattack((DISTANCE_FALLEN-3),"");
            };
            DISTANCE_FALLEN=0;
        };
    };
    return 0;
};
void mineblock(){
    int x=player.facingx+player.c.x,y=player.facingy+player.c.y,health,i,k;
    if(!isinmap(x, y)) return;
    if(fall()) return;
    TILEDATA t=getmaptiledata(x,y);
    if(!t.minable) return;
    if((t.hardlvl>gethelditemdata().minelvl)&&!SETTINGS.debugmode) return;
    if(SETTINGS.debugmode){
        health=1;
    }else{
        health=t.hardness;
    };
    attr_set(A_NORMAL,0,NULL);
    for(i=(rand()%4);;i++){
        if(i==4) i=0;
        if (!getmapid(x,y)) break;
        stuffpertick();
        drawmap(player.c.x-38,player.c.y-10);
        mvprintw(2,0,"Mining block...%c",SPIN[i]);
        health-=gethelditemdata().minepower;
        k=getch();
        if(k!='j' && k!='J') {
            mvprintw(2,0,"                   ");
            return;
        };
        if(health<=0 || SETTINGS.debugmode)putmapid(x, y, 0);
    };
    emptystorage(&(getmaptile(x, y).storage));
    dropitems(t.drops,(COORDS){x,y},0);
    mvprintw(2,0,"                           ");
};
void moveplayer(int x,int y){
    if(y==-1){fall();};
    if(isinmap(x+player.c.x,y+player.c.y) && (x || y)){
        if(getmaptiledata(x+player.c.x,y+player.c.y).passable || SETTINGS.debugmode){
            player.c.x+=x;
            player.c.y+=y;
            stuffperticknofall();
        };
    };
    if(y!=-1){fall();};
};
void emptystorage(ITEM (*items)[10][10]){
    int i,j;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            (*items)[i][j]=(ITEM){0,0};
        };
    };
};
void updateskycolor(){
    switch((TICK/60)%24){
        case 22 ... 23:
        case 0 ... 3:
            SETTINGS.skycolor=0x10;
            break;
        case 4:
        case 21:
            SETTINGS.skycolor=0x11;
            break;
        case 5:
        case 20:
            SETTINGS.skycolor=0x12;
            break;
        case 6:
        case 19:
            SETTINGS.skycolor=0x13;
            break;
        case 7:
        case 18:
            SETTINGS.skycolor=0x14;
            break;
        case 8:
        case 17:
            SETTINGS.skycolor=0x15;
            break;
        case 9 ... 16:
            SETTINGS.skycolor=0x21;
            break;
    };
    if(SETTINGS.oldskycolor!=SETTINGS.skycolor){
        SETTINGS.oldskycolor=SETTINGS.skycolor;
        initmycolorpairs();
    };
};
