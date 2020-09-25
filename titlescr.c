#include "header.h"
#include "vars.h"
#include <curses.h>
int CHOSEN_WORLD=0;
int CHOSEN_PLAYER=0;
#define OP_TYPE_INT 1
#define OP_TYPE_BOOL 2
int optionstatus[5]={};
const int optiontype[5]={OP_TYPE_INT,             OP_TYPE_INT              ,OP_TYPE_BOOL  ,OP_TYPE_BOOL,OP_TYPE_BOOL};
void drawopt(int i){
    const char *options[5]={"Map height(Crashes if changed)","Map width(Crashes if changed)","Autosave","Debug mode","Auto pickup"};
    const char*tf[2]={"Off","On"};
    addstr(options[i]);
    if(optiontype[i]==OP_TYPE_BOOL){
        printw(":%s\n",tf[optionstatus[i]]);
    }else{
        printw(":%d\n",optionstatus[i]);
    };
};
void options(){
    int i,selected=0;
    
    for(;;){
        optionstatus[0]=MAP_H;
        optionstatus[1]=MAP_W;
        optionstatus[2]=SETTINGS.autosave;
        optionstatus[3]=SETTINGS.debugmode;
        optionstatus[4]=SETTINGS.autopickup;
        clear();
        attr_set(A_NORMAL,0,NULL);
        addstr("Options\n\n");
        for(i=0;i<5;i++){
            drawopt(i);
        };
        move(selected+2,0);
        attron(A_REVERSE);
        drawopt(selected);
        i=0;
        switch(getch()){
            case 'q':
            case 'Q':
            case '\e':
                return;
            case 'w':
            case 'W':
            case KEY_UP:
                selected -=(selected>0);
                break;
            case 's':
            case 'S':
            case KEY_DOWN:
                selected +=(selected<4);
                break;
            case 'a':
            case 'A':
            case KEY_LEFT:
                i=-2;
            case 'd':
            case 'D':
            case KEY_RIGHT:
                i++;
                if(optiontype[selected]==OP_TYPE_BOOL){
                    optionstatus[selected]=!optionstatus[selected];
                }else{
                    optionstatus[selected]+=((optionstatus[selected]<25000 && i>0)
                    -(optionstatus[selected]>200 && i<0))*100;
                };
                break;
        };
        MAP_H=optionstatus[0];
        MAP_W=optionstatus[1];
        SETTINGS.autosave=optionstatus[2];
        SETTINGS.debugmode=optionstatus[3];
        SETTINGS.autopickup=optionstatus[4];
    };
};
int _titlescr();
char isplayersaved(int i){
    char *fname=malloc_throw(26);
    sprintf(fname,"./terminal_craft/player%d",i);
    FILE *f=fopen(fname,"r");
    if(f!=NULL){
        fclose(f);
        return 1;
    }else{
        return 0;
    };
    free(fname);
};
void _playprintplayer(int i){
    if(i==10){
        addstr("Back");
    }else {
        if(isplayersaved(i)){
            printw("Player %d(Load)\n",i);
        }else{
            printw("Player %d(New)\n",i);
        };
    };
}
int playchooseplayer(){
    static int p_selection=0;
    int i;
    clear();
    printw("Choose Player\n\n");
    for(;;){
        attr_set(A_NORMAL,0,NULL);        
        move(2,0);
        for(i=0;i<11;i++){
            _playprintplayer(i);
        };
        move(p_selection+2,0);
        attron(A_REVERSE);
        _playprintplayer(p_selection);
        switch(getch()){
            case 'j':
            case 'J':
            case '\n':
                return p_selection;
            case 's':
            case 'S':
            case KEY_DOWN:
                p_selection +=(p_selection<10);
                break;
            case 'w':
            case 'W':
            case KEY_UP:
                p_selection -=(p_selection>0);
                break;
            };
    };
};
char isworldsaved(int i){
    char *fname=malloc_throw(25);
    sprintf(fname,"./terminal_craft/world%d",i);
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
};
int play(){
    clear();
    if((CHOSEN_PLAYER=playchooseplayer())==10) return 0;
    if((CHOSEN_WORLD=playchooseworld())==10) return 0;
    load();
    gotospawn();
    return 1;
};
int titlescr(){
    for(;;){
        switch(_titlescr()){
            case 0:
                if(play()) return 0;
                break;
            case 1:
                options();
                savesettings();
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
