#ifndef VARS_H_INCLUDED
#define VARS_H_INCLUDED
#include "structs.h"
#include "defines.h"
extern const COLOR_PAIR_DEF MY_COLOR_PAIRS[COLOR_NUM];
extern const TILEDATA TILES[TILE_NUM];
extern _SETTINGS SETTINGS;
extern _WORLD WORLD;
extern const EQUIPMENTDATA EQUIPMENT[];
extern PLAYER player;
extern const ITEMDATA ITEMS[ITEMNUM];
extern const unsigned char SPIN[4];
extern int CURRENT_STATION;
extern const _CRAFT_RECIPIE CRAFT_RECIPIE[CRAFT_RECIPIE_NUM];
extern int CHOSEN_WORLD;
extern int CHOSEN_PLAYER;
extern COORDS *entityxy;
extern const ENTITY_DEF ENTITIES[ENTITY_NUM];
extern char *GOT_HIT_MSG;
extern char *HIT_MSG;
#endif