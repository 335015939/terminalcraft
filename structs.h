#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED
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
    TILE t;
    DROPITEMDATA drops;
    char *name;
} TILEDATA;
typedef struct {
    unsigned int _MAP_W;
    unsigned int _MAP_H;
    int skycolor;
} _SETTINGS;
typedef struct {
    int id;

} MAPTILE;
typedef struct {
    MAPTILE **map;
    int time;
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
} PLAYER;
typedef struct {
    int id;
    int maxstack;
    TILE t;
    char *name;
}ITEMDATA;
#endif