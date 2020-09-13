#include "header.h"
#include <curses.h>

void myinit(){
    initscr();
    start_color();
    curs_set(0);
    keypad(stdscr, true);
    if(LINES<24 || COLS < 80){
        printw("Warning:terminal recommended size:80x24 (currently %dx%d)",COLS,LINES);
    };
    if (!has_colors()){
	    printw("Warning:colors not supported");
    }else if(!can_change_color()){
	    printw("Warning:colors may be incorrect");
    };
    initmycolors();
    initmycolorpairs();
};
