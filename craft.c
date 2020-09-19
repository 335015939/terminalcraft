#include "defines.h"
#include "header.h"
#include "structs.h"
#include "vars.h"
#include <curses.h>
int CURRENT_STATION=0;
void recipiescan(){
    int i=0,j,yes;
    for(;i<CRAFT_RECIPIE_NUM;i++){
        for(j=0;j<CRAFT_RECIPIE[i].ingredient_num;j++){
            if (searchinv(CRAFT_RECIPIE[i].ingredients[j].id).found) continue;
            yes=0;
            break;
        };
        if(yes){
            player.recipies_found[i]=1;
        };
    };
};
void _printcraft(int i){
    if(player.recipies_found[i]){
        printw("%s(%d)",ITEMS[CRAFT_RECIPIE[i].result.id].name,
        CRAFT_RECIPIE[i].result.num);
    }else{
        printw("Not yet found");
    };
};
void print_require(_CRAFT_RECIPIE r,int f){
    int i=0;
    move(0,20);
    printw("Ingredients:");
    if (f){
        for(i=0;i<r.ingredient_num;i++){
            move(i+1,21);
            printw("%s(%d),",ITEMS[r.ingredients[i].id].name,r.ingredients[i].num);
        };
        move(i+1,20);
        printw("Makes:%s(%d)",ITEMS[r.result.id].name,r.result.num);
        move (i+2,20);
        printw("station:%s",tiletypetostationname(r.station));
    }else{
        printw("???");
        move(1,20);
        printw("Makes:???");
        move(2,20);
        printw("station:???");
    };
};
void printcraft(int s,int so){
    clear();
    attr_set(A_NORMAL,0,NULL);
    int i;
    for(i=(s-so);i<min(CRAFT_RECIPIE_NUM,24);i++){
        move(i,0);
        _printcraft(i);
    };
    print_require(CRAFT_RECIPIE[s],player.recipies_found[s]);
    move(so,0);
    attron(A_REVERSE);
    _printcraft(s);
};
void craft(){
    clear();
    static int selected=0;
    int selected_onscreen=0,k;
    printw("scanning...");
    recipiescan();
    clear();
    
    for(;;){
        printcraft(selected,selected_onscreen);
        switch((k=getch())){
            case 'j':
            case 'J':
            case '\n':
                if(invremovemultipleitembyid(CRAFT_RECIPIE[selected].ingredient_num,
                CRAFT_RECIPIE[selected].ingredients));
                invadditem(CRAFT_RECIPIE[selected].result);
            case 's':
            case 'S':
            case KEY_DOWN:
                if(selected<(CRAFT_RECIPIE_NUM-1)){
                    selected ++;
                    if(selected_onscreen<23) selected_onscreen++;
                };
                break;
            case 'w':
            case 'W':
            case KEY_UP:
                if(selected>0){
                    selected --;
                    if(selected_onscreen>0) selected_onscreen--;
                };
                break;
            case 'q':
            case 'Q':
                goto lbl_end;
        };
    };
    lbl_end:
    clear();
    return;
};