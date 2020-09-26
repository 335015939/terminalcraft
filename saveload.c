#include "funcs.h"
#include "header.h"
#include "vars.h"
#include <curses.h>
#include <string.h>
void save(){
    clear();
    attr_set(0,0,NULL);
    addstr("Saving player...");
    refresh();
    saveplayer();
    mvprintw(0, 0, "Saving World.");
    refresh();
    saveworld();
    clear();
};
void load(){
    clear();
    attr_set(0,0,NULL);
    addstr("Loading player...");
    refresh();
    memset(&player,0,sizeof(PLAYER));
    memset(MAP,0,sizeof(MAPTILE)*MAP_W*MAP_H);
    if(!loadplayer()){
        player=(PLAYER){{},0,0,0//coords,facingx,facingy,holding
        ,100,{},{},{}//hp,recipies found,inventory,equipped stuff
        ,0,0,0,0,0,0,0,0,//added attributes from equipment
        0,0,5,100//base stats
        ,0,1//can fly,fall damage
        };
        invadditem((ITEM){ITEM_WOOD_SWORD,1});
        invadditem((ITEM){ITEM_WOOD_PICKAXE,1});
    };
    mvprintw(0, 0, "Loading World.");
    refresh();
    if(!loadworld()){
        mapgen();
    };
    clear();
};
void savesettings(){
    int i;
    system("mkdir -p ./terminal_craft");
    FILE *f=fopen("./terminal_craft/settings","w");
    char *m=(char *)&SETTINGS;
    for(i=0;i<sizeof(SETTINGS);i++){
        fputc(m[i],f);
    };
    fclose(f);
    return;
};
void loadsettings(){
    int i;
    FILE *f=fopen("./terminal_craft/settings","r");
    if(!f) return;
    char *m=(char *)&SETTINGS;
    for(i=0;i<sizeof(SETTINGS);i++){
        m[i]=fgetc(f);
    };
    fclose(f);
    return;
};
char saveplayer(){
    system("mkdir -p ./terminal_craft");
    char *fname=malloc_throw(26);
    int i;
    sprintf(fname,"./terminal_craft/player%d",CHOSEN_PLAYER);
    FILE *f=fopen(fname,"w");
    if(!f) return 0;
    char *m=(char *)&player;
    for(i=0;i<sizeof(PLAYER);i++){
        fputc(m[i],f);
    };
    fclose(f);
    free(fname);
    return 1;
};
char loadplayer(){
    int i;
    char *fname=malloc_throw(26);
    sprintf(fname,"./terminal_craft/player%d",CHOSEN_PLAYER);
    FILE *f=fopen(fname,"r+");
    if(!f) return 0;
    char *m=(char *)&player;
    for(i=0;i<(sizeof(PLAYER));i++){
        m[i]=fgetc(f);
    };
    fclose(f);
    free(fname);
    return 1;
};
char loadworld(){
    int i;
    char *fname=malloc_throw(28);
    clear();
    attr_set(A_NORMAL,0,NULL);
    
    sprintf(fname,"./terminal_craft/world%d",CHOSEN_WORLD);
    FILE *f=fopen(fname,"r+");
    if(!f) return 0;

    char *m=(char *)MAP;
    fread(m,MAP_W*MAP_H*sizeof(MAPTILE),1,f);
    
    char *w=(char *)&WORLD;
    for(i=0;i<(sizeof(_WORLD));i++){
        w[i]=fgetc(f);
    };

    MAP=(MAPTILE *)m;

    fread(entityxy,sizeof(COORDS)*MAX_ENTITY,1,f);

    fclose(f);
    free(fname);

    //printw("\ntick:%d\nwidth:%d\nheight:%d\nspawnx:%d\nspawny:%d\n",
    //TICK,WORLD.width,WORLD.height,WORLD.spawnx,WORLD.spawny);
    //getch();

    MAP_H=WORLD.height;
    MAP_W=WORLD.width;

    return 1;
};
char saveworld(){
    int i;
    char *fname=malloc_throw(25);
    system("mkdir -p ./terminal_craft");
    sprintf(fname,"./terminal_craft/world%d",CHOSEN_WORLD);
    FILE *f=fopen(fname,"w");

    char *m=(char *)MAP;
    fwrite(m, (MAP_W*MAP_H*sizeof(MAPTILE)),1,f);
    
    char *w=(char *)&WORLD;
    for(i=0;i<sizeof(_WORLD);i++){
        fputc(w[i],f);
    };

    fwrite(entityxy,sizeof(COORDS)*MAX_ENTITY,1,f);

    fclose(f);
    free(fname);
    return 1;
};