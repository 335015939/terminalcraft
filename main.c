#include "header.h"
#include "vars_def.h"

int main(){
  myinit();
  clear();
  init_color(0xff,0xff,0xff,0xff);
  putmapid(0,0,TILE_STONE);
  mvdtiledata(1,1,TILES[0]);
  mvdtiledata(0,0,TILES[getmapid(0,0)]);
  getch();
  endwin();
};
