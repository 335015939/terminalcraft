#include "funcs.h"
#include "header.h"
#include "vars.h"
#include <stdio.h>

char loadworld(){
    int i;
    char *fname=malloc_throw(25);
    sprintf(fname,"./terminal_craft/world%d",CHOSEN_WORLD);
    FILE *f=fopen(fname,"r");
    char *m=(char *)MAP;
    for(i=0;i<(MAP_W*MAP_H*sizeof(MAPTILE));i++){
        m[i]=fgetc(f);
    };
    fclose(f);
    free(fname);
    return 1;
};
char saveworld(){
    char *fname=malloc_throw(25);
    int i;
    sprintf(fname,"./terminal_craft/world%d",CHOSEN_WORLD);
    FILE *f=fopen(fname,"w");
    char *m=(char *)MAP;
    for(i=0;i<(MAP_W*MAP_H*sizeof(MAPTILE));i++){
        fputc(m[i],f);
    };
    fclose(f);
    free(fname);
    return 1;
}