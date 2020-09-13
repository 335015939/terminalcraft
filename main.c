#include "header.h"
#include "vars_def.h"

int main(){
  myinit();
  clear();
  TILE x={'#',A_NORMAL,0,0};
  mvdtiledata(1,1,TILES[0]);
  wgetch(stdscr);
  endwin();
};
