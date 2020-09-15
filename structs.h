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
    TILE t;
    DROPITEMDATA drops;
} TILEDATA;
typedef struct {
    unsigned int _MAP_H;
    unsigned int _MAP_W;
    int skycolor;
} _SETTINGS;
typedef struct {
    int id;

} MAPTILE;
#endif