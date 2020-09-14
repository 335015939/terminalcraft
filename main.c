#include "header.h"
#include "vars_def.h"

int main(){
  myinit();
  clear();
  mvdtiledata(1,1,TILES[0]);
  getch();
  endwin();
};
