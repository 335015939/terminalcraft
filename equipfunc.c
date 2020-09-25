#include "enum.h"
#include "header.h"
#include "structs.h"
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
};
char unequipitem(int part){
    const int zero=0;
    if(!invadditem((ITEM){(*bodypart[part].id),1})){
        return 0;
    }else{
        *bodypart[part].id=0;
        return 1;
    };
};
char equipitem(ITEM item,int part){
    if(ITEMS[item.id].equipid){
        if(unequipitem(part)){
            *bodypart[part].id=item.id;
            return 1;
        };
    };
    return 0;
};
void equipdraw(){
    clear();
    int i;
    addstr("Equipment\n\n");
    for(i=0;i<BODY_PARTS;i++){
        printw("%s:%s\n",bodypart[i].name,ITEMS[(int)(*bodypart[i].id)].name);
    };
};
void equip(){
    for(;;){
        equipdraw();
        switch(getch()){
            case 'q':
            case 'Q':
                goto lbl_end;

        };
    };
    lbl_end:
    reloadstats();
    clear();
};