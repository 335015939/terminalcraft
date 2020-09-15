#include "enum.h"
#include "header.h"
#include "vars_def.h"

//MAPTILE *map=NULL;
_SETTINGS SETTINGS={
    3000,500,0x33
};
PLAYER player={{}};
_WORLD WORLD={};
int main(){
  myinit();
  clear();
  init_color(0xff,0xff,0xff,0xff);
  mapgen();
  player.c.x=MAP_W/2;
  for(;getmapid(player.c.x,player.c.y);player.c.y++){

  };
  drawmap(0,0);
  getch();
  free(WORLD.map);
  endwin();
};
