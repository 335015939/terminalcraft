#include "enum.h"
#include "funcs.h"
#include "header.h"
#include "structs.h"
#include "vars.h"
#define BODY_PARTS 10
const struct{
    const char *name;
    int *id;
}bodypart[BODY_PARTS]={
    {"Head",&player.equip.headid},
    {"Torso",&player.equip.bodyid},
    {"Legs",&player.equip.legid},
    {"Feet",&player.equip.feetid},
    {"Neck",&player.equip.neckid},
    {"Back",&player.equip.backid},
    {"Cloak",&player.equip.cloakid},
    {"Gloves",&player.equip.gloveid},
    {"Left Hand",&player.equip.lhandid},
    {"Wrist",&player.equip.wristid},
};
void reloadstats(){
    int i;
    player.falldmg=1;
    player.canfly=0;
    player.dmgmulti=0;
    player.defmulti=0;
    player.regenmulti=0;
    player.maxhpmulti=0;
    player.dmgplus=0;
    player.defplus=0;
    player.regenplus=0;
    player.maxhpplus=0;
    EQUIPMENTDATA e; 
    for(i=0;i<BODY_PARTS;i++){
        e=EQUIPMENT[*bodypart[i].id];
        player.falldmg=player.falldmg && e.falldmg;
        player.canfly=player.canfly || e.canfly;
        player.dmgmulti+=e.dmgmulti;
        player.defmulti+=e.defmulti;
        player.regenmulti+=e.regenmulti;
        player.maxhpmulti+=e.maxhpmulti;
        player.dmgplus+=e.dmgplus;
        player.defplus+=e.defplus;
        player.regenplus+=e.regenplus;
        player.maxhpplus+=e.maxhpplus;
    };
    if(player.hp>getmaxhp()){
        player.hp=getmaxhp();
    };
};
char unequipitem(int part){
    if(!invadditem((ITEM){(EQUIPMENT[*bodypart[part].id].itemid),1})){
        return 0;
    }else{
        *bodypart[part].id=0;
        return 1;
    };
};
char equipitem(ITEM item){
    int x;
    if(!(x=ITEMS[item.id].equipid)) return 0;
    int part=EQUIPMENT[x].position;
    if(ITEMS[item.id].equipid){
        if(unequipitem(part)){
            *bodypart[part].id=x;
            reloadstats();
            return 1;
        };
    };
    return 0;
};
unsigned char CURRENT_ATTR_TO_DRAW=0;
void drawattr(int y,int x){
    const char* names[8]={
        "Defence",
        "Damage",
        "Regeneration",
        "Max health",
        "Defence",
        "Damage",
        "Regeneration",
        "Max health"
    };
    char *str;
    const int values[8]={
        EQUIPMENT[y].defmulti,
        EQUIPMENT[y].dmgmulti,
        EQUIPMENT[y].regenmulti,
        EQUIPMENT[y].maxhpmulti,
        EQUIPMENT[y].defplus,
        EQUIPMENT[y].dmgplus,
        EQUIPMENT[y].regenplus,
        EQUIPMENT[y].maxhpplus,
    };
    const char ismultiplier[]={1,1,1,1,0,0,0,0};
    if(ismultiplier[x]){
        str="%s multiplier:+%d%%";
    }else{
        str="%s:%d";
    };
    if(values[x]){
        mvprintw(CURRENT_ATTR_TO_DRAW+2,25,str,names[x],values[x]);
        CURRENT_ATTR_TO_DRAW++;
    };
};
void equipdraw(int x){
    clear();
    int i;
    CURRENT_ATTR_TO_DRAW=0;
    attr_set(0,0,NULL);
    addstr("Equipment\n\n");
    for(i=0;i<BODY_PARTS;i++){
        printw("%s:%s\n",bodypart[i].name,ITEMS[(int)(EQUIPMENT[*bodypart[i].id].itemid)].name);
    };
    for(i=0;i<8;i++){
        drawattr(*bodypart[x].id,i);
    };
    attron(A_REVERSE);
    mvprintw(x+2,0,"%s:%s",bodypart[x].name,ITEMS[(int)(EQUIPMENT[*bodypart[x].id].itemid)].name);
};
void equip(){
    static int selected=0;
    for(;;){
        equipdraw(selected);
        switch(getch()){
            case 'q':
            case 'Q':
                goto lbl_end;
            case 's':
            case 'S':
            case KEY_DOWN:
                selected +=(selected<(BODY_PARTS-1));
                break;
            case 'w':
            case 'W':
            case KEY_UP:
                selected-=(selected>0);
                break;
            case 'j':
            case 'J':
            case '\n':
                unequipitem(selected);
                break;
        };
    };
    lbl_end:
    reloadstats();
    clear();
};