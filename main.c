#include "enum.h"
#include "funcs.h"
#include "header.h"
#include "vars.h"
#include "vars_def.h"
#include <curses.h>

//MAPTILE *map=NULL;
_SETTINGS SETTINGS={
    3000,500,0x21,0x21,1,0,1
};
char *GOT_HIT_MSG=" ";
char *HIT_MSG=" ";
int DISTANCE_FALLEN=0;
PLAYER player={{},0,0,0//coords,facingx,facingy,holding,hp
,20,{},{},{}//recipies found,inventory,equipped stuff
,0,0,0,0,0,0,0,0,//added attributes from equipment
0,0,15,20//base stats
,0,0//can fly,fall damage
};
_WORLD WORLD={NULL,6*60,3000,500};
int main(){
    int x,k,y,tick=TICK;
    //ENTITY *ent;
    myinit();
    lbl_start:
    titlescr();
    
    clear();
    updateskycolor();

    for(;;){
        while (TICK==tick){  
            drawmap(player.c.x-38,player.c.y-10);
            HIT_MSG=GOT_HIT_MSG=" ";
            x=y=0;
            k=getch();
            switch(k){
                case 't':
                case 'T':
                    showplayerstats();
                    break;
                case 'E':
                case 'e':
                    equip();
                    break;
                case '\\':
                case '/':
                case '\b':
                    if(gethelditemdata().id){
                        if(dropitem(player.c.x+player.facingx,player.c.y+player.facingy
                        ,player.i[0][player.holding])){
                            player.i[0][player.holding]=(ITEM){0,0};
                        };
                    };
                    break;
                case 'k':
                case 'K':
                    if(isinmap(player.c.x+player.facingx,player.c.y+player.facingy)){
                        switch(getmaptiledata(player.c.x+player.facingx, player.c.y+player.facingy).type){
                            case TILE_TYPE_CHEST:
                                chest(player.c.x+player.facingx,player.c.y+player.facingy);
                                break;
                            case TILE_TYPE_FURNACE:
                            case TILE_TYPE_WORKBENCH:
                                craft();
                                break;
                        };
                    }
                    break;
                case 'Q':
                case 'q':
                    if(SETTINGS.autosave){
                        save();
                    };
                    goto lbl_start;
                case 'a':
                    x--;
                case 'A':
                    player.facingx=-1;
                    player.facingy=0;
                    break;
                case 'd':
                    x++;
                case 'D':
                    player.facingy=0;
                    player.facingx=1;
                    break;
                case 's':
                    y++;
                case 'S':
                    player.facingy=1;
                    player.facingx=0;
                    break;
                case 'w':
                    y--;
                case 'W':
                    player.facingy=-1;
                    player.facingx=0;
                    break;
                case ' ':
                    player.facingx=player.facingy=0;
                    break;
                case 'l':
                case 'L':
                    if(hasdroppeditem(player.c.x+player.facingx,player.c.y+player.facingy)){
                        pickupitem(player.c.x+player.facingx,player.c.y+player.facingy);
                        stuffpertick();
                    };
                    break;
                case 'j':
                case 'J':
                    switch(gethelditemdata().type){
                        case ITEM_TYPE_PICKAXE:
                            mineblock();
                            break;
                        case ITEM_TYPE_PLACABLE:
                            placeblock();
                            stuffpertick();
                            break;
                        case ITEM_TYPE_WEAPON:
                            playerattack();
                            break;
                        case ITEM_TYPE_MAGIC_MIRROR:
                            gotospawn();
                            stuffpertick();
                            break;
                    };
                    break;
                case 'i':
                case 'I':
                    inventory();
                    break;
                case '0' ... '9':
                    if (k=='0'){
                        k='9'+1;
                    };
                    player.holding=k-'1';
                    break;
                case 'c':
                case 'C':
                    craft();
                    break;
                case 'p':
                case 'P':
                case '\e':
                    if(pause()){
                        goto lbl_start;
                    };
                    clear();
                    break;
            };
            if(x || y) moveplayer(x,y);
        };
        if(player.hp<=0){
            die();
            goto lbl_start;
        };
        if(SETTINGS.autopickup){
            if(hasdroppeditem(player.c.x,player.c.y)){
                pickupitem(player.c.x, player.c.y);
            };
        };
        tick=TICK;
    };
    //lbl_end:
};
