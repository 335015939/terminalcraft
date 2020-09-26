#ifndef ENUM_H_INCLUDED
#define ENUM_H_INCLUDED
enum _EQUIPMENT_IDS {
    EQUIPMENT_NONE=0,EQUIPMENT_WOOD_HEMLET,EQUIPMENT_WOOD_BREASTPLATE,EQUIPMENT_SNAKE_SKIN_CLOAK,EQUIPMENT_BATWINGS,
    EQUIPMENT_COPPER_HELMET,EQUIPMENT_COPPER_BREASTPLATE,EQUIPMENT_COPPER_GREAVES,EQUIPMENT_COPPER_BOOTS
};
enum _ENTITY_IDS {
    ENTITY_NONE=0,ENTITY_SNAKE,ENTITY_BAT,ENTITY_ZOMBIE
};
enum _COLOR_PAIRS {
    CP_ITEM_NONE=0,CP_TILE_DIRT=1,CP_TILE_AIR,CP_TILE_STONE,CP_TILE_GRASS,CP_PLAYER,CP_TILE_OAK_LEAF,CP_TILE_OAK_TRUNK,
    CP_ITEM_DIRT,CP_ITEM_APPLE,CP_ITEM_WOOD,CP_ITEM_DOOR=CP_ITEM_WOOD,CP_ITEM_WOOD_HELMET=CP_ITEM_WOOD,
    CP_ITEM_WOOD_BREASTPLATE=CP_ITEM_WOOD,
    CP_ITEM_STONE,CP_ITEM_WOOD_PICKAXE,CP_TILE_PINE_TRUNK,CP_TILE_PINE_LEAF,
    CP_ITEM_COAL,CP_ITEM_IRON_ORE,CP_ITEM_SILVER_ORE,CP_ITEM_GOLD_ORE,CP_ITEM_DIAMOND_ORE,CP_ITEM_MYTHRIL_ORE,
    CP_TILE_COAL_ORE,CP_TILE_IRON_ORE,CP_TILE_SILVER_ORE,CP_TILE_GOLD_ORE,CP_TILE_DIAMOND_ORE,CP_TILE_MYTHRIL_ORE,
    CP_ITEM_COPPER_ORE,CP_ITEM_COPPER=CP_ITEM_COPPER_ORE,CP_ITEM_COPPER_SWORD=CP_ITEM_COPPER,
    CP_ITEM_COPPER_HELMET=CP_ITEM_COPPER,CP_ITEM_COPPER_BREASTPLATE=CP_ITEM_COPPER,CP_ITEM_COPPER_GREAVES=CP_ITEM_COPPER,
    CP_ITEM_COPPER_BOOTS=CP_ITEM_COPPER,CP_ITEM_COIN_COPPER=CP_ITEM_COPPER,
    CP_TILE_COPPER_ORE,CP_ITEM_IRON,CP_ITEM_WORKBENCH,CP_TILE_WORKBENCH,CP_TILE_WOOD,
    CP_TILE_FURNACE,CP_ITEM_FURNACE,CP_ITEM_COPPER_PICKAXE,CP_ITEM_IRON_PICKAXE,CP_ITEM_IRON_SWORD=CP_ITEM_IRON_PICKAXE,
    CP_ITEM_LADDER,CP_TILE_LADDER,CP_TILE_DOOR=CP_TILE_LADDER,
    CP_TILE_WOOD_WALL,CP_ITEM_WOOD_WALL,CP_ITEM_CHEST,CP_TILE_CHEST,CP_ITEM_MAGIC_MIRROR,
    CP_ITEM_SILVER,CP_ITEM_COIN_SILVER=CP_ITEM_SILVER,
    CP_ENTITY_BAT,CP_ENTITY_ZOMBIE,
    CP_ITEM_GOLD,CP_ITEM_COIN_GOLD=CP_ITEM_GOLD,
    CP_ITEM_WOOD_SWORD,CP_ENTITY_SNAKE,CP_ITEM_OAK_SAPLING,CP_TILE_OAK_SAPLING,CP_ITEM_PINE_SAPLING,
    CP_TILE_PINE_SAPLING,CP_ITEM_SNAKE_SKIN,CP_ITEM_SNAKE_SKIN_CLOAK=CP_ITEM_SNAKE_SKIN

};
enum _TILE_IDS {
    TILE_AIR=0,TILE_DIRT,TILE_STONE,TILE_GRASS,TILE_OAK_LEAF,TILE_OAK_TRUNK,TILE_PINE_TRUNK,TILE_PINE_LEAF,TILE_COAL_ORE,
    TILE_IRON_ORE,TILE_SILVER_ORE,TILE_GOLD_ORE,TILE_DIAMOND_ORE,TILE_COPPER_ORE,TILE_WORKBENCH,TILE_WOOD,TILE_FURNACE,
    TILE_LADDER,TILE_DOOR,TILE_WOOD_WALL,TILE_CHEST,TILE_OAK_SAPLING,TILE_PINE_SAPLING
};
enum _TREE_TYPE {
    TREE_OAK=0,TREE_PINE
};
enum _BODY_POSITIONS{
    BODY_HEAD=0,BODY_BODY,BODY_LEG,BODY_FEET,BODY_NECK,BODY_BACK,BODY_CLOAK,BODY_GLOVES,BODY_LHAND,BODY_WRIST
};
enum _ITEM_TYPES{
    ITEM_TYPE_NONE=0,ITEM_TYPE_PICKAXE,ITEM_TYPE_OTHER,ITEM_TYPE_FOOD,ITEM_TYPE_PLACABLE,ITEM_TYPE_WEAPON,
    ITEM_TYPE_MAGIC_MIRROR,ITEM_TYPE_EQUIPABLE,ITEM_TYPE_COIN
};
enum _ITEM_IDS {
    ITEM_NONE=0,ITEM_DIRT,ITEM_WOOD,ITEM_APPLE,ITEM_STONE,
    ITEM_WOOD_PICKAXE,ITEM_COAL,ITEM_IRON_ORE,
    ITEM_SILVER_ORE,ITEM_GOLD_ORE,ITEM_DIAMOND_ORE,ITEM_COPPER_ORE,ITEM_COPPER,ITEM_IRON,ITEM_WORKBENCH,
    ITEM_FURNACE,ITEM_COPPER_PICKAXE,ITEM_IRON_PICKAXE,ITEM_LADDER,ITEM_DOOR,ITEM_WOOD_WALL,ITEM_CHEST,
    ITEM_MAGIC_MIRROR,ITEM_SILVER,ITEM_GOLD,ITEM_WOOD_SWORD,ITEM_OAK_SAPLING,ITEM_PINE_SAPLING,ITEM_COPPER_SWORD,
    ITEM_IRON_SWORD,ITEM_WOOD_HELMET,ITEM_SNAKE_SKIN,ITEM_SNAKE_SKIN_CLOAK,ITEM_WOOD_BREASTEPLATE,ITEM_COPPER_HELMET,
    ITEM_COPPER_BREASTPLATE,ITEM_COPPER_GREAVES,ITEM_COPPER_BOOTS,ITEM_COIN_COPPER,ITEM_COIN_SILVER,ITEM_COIN_GOLD
};
enum _TILE_TYPES{
    TILE_TYPE_NONE,TILE_TYPE_WORKBENCH,TILE_TYPE_FURNACE,TILE_TYPE_CHEST,TILE_TYPE_OAK_SAPLING,TILE_TYPE_PINE_SAPLING,
    TILE_TYPE_BACKGROUND_WALL,TILE_TYPE_DOOR,TILE_TYPE_GRASS,TILE_TYPE_DIRT,TILE_TYPE_TREE_TRUNK,TILE_TYPE_LEAF,
    TILE_TYPE_LADDER
};
#endif