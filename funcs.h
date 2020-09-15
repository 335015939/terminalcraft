#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED
#include "structs.h"
#define mvdtile(y,x,t) move((y),(x));dtile(t)
#define dtiledata(z) dtile((z).t)
#define mvdtiledata(y,x,z) move((y),(x));dtile((z).t)
#define dmaptile(x,y) dtile(TILES[WORLD.map[(x)][(y)].id].t)
#define mvdmaptile(y,x,mx,my) move((y),(x));dtile(TILES[WORLD.map[(x)][(y))].id].t)
#define getmapid(x,y) (WORLD.map[(x)][(y)].id)
#define putmapid(x,y,z) (WORLD.map[(x)][(y)].id=(z))
void myinit();
void dtile(TILE t);
void initmycolorpairs();
void init_map();
void *malloc_throw(unsigned long size);
void mapgen();
void drawmap(int x,int y);
#endif
