#ifndef ENUM_H_INCLUDED
#define ENUM_H_INCLUDED
enum _COLOR_PAIRS {
    CP_ITEM_NONE=0,CP_TILE_DIRT=1,CP_TILE_AIR,CP_TILE_STONE,CP_TILE_GRASS,CP_PLAYER,CP_TILE_OAK_LEAF,CP_TILE_OAK_TRUNK,
    CP_ITEM_DIRT,CP_ITEM_APPLE,CP_ITEM_WOOD,CP_ITEM_STONE,CP_ITEM_WOOD_PICKAXE,CP_TILE_PINE_TRUNK,CP_TILE_PINE_LEAF,
    CP_ITEM_COAL,CP_ITEM_IRON_ORE,CP_ITEM_SILVER_ORE,CP_ITEM_GOLD_ORE,CP_ITEM_DIAMOND_ORE,CP_ITEM_MYTHRIL_ORE,
    CP_TILE_COAL_ORE,CP_TILE_IRON_ORE,CP_TILE_SILVER_ORE,CP_TILE_GOLD_ORE,CP_TILE_DIAMOND_ORE,CP_TILE_MYTHRIL_ORE,
    CP_ITEM_COPPER_ORE,CP_TILE_COPPER_ORE,CP_ITEM_COPPER,CP_ITEM_IRON,CP_ITEM_WORKBENCH,CP_TILE_WORKBENCH,CP_TILE_WOOD,
    CP_TILE_FURNACE,CP_ITEM_FURNACE,CP_ITEM_COPPER_PICKAXE,CP_ITEM_IRON_PICKAXE,CP_ITEM_LADDER,CP_TILE_LADDER,CP_ITEM_DOOR,
    CP_TILE_DOOR,CP_TILE_WOOD_WALL,CP_ITEM_WOOD_WALL,CP_ITEM_CHEST,CP_TILE_CHEST,CP_ITEM_MAGIC_MIRROR

};
enum _TILE_IDS {
    TILE_AIR=0,TILE_DIRT,TILE_STONE,TILE_GRASS,TILE_OAK_LEAF,TILE_OAK_TRUNK,TILE_PINE_TRUNK,TILE_PINE_LEAF,TILE_COAL_ORE,
    TILE_IRON_ORE,TILE_SILVER_ORE,TILE_GOLD_ORE,TILE_DIAMOND_ORE,TILE_COPPER_ORE,TILE_WORKBENCH,TILE_WOOD,TILE_FURNACE,
    TILE_LADDER,TILE_DOOR,TILE_WOOD_WALL,TILE_CHEST
};
enum _TREE_TYPE {
    TREE_OAK=0,TREE_PINE
};
enum _ITEM_TYPES{
    ITEM_TYPE_NONE=0,ITEM_TYPE_PICKAXE,ITEM_TYPE_OTHER,ITEM_TYPE_FOOD,ITEM_TYPE_PLACABLE,ITEM_TYPE_WEAPON,
    ITEM_TYPE_MAGIC_MIRROR
};
enum _ITEM_IDS {
    ITEM_NONE=0,ITEM_DIRT,ITEM_WOOD,ITEM_APPLE,ITEM_STONE,ITEM_WOOD_PICKAXE,ITEM_COAL,ITEM_IRON_ORE,
    ITEM_SILVER_ORE,ITEM_GOLD_ORE,ITEM_DIAMOND_ORE,ITEM_COPPER_ORE,ITEM_COPPER,ITEM_IRON,ITEM_WORKBENCH,
    ITEM_FURNACE,ITEM_COPPER_PICKAXE,ITEM_IRON_PICKAXE,ITEM_LADDER,ITEM_DOOR,ITEM_WOOD_WALL,ITEM_CHEST,
    ITEM_MAGIC_MIRROR
};
enum _TILE_TYPES{
    TILE_TYPE_NONE,TILE_TYPE_WORKBENCH,TILE_TYPE_FURNACE,TILE_TYPE_CHEST,TILE_TYPE_OAK_SAPLING,TILE_TYPE_PINE_SAPLING,
    TILE_TYPE_BACKGROUND_WALL,TILE_TYPE_DOOR,TILE_TYPE_GRASS,TILE_TYPE_DIRT,TILE_TYPE_TREE_TRUNK,TILE_TYPE_LEAF
};
#endif