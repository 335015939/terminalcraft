#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED
#include "structs.h"
#define mvdtile(y,x,t) move((y),(x));dtile(t)
#define dtiledata(z) dtile((z).t)
#define mvdtiledata(y,x,z) move((y),(x));dtile((z).t)
#define dmaptile(x,y) dtile(TILES[getmapid(x,y)].t)
#define mvdmaptile(y,x,mx,my) move((y),(x));dtile(TILES[getmapid(x,y)].t)
#define getmapid(x,y) (WORLD.map[(x)+(MAP_W*(y))].id)
#define getmaptile(x,y) (WORLD.map[(x)+(MAP_W*(y))])
#define putmapid(x,y,z) (WORLD.map[(x)+(MAP_W*(y))].id=(z))
#define getmaptiledata(x,y) (TILES[getmapid(x,y)])
#define getmaxhp() (player.basemaxhp+player.maxhpplus+(player.basemaxhp*(player.maxhpmulti)))
#define getregen() (player.baseregen+player.regenplus+(player.baseregen*(player.regenmulti)))
#define getdmg() (player.basedmg+player.dmgplus+(player.basedmg*(player.dmgmulti)))
#define getdef() (player.basedef+player.defplus+(player.basedef*(player.defmulti)))
#define isinmap(x,y) (((x)>=0)&&((y)>=0)&&((x)<MAP_W)&&((y)<MAP_H))
#define getinvitem(x,y) (player.i[(x)][(y)])
#define isnight() ((((TICK/60)%24)>20)||(((TICK/60)%24)<5))
#define gethelditemdata() (ITEMS[player.i[0][player.holding].id])
#define tiledatatostationname(x) (tiledatatostationname((x).type))
#define onscreen(z,t) (((z)>=player.c.x-38) && ((z)<=player.c.x+38) && ((t)>=player.c.y-10) && ((t)<=player.c.y+10))
#define nearplayer(z,t) (((z)>=player.c.x-100) && ((z)<=player.c.x+100) && ((t)>=player.c.y-100) && ((t)<=player.c.y+100))
void myinit();
void load();
void save();
char hasdroppeditem(int x,int y);
char dropitem(int x,int y,ITEM item);
void die();
void entities();
void savesettings();
void loadsettings();
void inventory();
void pickupitem(int x,int y);
char fall();
void stuffpertick();
void stuffperticknofall();
void gotospawn();
char saveworld();
char loadplayer();
void chest(int x,int y);
void emptystorage(ITEM (*items)[10][10]);
char saveplayer();
char invremovemultipleitembyid(int num,const ITEM item[5]);
char invremoveitembyid(ITEM item);
char invitemcanberemoved(ITEM item,INV_SEARCH c);
void dtile(TILE t);
char pause();
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
void mktree(COORDS c,int type);
#endif
