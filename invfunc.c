#include "header.h"
#include "structs.h"
#include <curses.h>
INV_SEARCH searchinv(int id){
    int i=0,j;
    for(;i<10;i++){
        for(j=0;j<10;j++){
            if(player.i[i][j].id==id){
                return (INV_SEARCH){i,j,1};
            };
        };
    };
    return (INV_SEARCH){0,0,0};
};
char invitemcanberemoved(ITEM item,INV_SEARCH c){
    if(!c.found) return 0;
    if(player.i[c.x][c.y].num<item.num) return 0;
    return 1;
};
char invremoveitembyid(ITEM item){
    INV_SEARCH s=searchinv(item.id);
    if(!invitemcanberemoved(item,s)) return 0;
    player.i[s.x][s.y].num-=item.num;
    if(player.i[s.x][s.y].num==0) player.i[s.x][s.y].id=0;
    return 1;
};
char invremovemultipleitembyid(int num,const ITEM item[5]){
    int i;
    for(i=0;i<num;i++){
        if(!invitemcanberemoved(item[i],searchinv(item[i].id))) return 0;
    };
    for(i=0;i<num;i++){
        invremoveitembyid(item[i]);
    };
    return 1;
};
char invadditem(ITEM item){
    int j,i=0,x,maxstack;
    unsigned char freespace=0;
    for(;i<10;i++){
        for(j=0;j<10;j++){
            maxstack=ITEMS[getinvitem(i,j).id].maxstack;
            if (!getinvitem(i,j).id){
                freespace++;
            }else if(getinvitem(i,j).id==item.id){
                if((x=player.i[i][j].num+item.num)>=maxstack){
                    item.num-=(maxstack-player.i[i][j].num);
                    player.i[i][j].num=maxstack;
                }else{
                    player.i[i][j].num+=item.num;
                    return 1;
                };
            };
        };
    };
    if(!freespace) return 0;
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            if (!getinvitem(i,j).id){
                player.i[i][j]=item;
                return 1;
            };
        };
    };
    return 0;
};
void drawitem(ITEMDATA i){
    dtile(i.t);
};
void drawinv(COORDS c,COORDS s,char f){
    int i,j;
    clear();
    attr_set(A_BOLD,0,NULL);
    addstr("Inventory\n");
    for(i=0;i<12;i++){
        addch('-');
    };
    addch('\n');
    for(j=0;j<10;j++){
        addch('|');
        for(i=0;i<10;i++){
            drawitem(ITEMS[player.i[i][j].id]);
        };
        attr_set(A_BOLD,0,NULL);
        addstr("|\n");
    };
    for(i=0;i<12;i++){
        addch('-');
    };
    printw("\n%s(%d)",ITEMS[player.i[c.x][c.y].id].name,player.i[c.x][c.y].num);
    attr_set(A_REVERSE,ITEMS[player.i[c.x][c.y].id].t.cp,NULL);
    mvaddch(c.y+2,c.x+1,ITEMS[player.i[c.x][c.y].id].t.c);
    
    if(f){
        attr_set(A_REVERSE,ITEMS[player.i[s.x][s.y].id].t.cp,NULL);
        mvaddch(s.y+2,s.x+1,ITEMS[player.i[s.x][s.y].id].t.c);
    };

};
void inventory(){
    int k;
    static COORDS c={};
    COORDS s={};
    ITEM item;
    char f=0;
    do{
        drawinv(c,s,f);
        k=getch();
        switch(k){
            case 'a':
            case 'A':
            case KEY_LEFT:
                c.x--;
                break;
            case 'd':
            case 'D':
            case KEY_RIGHT:
                c.x++;
                break;
            case 'w':
            case 'W':
            case KEY_UP:
                c.y--;
                break;
            case 'S':
            case 's':
            case KEY_DOWN:
                c.y++;
                break;
            case 'j':
            case 'J':
            case '\n':
                if (!f){
                    f=1;
                    s=c;
                }else{
                    item=player.i[c.x][c.y];
                    player.i[c.x][c.y]=player.i[s.x][s.y];
                    player.i[s.x][s.y]=item;
                    f=0;
                };
        };
        c.x+=(c.x<0)-(c.x>9);
        c.y+=(c.y<0)-(c.y>9);
    }while((k!='q')&&(k!='Q'));
    clear();
};
