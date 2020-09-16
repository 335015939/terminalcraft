#ifndef VARS_DEF_H_INCLUDED
#define VARS_DEF_H_INCLUDED
#include <curses.h>
#define VARS_H_INCLUDED
#include "defines.h"
#include "structs.h"
#include "enum.h"

const COLOR_PAIR_DEF MY_COLOR_PAIRS[COLOR_NUM]={
    {CP_TILE_DIRT,0x5e,0x5e},
    {CP_TILE_AIR,0x0,0x0},
    {CP_TILE_STONE,0xf0,0xf0},
    {CP_TILE_GRASS,0x2e,0x00},
    {CP_TILE_OAK_LEAF,0x22,0x2e},
    {CP_TILE_OAK_TRUNK,0x5e,0x3a}
};
const TILEDATA TILES[TILE_NUM]={
    {
        TILE_AIR,1,0,0,1,//id,passable,minable,droppable(falling down),playerwill fall through
        {' ',A_NORMAL,0x0,CP_TILE_AIR},//char,attribute,background,color pair
        {//dropped items
            {},//id
            {},//low
            {},//max
            {}//chance
        },
        "Air"},
    {
        TILE_DIRT,0,1,0,0,
        {' ',A_NORMAL,0x5e,CP_TILE_DIRT},
        {},
        "Dirt"},
    {
        TILE_STONE,0,1,0,0,
        {' ',A_NORMAL,0xf0,CP_TILE_STONE},
        {},
        "Stone"},
    {
        TILE_GRASS,1,1,0,1,
        {'_',A_UNDERLINE,0x0,CP_TILE_GRASS},
        {},
        "Grass"},
    {
        TILE_OAK_LEAF,1,1,0,1,
        {'#',A_BOLD,0x22,CP_TILE_OAK_LEAF},
        {},
        "Oak leaves"},
    {
        TILE_OAK_TRUNK,1,1,0,0,
        {'|',A_BOLD,0x3a,CP_TILE_OAK_TRUNK},
        {},
        "Oak tree trunk"}

};
#endif