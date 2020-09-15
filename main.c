#include "header.h"
#include "vars_def.h"

MAPTILE *map=NULL;
_SETTINGS SETTINGS={
    30,5,0x33
};

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
  mvdtiledata(0,0,TILES[map[0].id]);
  dtiledata(TILES[x[0].id]);
  getch();
  endwin();
};
