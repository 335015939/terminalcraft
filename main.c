#include "header.h"
#include "vars_def.h"

int main(){
  myinit();
  attron(COLOR_PAIR(CP_TILE_DIRT));
  getch();
  endwin();
};
