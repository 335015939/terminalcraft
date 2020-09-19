#include "header.h"
#include <curses.h>

void _myexit(){
    free(MAP);
    endwin();
};
void myinit(){
    int i;
    atexit(_myexit);
    system("export TERM=xterm-256color");
    srand(time(NULL));
    initscr();
    start_color();
    init_color(0xff,0,0,0);
    curs_set(0);
    keypad(stdscr,TRUE);
    raw();
    noecho();
    keypad(stdscr, true);
    if(LINES<24 || COLS < 80){
        printw("Warning:terminal recommended size:80x24 (currently %dx%d)\n",COLS,LINES);
        getch();
    };    if (!has_colors()){
	    printw("Warning:colors not supported\n");
        getch();
    }else if(!can_change_color()){
	    printw("Warning:colors may be incorrect\n");
        getch();
    };
    initmycolorpairs();
    init_map();
    for(i=0;i<TILE_NUM;i++){
        if(TILES[i].id){
            if(TILES[i].id!=i){
                printw("Warning:tile id mismatch(%d->%d)\n",i,TILES[i].id);
                getch();
            };
        };
    };
    for(i=0;i<TILE_NUM;i++){
        if(ITEMS[i].id){
            if(ITEMS[i].id!=i){
                printw("Warning:tile id mismatch(%d->%d)\n",i,ITEMS[i].id);
                getch();
            };
        };
    };
};

void init_map(){
    MAPTILE *map=(MAPTILE*)(malloc_throw((sizeof(MAPTILE) * MAP_W * MAP_H)));
    WORLD.map=map;
};

void initmycolorpairs(){
    int i,x;
    for(i=0;i<(sizeof(MY_COLOR_PAIRS)/sizeof(COLOR_PAIR_DEF));i++){
        if((x=MY_COLOR_PAIRS[i].b)){
            init_pair(MY_COLOR_PAIRS[i].id,MY_COLOR_PAIRS[i].f,x);
        }else{
            init_pair(MY_COLOR_PAIRS[i].id,MY_COLOR_PAIRS[i].f,SKYCOLOR);
        }
    };

};
