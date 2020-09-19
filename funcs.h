#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED
#include "structs.h"
#define mvdtile(y,x,t) move((y),(x));dtile(t)
#define dtiledata(z) dtile((z).t)
#define mvdtiledata(y,x,z) move((y),(x));dtile((z).t)
#define dmaptile(x,y) dtile(TILES[getmapid(x,y)].t)
#define mvdmaptile(y,x,mx,my) move((y),(x));dtile(TILES[getmapid(x,y)].t)
#define getmapid(x,y) (WORLD.map[(x)+(MAP_W*(y))].id)
#define putmapid(x,y,z) (WORLD.map[(x)+(MAP_W*(y))].id=(z))
#define getmaptiledata(x,y) (TILES[getmapid(x,y)])
#define isinmap(x,y) (((x)>=0)&&((y)>=0)&&((x)<MAP_W)&&((y)<MAP_H))
#define getinvitem(x,y) (player.i[(x)][(y)])
#define gethelditemdata() (ITEMS[player.i[0][player.holding].id])
#define tiledatatostationname(x) (tiledatatostationname((x).type))
void myinit();
void inventory();
char saveworld();
char invremovemultipleitembyid(int num,const ITEM item[5]);
char invremoveitembyid(ITEM item);
char invitemcanberemoved(ITEM item,INV_SEARCH c);
void dtile(TILE t);
void pause();
int titlescr();
char loadworld();
void initmycolorpairs();
char *tiletypetostationname(int type);
void init_map();
void *malloc_throw(unsigned long size);
void mapgen();
void drawmap(int x,int y);
unsigned int facing();
void mineblock();
char invadditem(ITEM item);
void moveplayer(int x,int y);
void dhotbar();
char placeblock();
int max(int x,int y);
int min(int x,int y);
void craft();
INV_SEARCH searchinv(int id);
#endif
