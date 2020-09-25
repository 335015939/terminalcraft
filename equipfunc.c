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
    {"Head",&player.eqiup.headid},
    {"Torso",&player.eqiup.bodyid},
    {"Legs",&player.eqiup.legid},
    {"Feet",&player.eqiup.feetid},
    {"Neck",&player.eqiup.neckid},
    {"Back",&player.eqiup.backid},
    {"Cloak",&player.eqiup.cloakid},
    {"Gloves",&player.eqiup.gloveid},
    {"Left Hand",&player.eqiup.lhandid},
    {"Wrist",&player.eqiup.wristid},
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
            return 1;
        };
    };
    return 0;
};
unsigned char CURRENT_ATTR_TO_DRAW=0;
void drawattr(int x){
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
    int values[8]={
        EQUIPMENT[*bodypart[x].id].defmulti,
        EQUIPMENT[*bodypart[x].id].dmgmulti,
        EQUIPMENT[*bodypart[x].id].regenmulti,
        EQUIPMENT[*bodypart[x].id].maxhpmulti,
        EQUIPMENT[*bodypart[x].id].defplus,
        EQUIPMENT[*bodypart[x].id].dmgplus,
        EQUIPMENT[*bodypart[x].id].regenplus,
        EQUIPMENT[*bodypart[x].id].maxhpplus,
    };
    const char ismultiplier[]={1,1,1,1,0,0,0,0};
    if(ismultiplier[x]){
        str="%s multiplier:+%d%%";
    }else{
        str="%s:%d";
    };
    //if(values[x]){
        mvprintw(CURRENT_ATTR_TO_DRAW+2,20,str,names[x],values[x]);printw("  %d",*bodypart[x].id);
        CURRENT_ATTR_TO_DRAW++;
    //};
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
        drawattr(i);
    };
    attron(A_REVERSE);
    mvprintw(x+2,0,"%s:%s",bodypart[x].name,ITEMS[(int)(EQUIPMENT[*bodypart[i].id].itemid)].name);
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