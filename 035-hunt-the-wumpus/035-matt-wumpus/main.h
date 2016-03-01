/*main.h - Defines, types and function prototypes*/

#ifndef _MAIN_H
#define _MAIN_H

/*Defines*/
#define GRID_SIZE_X (15)
#define GRID_SIZE_Y (10)
#define PROB_MAX    (GRID_SIZE_X*GRID_SIZE_X*GRID_SIZE_Y*GRID_SIZE_Y) //max number of tries to get a random point

#define KEY_QUIT    'q'
#define KEY_SHOOT   'f'

#define NUM_PITS    (8)
#define NUM_BATS    (4)
#define NUM_ARR_OBJ (3) //number of arrows on the ground
#define NUM_ARR_PL  (5) //initial arrow count

//#define SEE_ALL       //uncomment to see hazards and items
#ifdef SEE_ALL
#define cEMPTY      '.'
#define cEXPLORED   '+'
#define cPLAYER     '@'
#define cWUMPUS     '#'
#define cPIT        'O'
#define cBAT        '^'
#define cARROW      '/'
#else
#define cEMPTY      '.'
#define cEXPLORED   '+'
#define cPLAYER     '@'
#define cWUMPUS     cEMPTY
#define cPIT        cEMPTY
#define cBAT        cEMPTY
#define cARROW      cEMPTY
#endif // SEE_ALL

typedef enum { UP, DOWN, LEFT, RIGHT, NUM_DIR } DIR;
typedef enum { NONE, EXPLORED, PLAYER, WUMPUS, PIT, BAT, ARROW, NUM_OBJ_TYPES } OBJ_TYPE;

/*Typedefs*/
typedef struct tile{
    uint8_t explored;
    OBJ_TYPE object;
} tile;

typedef struct pt {
    int8_t x, y;
} point;

typedef struct player {
    point* pos;
    uint8_t arrows;
} player;

/*const arrays & enums*/
tile grid[GRID_SIZE_Y][GRID_SIZE_X];

const point DIRECTIONS[NUM_DIR] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

const struct objs {
    OBJ_TYPE type;
    char ch;
    uint8_t num;
} OBJECTS[NUM_OBJ_TYPES] = {
    {NONE, cEMPTY, NULL},
    {EXPLORED, cEXPLORED, NULL},
    {PLAYER, cPLAYER, 1},
    {WUMPUS, cWUMPUS, 1},
    {PIT, cPIT, NUM_PITS},
    {BAT, cBAT, NUM_BATS},
    {ARROW, cARROW, NUM_ARR_OBJ}
};

/*Prototypes */
int isEmpty(point* pos);
int inBounds(point* pos);
point* getEmptyPoint(void);
void placeObj(point* p, OBJ_TYPE a);
void rmObj(point* p);
void initGrid(void);
player* initPlayer(OBJ_TYPE type);
void wumpusMove(player* w);
void playerNear(player* pl);
char* playerMove(player* pl, DIR a, player* w);
char* playerShoot(player* pl, DIR a, player* w);
void endGame(player* pl, player* w);
void playerDie(player* pl, player* w);
void drawGrid(player* pl, char* msg);
int input(void);
char* action(player* pl, player* w, int in);
void game(void);
//*/
#endif //_MAIN_H
