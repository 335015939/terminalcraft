#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED
#include "structs.h"
#define mvdtile(y,x,t) move((y),(x));dtile(t)
#define dtiledata(z) dtile((z).t)
#define mvdtiledata(y,x,z) move((y),(x));dtile((z).t)
void myinit();
void dtile(TILE t);
void initmycolorpairs();
void init_map(MAPTILE *map);
void *malloc_throw(unsigned long size);
int getmapid(int x,int y);
void putmapid(int x,int y,int t);
#endif
