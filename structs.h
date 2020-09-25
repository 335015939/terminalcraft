#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED
#include "defines.h"
typedef struct {
    int id;
    int f;
    int b;
}COLOR_PAIR_DEF;
typedef struct {
    int id;
    int num;
} ITEM;
typedef struct {
    int id[5];
    int low[5];
    int max[5];
    int chance[5];
}DROPITEMDATA;
typedef struct {
    int c;
    int a;
    int b;
    int cp;
} TILE;
typedef struct {
    int id;
    char passable;
    char minable;
    char droppable;
    char fallthrough;
    char placeover;
    int hardlvl;
    int hardness;
    int type;
    TILE t;
    DROPITEMDATA drops;
    char *name;
} TILEDATA;
typedef struct {
    unsigned int _MAP_W;
    unsigned int _MAP_H;
    int skycolor;
    int oldskycolor;
    char autosave;
    char debugmode;
} _SETTINGS;
typedef struct {
    int id;
    int hp;
} ENTITY;
typedef struct {
    int id;
    ITEM storage[10][10];
    ITEM dropped[5];
    ENTITY e;
} MAPTILE;
typedef struct {
    MAPTILE *map;
    int tick;
    int width;
    int height;
    int spawnx;
    int spawny;
    int entitiesinworld;
} _WORLD;
typedef struct{
    int x;
    int y;
} COORDS;
typedef struct {
    int headid;//armor
    int bodyid;
    int legid;

    int neckid;//random stuff
    int backid;
    int cloakid;
    int feetid;
    int gloveid;
    int lhandid;
    int wristid;
} EQUIPDATA;
typedef struct{
    int id;
    int itemid;
    int position;
    char canfly;
    char falldmg;
    int dmgmulti;
    int defmulti;
    int regenmulti;
    int maxhpmulti;
    int dmgplus;
    int defplus;
    int regenplus;
    int maxhpplus;
} EQUIPMENTDATA;
typedef struct{
    COORDS c;
    char facingx;
    char facingy;
    int holding;
    int hp;
    
    int recipies_found[CRAFT_RECIPIE_NUM];

    ITEM i[10][10];
    EQUIPDATA eqiup;
    
    int dmgmulti;//stats from equipped stuff
    int defmulti;
    int regenmulti;
    int maxhpmulti;
    int dmgplus;
    int defplus;
    int regenplus;
    int maxhpplus;

    int basedef;//base stats
    int basedmg;
    int baseregen;
    int basemaxhp;

    char canfly;//attributes
    char falldmg;
} PLAYER;
typedef struct {
    int id;
    int maxstack;
    int type;
    int placetileid;
    int minepower;
    int minelvl;
    int damage;
    TILE t;
    char *name;
    int equipid;
}ITEMDATA;
typedef struct {
    ITEM result;
    int ingredient_num;
    ITEM ingredients[5];
    int station;
} _CRAFT_RECIPIE;
typedef struct {
    int x;
    int y;
    char found;
} INV_SEARCH;
typedef struct {
    int id;
    TILE t;
    DROPITEMDATA d;
} ENTITY_DEF;
#endif