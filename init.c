#include "header.h"
#include <curses.h>

void myinit(){
    initscr();
    start_color();
    init_color(0xff,0,0,0);
    curs_set(0);
    raw();
    noecho();
    keypad(stdscr, true);
    if(LINES<24 || COLS < 80){
        printw("Warning:terminal recommended size:80x24 (currently %dx%d)",COLS,LINES);
        getch();
    };    if (!has_colors()){
	    printw("Warning:colors not supported");
        getch();
    }else if(!can_change_color()){
	    printw("Warning:colors may be incorrect");
        getch();
    };
    initmycolorpairs();
    init_map(map);
};

void init_map(MAPTILE *map){
    int i=0;
    map=(MAPTILE *)malloc_throw(sizeof(MAPTILE)*MAP_W*MAP_H);
};

void initmycolorpairs(){
    int i,x;
    for(i=0;i<(sizeof(MY_COLOR_PAIRS)/sizeof(COLOR_PAIR_DEF));i++){
        if ((x=MY_COLOR_PAIRS[i].b)==0xff){
            x=SKYCOLOR;
        };
        init_pair(MY_COLOR_PAIRS[i].id,MY_COLOR_PAIRS[i].f,x);
    };

};
