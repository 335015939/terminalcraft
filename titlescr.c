#include "header.h"
#include <curses.h>

int _titlescr();
int titlescr(){
    for(;;){
        switch(_titlescr()){
            case 0:
                return 0;
            case 1:
                clear();
                printw("Not avalaible right now");
                getch();
                break;
            case 2:
                exit(0);
        };
    };
};

int _titlescr(){
    int i,selection=0;
    const char *options[3]={"Play","Options","Quit"};
    clear();
    attr_set(A_BOLD,0,NULL);
    printw("  TerminalCraft");
    for(;;){
        attr_set(A_NORMAL,0,NULL);
        for(i=0;i<3;i++){
            move(i+2,3);
            printw("%s",options[i]);
        };
        attron(A_REVERSE);
        move(selection+2,3);
        printw("%s",options[selection]);
        switch(getch()){
            case 's':
            case 'S':
            case KEY_DOWN:
                selection +=(selection<2);
                break;
            case 'w':
            case 'W':
            case KEY_UP:
                selection -=(selection>0);
                break;
            case 'j':
            case 'J':
            case '\n':
                return selection;
        };
    };
};
