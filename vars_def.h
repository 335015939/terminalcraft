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
    {CP_TILE_OAK_TRUNK,0x5e,0x3a},
    {CP_ITEM_DIRT,0x5e,0x10},
    {CP_ITEM_NONE,0x10,0x10},
    {CP_ITEM_OAK_WOOD,0x5e,0x10},
    {CP_ITEM_APPLE,0xc4,0x10},
    {CP_ITEM_STONE,0xf0,0x10},
    {CP_ITEM_WOOD_PICKAXE,0x5e,0x10}
};
const TILEDATA TILES[TILE_NUM]={
    {
        TILE_AIR,1,0,0,1,1,//id,passable,minable,droppable(falling down),playerwill fall through, can be placed over
        {' ',A_NORMAL,0x0,CP_TILE_AIR},//char,attribute,background,color pair
        {//dropped items
            {},//id
            {},//low
            {},//max
            {}//chance
        },
        "Air"},
    {
        TILE_DIRT,0,1,0,0,0,
        {' ',A_NORMAL,0x5e,CP_TILE_DIRT},
        {
            {ITEM_DIRT,},
            {1},
            {1},
            {100}
        },
        "Dirt"},
    {
        TILE_STONE,0,1,0,0,0,
        {' ',A_NORMAL,0xf0,CP_TILE_STONE},
        {
            {ITEM_STONE},
            {1},
            {1},
            {100}
        },
        "Stone"},
    {
        TILE_GRASS,1,1,0,1,1,
        {'_',A_UNDERLINE,0x0,CP_TILE_GRASS},
        {},
        "Grass"},
    {
        TILE_OAK_LEAF,1,1,0,1,1,
        {'#',A_BOLD,0x2e,CP_TILE_OAK_LEAF},
        {
            {ITEM_APPLE},
            {1},
            {2},
            {5}
        },
        "Oak leaves"},
    {
        TILE_OAK_TRUNK,1,1,0,0,0,
        {'|',A_BOLD,0x3a,CP_TILE_OAK_TRUNK},
        {
            {ITEM_OAK_WOOD},
            {1},
            {1},
            {100}
        },
        "Oak tree trunk"}

};
const ITEMDATA ITEMS[ITEMNUM]={
    {
        ITEM_NONE,0,ITEM_TYPE_NONE,TILE_AIR,//id,maxstack,item type,tile when placed
        {' ',0x0,CP_ITEM_NONE},//char,attribute,background,color pair
        "Nothing"},//name
    {
        ITEM_DIRT,99,ITEM_TYPE_PLACABLE,TILE_DIRT,
        {'O',A_BOLD,0x0,CP_ITEM_DIRT},
        "Dirt"},
    {
        ITEM_OAK_WOOD,99,ITEM_TYPE_PLACABLE,TILE_OAK_TRUNK,
        {'=',A_BOLD,0x0,CP_ITEM_OAK_WOOD},
        "Oak wood"},
    {
        ITEM_APPLE,99,ITEM_TYPE_FOOD,TILE_AIR,
        {'o',A_BOLD,0x0,CP_ITEM_APPLE},
        "Apple"},
    {
        ITEM_STONE,99,ITEM_TYPE_PLACABLE,TILE_STONE,
        {'O',A_BOLD,0x0,CP_ITEM_STONE},
        "Stone"},
    {  
        ITEM_WOOD_PICKAXE,1,ITEM_TYPE_PICKAXE,TILE_AIR,
        {'T',A_BOLD,0x0,CP_ITEM_WOOD_PICKAXE},
        "Wood Pickaxe"},
};
#endif