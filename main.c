#include "header.h"
#include "vars_def.h"

//MAPTILE *map=NULL;
_SETTINGS SETTINGS={
    3000,500,0x33
};
_WORLD WORLD={};
int main(){
  myinit();
  clear();
  init_color(0xff,0xff,0xff,0xff);
  mapgen();
  drawmap(0,0);
  getch();
  free(WORLD.map);
  endwin();
};
