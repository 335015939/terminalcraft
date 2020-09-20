#include "funcs.h"
#include "header.h"
#include "vars.h"
#include <string.h>
char saveplayer(){
    char *fname=malloc_throw(26);
    int i;
    sprintf(fname,"./terminal_craft/player%d",CHOSEN_PLAYER);
    FILE *f=fopen(fname,"w");
    char *m=(char *)&player;
    for(i=0;i<sizeof(PLAYER);i++){
        fputc(m[i],f);
    };
    fclose(f);
    free(fname);
    return 1;
}
char loadplayer(){
    int i;
    char *fname=malloc_throw(26);
    sprintf(fname,"./terminal_craft/player%d",CHOSEN_PLAYER);
    FILE *f=fopen(fname,"r+");
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
    addstr("Loading...");
    refresh();

    sprintf(fname,"./terminal_craft/world%d",CHOSEN_WORLD);
    FILE *f=fopen(fname,"r+");

    char *m=(char *)MAP;
    fread(m,MAP_W*MAP_H*sizeof(MAPTILE),1,f);
    
    char *w=(char *)&WORLD;
    for(i=0;i<(sizeof(_WORLD));i++){
        w[i]=fgetc(f);
    };

    MAP=(MAPTILE *)m;
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
    sprintf(fname,"./terminal_craft/world%d",CHOSEN_WORLD);
    FILE *f=fopen(fname,"w");

    char *m=(char *)MAP;
    clear();
    addstr("Saving...");
    refresh();
    fwrite(m, (MAP_W*MAP_H*sizeof(MAPTILE)),1,f);
    
    char *w=(char *)&WORLD;
    for(i=0;i<sizeof(_WORLD);i++){
        fputc(w[i],f);
    };

    // printw("\ntick:%d\nwidth:%d\nheight:%d\nspawnx:%d\nspawny:%d\n",
    // TICK,WORLD.width,WORLD.height,WORLD.spawnx,WORLD.spawny);
    // getch();

    fclose(f);
    free(fname);
    return 1;
}