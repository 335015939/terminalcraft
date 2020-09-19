#ifndef ENUM_H_INCLUDED
#define ENUM_H_INCLUDED
enum _COLOR_PAIRS {
    CP_ITEM_NONE=0,CP_TILE_DIRT=1,CP_TILE_AIR,CP_TILE_STONE,CP_TILE_GRASS,CP_PLAYER,CP_TILE_OAK_LEAF,CP_TILE_OAK_TRUNK,
    CP_ITEM_DIRT,CP_ITEM_APPLE,CP_ITEM_OAK_WOOD,CP_ITEM_STONE,CP_ITEM_WOOD_PICKAXE
};
enum _TILE_IDS {
    TILE_AIR=0,TILE_DIRT,TILE_STONE,TILE_GRASS,TILE_OAK_LEAF,TILE_OAK_TRUNK
};
enum _TREE_TYPE {
    TREE_OAK,
};
enum _ITEM_TYPES{
    ITEM_TYPE_NONE=0,ITEM_TYPE_PICKAXE,ITEM_TYPE_OTHER,ITEM_TYPE_FOOD,ITEM_TYPE_PLACABLE
};
enum _ITEM_IDS {
    ITEM_NONE=0,ITEM_DIRT,ITEM_OAK_WOOD,ITEM_APPLE,ITEM_STONE,ITEM_WOOD_PICKAXE
};
#endif