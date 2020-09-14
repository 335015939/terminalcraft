#include "header.h"
#include "vars_def.h"

int main(){
  myinit();
  clear();
  init_color(0xff,0xff,0xff,0xff);
  mvdtiledata(1,1,TILES[0]);
  getch();
  endwin();
};
