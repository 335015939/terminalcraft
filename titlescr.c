#include "header.h"
#include <curses.h>
int CHOSEN_WORLD=0;
int CHOSEN_PLAYER=0;
int _titlescr();
char isworldsaved(int i){
    char *fname=malloc_throw(25);
    sprintf(fname,"./terminalcraft/world%d",i);
    FILE *f=fopen(fname,"r");
    if(f!=NULL){
        fclose(f);
        return 1;
    }else{
        return 0;
    };
    free(fname);
};
void _playprintworld(int i){
    if(i==10){
        addstr("Back");
    }else {
        if(isworldsaved(i)){
            printw("World %d(Load)\n",i);
        }else{
            printw("World %d(New)\n",i);
        };
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
    clear();
    if((CHOSEN_WORLD=playchooseworld())==10) return 0;
    if(!isworldsaved(CHOSEN_WORLD)){
        mapgen();
        player.c.x=MAP_W/2;
        for(;!getmapid(player.c.x,player.c.y) && player.c.y<MAP_H;player.c.y++){};

        invadditem((ITEM){ITEM_WOOD_PICKAXE,1});
    }else {
        loadworld(CHOSEN_WORLD);
    };
    return 1;
}
int titlescr(){
    for(;;){
        switch(_titlescr()){
            case 0:
                if(play()) return 0;
                break;
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
    int i;
    static int selection=0;
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
