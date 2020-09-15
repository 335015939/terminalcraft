#include <ncurses.h>

int main(){
    int i,j;
    char s[10];
    initscr();
    start_color();
    for(i=0;i<16;i++){
        sprintf(s,"%x",i);
        attr_set(A_NORMAL,0,NULL);
        mvaddch(0,i+1,s[0]);
        mvaddch(i+1,0,s[0]);
        for(j=0;j<16;j++){
            init_pair(i+(16*j)+1,0,i+(16*j));
            attron(COLOR_PAIR(i+(16*j)+1));
            mvaddch(j+1,i+1,'#');
        };
    };
    raw();
    noecho();
    curs_set(0);
    getch();
    endwin();
}