#include "header.h"
#include <curses.h>

int _titlescr();
void _playprintworld(int i){
    if(i==10){
        addstr("Back");
    }else {
        char *fname=malloc_throw(25);
        sprintf(fname,"./terminalcraft/world%d",i);
        FILE *f=fopen(fname,"r");
        if(f!=NULL){
            printw("World %d(Load)\n",i);
            fclose(f);
        }else{
            printw("World %d(New)\n",i);
        };
        free(fname);
    };
}
int playchooseworld(){
    static int world_selection=0;
    int i;
    clear();
    printw("Choose World\n\n");
    for(;;){
        attr_set(A_NORMAL,0,NULL);        
        move(2,0);
        for(i=0;i<11;i++){
            _playprintworld(i);
        };
        move(world_selection+2,0);
        attron(A_REVERSE);
        _playprintworld(world_selection);
        switch(getch()){
            case 'j':
            case 'J':
            case '\n':
                return world_selection;
            case 's':
            case 'S':
            case KEY_DOWN:
                world_selection +=(world_selection<10);
                break;
            case 'w':
            case 'W':
            case KEY_UP:
                world_selection -=(world_selection>0);
                break;
            };
    };
}
int play(){
    int chosenworld;
    int chosenplayer;
    clear();
    if(playchooseworld()==10) return 10;
    mapgen();
    player.c.x=MAP_W/2;
    for(;!getmapid(player.c.x,player.c.y) && player.c.y<MAP_H;player.c.y++){};

    invadditem((ITEM){ITEM_WOOD_PICKAXE,1});
    return 0;
}
int titlescr(){
    for(;;){
        switch(_titlescr()){
            case 0:
                switch(play()){
                    case 0 ... 9:
                    return 0;
                };
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
