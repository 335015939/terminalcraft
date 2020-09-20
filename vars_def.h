#ifndef VARS_DEF_H_INCLUDED
#define VARS_DEF_H_INCLUDED
#include <curses.h>
#define VARS_H_INCLUDED
#include "defines.h"
#include "structs.h"
#include "enum.h"
const unsigned char SPIN[4]={'|','/','-','\\'};
const _CRAFT_RECIPIE CRAFT_RECIPIE[CRAFT_RECIPIE_NUM]={
    {
        {ITEM_COPPER,1},//result after crafting
        2,//number of different items needed
        {//list of items (less than 5)
            {ITEM_COPPER_ORE,2},
            {ITEM_COAL,2},
        },
        TILE_TYPE_FURNACE},//crafting station needed
    {
        {ITEM_IRON,1},
        2,
        {
            {ITEM_IRON_ORE,2},
            {ITEM_COAL,2},
        },
        TILE_TYPE_NONE},
    {
        {ITEM_WORKBENCH,1},
        1,
        {
            {ITEM_WOOD,4}
        },
        TILE_TYPE_NONE},
    {
        {ITEM_FURNACE,1},
        1,
        {
            {ITEM_STONE,10},
        },
        TILE_TYPE_WORKBENCH},
    {
        {ITEM_COPPER_PICKAXE,1},
        2,
        {
            {ITEM_COPPER,3},
            {ITEM_WOOD,1}
        },
        TILE_TYPE_WORKBENCH},
    {
        {ITEM_IRON_PICKAXE,1},
        2,
        {
            {ITEM_IRON,3},
            {ITEM_WOOD,1}
        },
        TILE_TYPE_WORKBENCH},
    {
        {ITEM_LADDER,2},
        1,
        {
            {ITEM_WOOD,3}
        },
        TILE_TYPE_WORKBENCH},
    {
        {ITEM_DOOR,1},
        1,
        {
            {ITEM_WOOD,4}
        },
        TILE_TYPE_WORKBENCH},
    {
        {ITEM_WOOD_WALL,2},
        1,
        {
            {ITEM_WOOD,1}
        },
        TILE_TYPE_WORKBENCH},
    {
        {ITEM_CHEST,1},
        1,
        {
            {ITEM_WOOD,10}
        },
        TILE_TYPE_WORKBENCH},
};
const COLOR_PAIR_DEF MY_COLOR_PAIRS[COLOR_NUM]={
    {CP_TILE_DIRT,0x5e,0x5e},
    {CP_TILE_AIR,0x0,0x0},
    {CP_TILE_STONE,0xf0,0xf0},
    {CP_TILE_GRASS,0x2e,0x00},
    {CP_TILE_OAK_LEAF,0x22,0x2e},
    {CP_TILE_OAK_TRUNK,0x5e,0x3a},
    {CP_ITEM_DIRT,0x5e,0xe9},
    {CP_ITEM_NONE,-1,-1},
    {CP_ITEM_WOOD,0x5e,0xe9},
    {CP_ITEM_APPLE,0xc4,0xe9},
    {CP_ITEM_STONE,0xf0,0xe9},
    {CP_ITEM_WOOD_PICKAXE,0x5e,0xe9},
    {CP_TILE_PINE_LEAF,0x16,0x1c},
    {CP_TILE_PINE_TRUNK,0x5f,0x3a},
    {CP_ITEM_COAL,0xed,0xe9},
    {CP_TILE_COAL_ORE,0x10,0xf0},
    {CP_ITEM_IRON_ORE,0xdd,0xe9},
    {CP_TILE_IRON_ORE,0xdd,0xf0},
    {CP_ITEM_SILVER_ORE,0xfe,0xe9},
    {CP_TILE_SILVER_ORE,0xfe,0xf0},
    {CP_ITEM_GOLD_ORE,0x03,0xe9},
    {CP_TILE_GOLD_ORE,0x03,0xf0},
    {CP_ITEM_DIAMOND_ORE,0x06,0xe9},
    {CP_TILE_DIAMOND_ORE,0x06,0xf0},
    {CP_ITEM_COPPER_ORE,0xca,0xe9},
    {CP_TILE_COPPER_ORE,0xca,0xf0},
    {CP_ITEM_IRON,0xdf,0xe9},
    {CP_TILE_WORKBENCH,0x5e,0x0},
    {CP_ITEM_WORKBENCH,0x5e,0xe9},
    {CP_TILE_WOOD,0x5e,0x3a},
    {CP_TILE_FURNACE,0x01,0xf0},
    {CP_ITEM_FURNACE,0xf0,0xe9},
    {CP_ITEM_COPPER_PICKAXE,0xa6,0xe9},
    {CP_ITEM_IRON_PICKAXE,0xfe,0xe9},
    {CP_ITEM_LADDER,0x5e,0xe9},
    {CP_TILE_LADDER,0x5e,0x0},
    {CP_TILE_DOOR,0x5e,0x0},
    {CP_ITEM_DOOR,0x5e,0xe9},
    {CP_ITEM_WOOD_WALL,0x5e,0x3a},
    {CP_TILE_WOOD_WALL,0x3a,0x3a},
    {CP_TILE_CHEST,0x5e,0x3a},
    {CP_ITEM_CHEST,0x82,0x5e}
};
const TILEDATA TILES[TILE_NUM]={
    {
        TILE_AIR,1,0,0,1,1,//id,passable,minable,droppable(falling down),playerwill fall through, can be placed over
        0,0,TILE_TYPE_NONE,//hardness level, hardness, tile type
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
        1,12,TILE_TYPE_NONE,
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
        1,20,TILE_TYPE_NONE,
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
        1,1,TILE_TYPE_NONE,
        {'_',A_UNDERLINE,0x0,CP_TILE_GRASS},
        {},
        "Grass"},
    {
        TILE_OAK_LEAF,1,1,0,1,1,
        1,1,TILE_TYPE_NONE,
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
        1,12,TILE_TYPE_NONE,
        {'|',A_BOLD,0x3a,CP_TILE_OAK_TRUNK},
        {
            {ITEM_WOOD},
            {1},
            {1},
            {100}
        },
        "Oak tree trunk"},
    {
        TILE_PINE_TRUNK,1,1,0,0,0,
        1,12,TILE_TYPE_NONE,
        {'|',A_BOLD,0x3a,CP_TILE_PINE_TRUNK},
        {
            {ITEM_WOOD},
            {1},
            {1},
            {100}
        },
        "Pine tree trunk"},
    {
        TILE_PINE_LEAF,1,1,0,1,1,
        1,1,TILE_TYPE_NONE,
        {'=',A_BOLD,0x1c,CP_TILE_PINE_LEAF},
        {},
        "Pine tree needles"},
    {
        TILE_COAL_ORE,0,1,0,0,0,
        1,22,TILE_TYPE_NONE,
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
        2,32,TILE_TYPE_NONE,
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
        2,32,TILE_TYPE_NONE,
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
        2,40,TILE_TYPE_NONE,
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
        3,81,TILE_TYPE_NONE,
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
        1,24,TILE_TYPE_NONE,
        {'#',A_BOLD,0xf0,CP_TILE_COPPER_ORE},
        {
            {ITEM_COPPER_ORE},
            {1},
            {1},
            {100}
        },
        "Copper Ore"},
    {
        TILE_WORKBENCH,1,1,0,0,0,
        1,6,TILE_TYPE_WORKBENCH,
        {'n',A_BOLD,0x0,CP_TILE_WORKBENCH},
        {
            {ITEM_WORKBENCH},
            {1},
            {1},
            {100}
        },
        "Workbench"},
    {
        TILE_WOOD,0,1,0,0,0,
        1,11,TILE_TYPE_NONE,
        {'=',A_BOLD,0x5e,CP_TILE_WOOD},
        {
            {ITEM_WOOD},
            {1},
            {1},
            {100}
        },
        "Wood block"},
    {
        TILE_FURNACE,1,1,0,0,0,
        1,21,TILE_TYPE_FURNACE,
        {'o',A_BOLD,0xf0,CP_TILE_FURNACE},
        {
            {ITEM_FURNACE},
            {1},
            {1},
            {100}
        },
        "Furnace"},
    {
        TILE_LADDER,1,1,0,0,0,
        1,3,TILE_TYPE_NONE,
        {'#',A_BOLD,0x0,CP_TILE_LADDER},
        {
            {ITEM_LADDER},
            {1},
            {1},
            {100},
        },
        "Ladders"},
    {
        TILE_DOOR,1,1,0,0,0,
        1,6,TILE_TYPE_DOOR,
        {'|',A_BOLD,0x0,CP_TILE_DOOR},
        {
            {ITEM_DOOR},
            {1},
            {1},
            {100},
        },
        "Door"},
    {
        TILE_WOOD_WALL,1,1,0,1,0,
        1,1,TILE_TYPE_BACKGROUND_WALL,
        {' ',A_NORMAL,0x3a,CP_TILE_WOOD_WALL},
        {
            {ITEM_WOOD_WALL},
            {1},
            {1},
            {100},
        },
        "Wall"},
    {
        TILE_CHEST,1,1,0,0,0,
        1,12,TILE_TYPE_CHEST,
        {'^',A_BOLD,0x5e,CP_TILE_CHEST},
        {
            {ITEM_CHEST},
            {1},
            {1},
            {100},
        },
        "Chest"},
};
const ITEMDATA ITEMS[ITEMNUM]={
    {
        ITEM_NONE,0,ITEM_TYPE_NONE,//id,maxstack,item type
        TILE_AIR,0,0,0,//tile when placed,mine power, mine level, damage
        {' ',A_BOLD,0x0,CP_ITEM_NONE},//char,attribute,background,color pair
        "Nothing"},//name
    {
        ITEM_DIRT,99,ITEM_TYPE_PLACABLE,
        TILE_DIRT,0,0,0,
        {224,A_BOLD,0x0,CP_ITEM_DIRT},
        "Dirt"},
    {
        ITEM_WOOD,99,ITEM_TYPE_PLACABLE,
        TILE_WOOD,0,0,0,
        {'=',A_BOLD,0x0,CP_ITEM_WOOD},
        "Wood"},
    {
        ITEM_APPLE,99,ITEM_TYPE_FOOD,
        TILE_AIR,0,0,0,
        {'o',A_BOLD,0x0,CP_ITEM_APPLE},
        "Apple"},
    {
        ITEM_STONE,99,ITEM_TYPE_PLACABLE,
        TILE_STONE,0,0,0,
        {224,A_BOLD,0x0,CP_ITEM_STONE},
        "Stone"},
    {  
        ITEM_WOOD_PICKAXE,1,ITEM_TYPE_PICKAXE,
        TILE_AIR,1,1,0,
        {'T',A_BOLD,0x0,CP_ITEM_WOOD_PICKAXE},
        "Wood Pickaxe"},
    {
        ITEM_COAL,99,ITEM_TYPE_OTHER,
        TILE_AIR,0,0,0,
        {'o',A_BOLD,0x0,CP_ITEM_COAL},
        "Coal"},
    {
        ITEM_IRON_ORE,99,ITEM_TYPE_PLACABLE,
        TILE_IRON_ORE,0,0,0,
        {'#',A_NORMAL,0x0,CP_TILE_IRON_ORE},
        "Iron Ore"},
    {
        ITEM_SILVER_ORE,99,ITEM_TYPE_PLACABLE,
        TILE_SILVER_ORE,0,0,0,
        {'#',A_NORMAL,0x0,CP_ITEM_SILVER_ORE},
        "Silver Ore"},
    {
        ITEM_GOLD_ORE,99,ITEM_GOLD_ORE,
        TILE_GOLD_ORE,0,0,0,
        {'~',A_BOLD,0x0,CP_ITEM_GOLD_ORE},
        "Gold Ore"},
    {
        ITEM_DIAMOND_ORE,99,ITEM_TYPE_PLACABLE,
        TILE_DIAMOND_ORE,0,0,0,
        {':',A_BOLD,0x0,CP_ITEM_DIAMOND_ORE},
        "Diamond Ore"},
    {
        ITEM_COPPER_ORE,99,ITEM_TYPE_PLACABLE,
        TILE_COPPER_ORE,0,0,0,
        {'#',A_BOLD,0x0,CP_ITEM_COPPER_ORE},
        "Copper Ore"},
    {
        ITEM_COPPER,99,ITEM_TYPE_OTHER,
        TILE_AIR,0,0,0,
        {'-',A_BOLD,0x0,CP_ITEM_COPPER},
        "Copper Bar"},
    {
        ITEM_IRON,99,ITEM_TYPE_OTHER,
        TILE_AIR,0,0,0,
        {'-',A_BOLD,0x0,CP_ITEM_IRON},
        "Iron Bar"},
    {
        ITEM_WORKBENCH,9,ITEM_TYPE_PLACABLE,
        TILE_WORKBENCH,0,0,0,
        {'n',A_BOLD,0x0,CP_ITEM_WORKBENCH},
        "Workbench"},
    {
        ITEM_FURNACE,9,ITEM_TYPE_PLACABLE,
        TILE_FURNACE,0,0,0,
        {'o',A_BOLD,0x0,CP_ITEM_FURNACE},
        "Furnace"},
    {
        ITEM_COPPER_PICKAXE,1,ITEM_TYPE_PICKAXE,
        TILE_AIR,3,2,0,
        {'T',A_BOLD,0x0,CP_ITEM_COPPER_PICKAXE},
        "Copper pickaxe"},
    {
        ITEM_IRON_PICKAXE,1,ITEM_TYPE_PICKAXE,
        TILE_AIR,8,3,0,
        {'T',A_BOLD,0x0,CP_ITEM_IRON_PICKAXE},
        "Iron pckaxe"},
    {
        ITEM_LADDER,99,ITEM_TYPE_PLACABLE,
        TILE_LADDER,0,0,0,
        {'#',A_NORMAL,0x0,CP_ITEM_LADDER},
        "Ladders"},
    {
        ITEM_DOOR,4,ITEM_TYPE_PLACABLE,
        TILE_DOOR,0,0,0,
        {'|',A_NORMAL,0x0,CP_ITEM_DOOR},
        "Door"},
    {
        ITEM_WOOD_WALL,99,ITEM_TYPE_PLACABLE,
        TILE_WOOD_WALL,0,0,0,
        {'=',A_NORMAL,0x0,CP_ITEM_WOOD_WALL},
        "Wooden walls"},
    {
        ITEM_CHEST,99,ITEM_TYPE_PLACABLE,
        TILE_CHEST,0,0,0,
        {'^',A_NORMAL,0x0,CP_ITEM_CHEST},
        "Chest"},
};
#endif