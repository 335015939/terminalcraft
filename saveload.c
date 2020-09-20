#include "funcs.h"
#include "header.h"
#include "vars.h"
#include <stdio.h>
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
    //int i;
    char *fname=malloc_throw(25);
    sprintf(fname,"./terminal_craft/world%d",CHOSEN_WORLD);
    FILE *f=fopen(fname,"r");
    char *m=(char *)MAP;
    clear();
    addstr("Loading...");
    refresh();
    fread(m,MAP_W*MAP_H*sizeof(MAPTILE),1,f);
    
    /*for(i=0;i<(MAP_W*MAP_H*sizeof(MAPTILE));i++){
        mvprintw(0,0,"Loading... %d/%d",(i),(MAP_W*MAP_H*sizeof(MAPTILE)));
        refresh();
        m[i]=fgetc(f);
    };*/
    fclose(f);
    free(fname);
    return 1;
};
char saveworld(){
    char *fname=malloc_throw(25);
    //int i;
    sprintf(fname,"./terminal_craft/world%d",CHOSEN_WORLD);
    FILE *f=fopen(fname,"w");
    char *m=(char *)MAP;
    clear();
    addstr("Saving...");
    refresh();
    fwrite(m, (MAP_W*MAP_H*sizeof(MAPTILE)),1,f);
    /*for(i=0;i<(MAP_W*MAP_H*sizeof(MAPTILE));i++){
        mvprintw(0,0,"Saving... %d%%",(100*i)/(MAP_W*MAP_H*sizeof(MAPTILE)));
        refresh();
        fputc(m[i],f);
    };*/
    fclose(f);
    free(fname);
    return 1;
}