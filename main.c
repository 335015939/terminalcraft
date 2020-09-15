#include "header.h"
#include "vars_def.h"

//MAPTILE *map=NULL;
_SETTINGS SETTINGS={
    30,5,0x33
};
_WORLD WORLD={};
int main(){
  myinit();
  clear();
  MAPTILE *x=(MAPTILE*)(malloc(10*sizeof(MAPTILE)));
  init_color(0xff,0xff,0xff,0xff);
  //putmapid(0,0,TILE_STONE);
  printw("a");
  getch();
  mvdtiledata(1,1,TILES[0]);
  getch();
  dtiledata(TILES[x[0].id]);
  getch();
  mvdtiledata(0,0,TILES[getmapid(0,0)]);
  
  getch();
  free(WORLD.map);
  endwin();
};
