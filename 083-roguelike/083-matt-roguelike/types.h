#ifndef TYPES_H
#define TYPES_H

typedef struct pt {
    int16_t x, y;
} Point;

/**Objects*/

enum OBJ_TYPE {NO_OBJ, GOLD, WEAPON, POTION, ARMOR, NUM_OBJ_TYPES};
enum EFFECTS {PRAND, NO_EFF, HEAL, EXP, WBUFF, TELE, ABUFF, FHEAL, NUM_EFFECTS};
enum MATERIALS {IRON, STEEL, ADAMANTINE, NUM_MATERIALS};

typedef struct Object {
    enum OBJ_TYPE type;
    char name[30];

    union {
        struct gold {
            uint16_t amount;
        } gold;

        struct weapon {
            uint8_t dmg;
            enum MATERIALS mat;
        } weapon;

        struct potion {
            enum EFFECTS eff;
        } potion;

        struct armor {
            uint8_t prot_fact;
            enum MATERIALS mat;
        } armor;
    } obj;
} Object;

/**Map*/
enum TILE_TYPE {EMPTY, WALL, FLOOR, DOOR, STAIR, NUM_TILE_TYPES};

#define MAP_SIZE_Y 25
#define MAP_SIZE_X 80

typedef struct tile{
    uint8_t vis;
    enum TILE_TYPE type;
    Object obj;
} Tile;

typedef struct Map{
    Tile map[MAP_SIZE_Y][MAP_SIZE_X];
    uint8_t current_floor;
} Map;

/**Mobs*/

#define MIN_MOBS    3
#define MAX_MOBS    8

enum MOB_TYPES {NO_MOB, RAT, KOBOLD, CRAB, DINGO, SNAKE, GOBLIN, ZOMBIE, SKELETON, OGRE, LIZPRSN, TROLL, CENTAUR, MINOTAUR, DEMON, NUM_MOB_TYPES};
enum MOB_STATE {STILL, RAND, AGGRO};

typedef struct mob {
    enum MOB_TYPES type;
    enum MOB_STATE state;
    char* name;
    uint16_t exp;
    int16_t hp;
    uint8_t dmg;
    Point* pos;
} Mob;

/**Player*/
#define MAX_ITEMS_INV 10

typedef struct Player {
    Object inv[MAX_ITEMS_INV];
    uint8_t num_items_inventory;

    uint8_t alive;
    int16_t hp;
    uint16_t gold;
    uint16_t maxhp;
    uint16_t level;
    uint16_t exp;
    uint16_t dmg;

    Object* armor;
    Object* weapon;

    Point* pos;
} Player;

/**Game*/
typedef struct Game{
    Map map;
    Mob** mobList;
    int8_t num_mobs;
    Player* pl;
} Game;


#endif // TYPES_H
