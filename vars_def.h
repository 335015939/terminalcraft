#ifndef VARS_DEF_H_INCLUDED
#define VARS_DEF_H_INCLUDED
#include <curses.h>
#define VARS_H_INCLUDED
#include "defines.h"
#include "structs.h"
#include "enum.h"
const unsigned char SPIN[4]={'|','/','-','\''};
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
    {CP_ITEM_WOOD_PICKAXE,0x5e,0x10},
    {CP_TILE_PINE_LEAF,0x16,0x1c},
    {CP_TILE_PINE_TRUNK,0x5f,0x3a},
    {CP_ITEM_COAL,0xe9,0x10},
    {CP_TILE_COAL_ORE,0x10,0xf0},
    {CP_ITEM_IRON_ORE,0xdf,0x10},
    {CP_TILE_IRON_ORE,0xdf,0xf0},
    {CP_ITEM_SILVER_ORE,0xfe,0x10},
    {CP_TILE_SILVER_ORE,0xfe,0xf0},
    {CP_ITEM_GOLD_ORE,0x03,0x10},
    {CP_TILE_GOLD_ORE,0x03,0xf0},
    {CP_ITEM_DIAMOND_ORE,0x06,0x10},
    {CP_TILE_DIAMOND_ORE,0x06,0xf0},
    {CP_ITEM_COPPER_ORE,0x82,0x10},
    {CP_TILE_COPPER_ORE,0x82,0xf0}

};
const TILEDATA TILES[TILE_NUM]={
    {
        TILE_AIR,1,0,0,1,1,//id,passable,minable,droppable(falling down),playerwill fall through, can be placed over
        0,0,//hardness level, hardness
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
        1,3,
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
        1,10,
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
        1,1,
        {'_',A_UNDERLINE,0x0,CP_TILE_GRASS},
        {},
        "Grass"},
    {
        TILE_OAK_LEAF,1,1,0,1,1,
        1,1,
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
        1,4,
        {'|',A_BOLD,0x3a,CP_TILE_OAK_TRUNK},
        {
            {ITEM_OAK_WOOD},
            {1},
            {1},
            {100}
        },
        "Oak tree trunk"},
    {
        TILE_PINE_TRUNK,1,1,0,0,0,
        1,4,
        {'|',A_BOLD,0x3a,CP_TILE_PINE_TRUNK},
        {},
        "Pine tree trunk"},
    {
        TILE_PINE_LEAF,1,1,0,1,1,
        1,1,
        {'=',A_BOLD,0x1c,CP_TILE_PINE_LEAF},
        {},
        "Pine tree needles"},
    {
        TILE_COAL_ORE,0,1,0,0,0,
        1,12,
        {'#',A_BOLD,0xf0,CP_TILE_COAL_ORE},
        {
            {ITEM_COAL},
            {1},
            {3},
            {100},
        },
        "Coal Ore"},
    {
        TILE_IRON_ORE,0,1,0,0,0,
        2,16,
        {'#',A_BOLD,0xf0,CP_TILE_IRON_ORE},
        {
            {ITEM_IRON_ORE},
            {1},
            {1},
            {100},
        },
        "Iron Ore"},
    {
        TILE_SILVER_ORE,0,1,0,0,0,
        2,20,
        {'#',A_BOLD,0xf0,CP_TILE_SILVER_ORE},
        {
            {ITEM_SILVER_ORE},
            {1},
            {1},
            {100}
        },
        "Silver Ore"},
    {
        TILE_GOLD_ORE,0,1,0,0,0,
        2,19,
        {'~',A_BOLD,0xf0,CP_TILE_GOLD_ORE},
        {
            {ITEM_GOLD_ORE},
            {1},
            {1},
            {100}
        },
        "Gold Ore"},
    {
        TILE_DIAMOND_ORE,0,1,0,0,0,
        3,30,
        {':',A_BOLD,0xf0,CP_TILE_DIAMOND_ORE},
        {
            {ITEM_DIAMOND_ORE},
            {1},
            {1},
            {100}
        },
        "Diamond Ore"},
    {
        TILE_COPPER_ORE,0,1,0,0,0,
        1,14,
        {'#',A_BOLD,0xf0,CP_TILE_COPPER_ORE},
        {
            {ITEM_COPPER_ORE},
            {1},
            {1},
            {100}
        },
        "Copper Ore"},
};
const ITEMDATA ITEMS[ITEMNUM]={
    {
        ITEM_NONE,0,ITEM_TYPE_NONE,//id,maxstack,item type
        TILE_AIR,0,0,0,//tile when placed,mine power, mine level, damage
        {' ',0x0,CP_ITEM_NONE},//char,attribute,background,color pair
        "Nothing"},//name
    {
        ITEM_DIRT,99,ITEM_TYPE_PLACABLE,
        TILE_DIRT,0,0,0,
        {'O',A_BOLD,0x0,CP_ITEM_DIRT},
        "Dirt"},
    {
        ITEM_OAK_WOOD,99,ITEM_TYPE_PLACABLE,
        TILE_OAK_TRUNK,0,0,0,
        {'=',A_BOLD,0x0,CP_ITEM_OAK_WOOD},
        "Oak wood"},
    {
        ITEM_APPLE,99,ITEM_TYPE_FOOD,
        TILE_AIR,0,0,0,
        {'o',A_BOLD,0x0,CP_ITEM_APPLE},
        "Apple"},
    {
        ITEM_STONE,99,ITEM_TYPE_PLACABLE,
        TILE_STONE,0,0,0,
        {'O',A_BOLD,0x0,CP_ITEM_STONE},
        "Stone"},
    {  
        ITEM_WOOD_PICKAXE,1,ITEM_TYPE_PICKAXE,
        TILE_AIR,999,999,0,
        {'T',A_BOLD,0x0,CP_ITEM_WOOD_PICKAXE},
        "Wood Pickaxe"},
    {
        ITEM_COAL,99,ITEM_TYPE_OTHER,
        TILE_AIR,0,0,0,
        {'o',0x0,CP_ITEM_COAL},
        "Coal"},
    {
        ITEM_IRON_ORE,99,ITEM_TYPE_PLACABLE,
        TILE_IRON_ORE,0,0,0,
        {'#',0x0,CP_TILE_IRON_ORE},
        "Iron Ore"},
    {
        ITEM_SILVER_ORE,99,ITEM_TYPE_PLACABLE,
        TILE_SILVER_ORE,0,0,0,
        {' ',0x0,CP_ITEM_SILVER_ORE},
        "Silver Ore"},
    {
        ITEM_GOLD_ORE,99,ITEM_GOLD_ORE,
        TILE_GOLD_ORE,0,0,0,
        {'~',0x0,CP_ITEM_GOLD_ORE},
        "Gold Ore"},
    {
        ITEM_DIAMOND_ORE,99,ITEM_TYPE_PLACABLE,
        TILE_DIAMOND_ORE,0,0,0,
        {':',0x0,CP_ITEM_DIAMOND_ORE},
        "Diamond Ore"},
    {
        ITEM_COPPER_ORE,99,ITEM_TYPE_PLACABLE,
        TILE_COPPER_ORE,0,0,0,
        {'#',0x0,CP_ITEM_COPPER_ORE},
        "Copper Ore"},
};
#endif