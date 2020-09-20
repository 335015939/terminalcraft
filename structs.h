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
} _SETTINGS;
typedef struct {
    int id;

} MAPTILE;
typedef struct {
    MAPTILE *map;
    int tick;
    int widht;
    int height;
} _WORLD;
typedef struct{
    int x;
    int y;
} COORDS;
typedef struct{
    COORDS c;
    char facingx;
    char facingy;
    ITEM i[10][10];
    int holding;
    int recipies_found[CRAFT_RECIPIE_NUM];
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
#endif