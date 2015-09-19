/*main.h - Defines, types and function prototypes*/

#ifndef _MAIN_H
#define _MAIN_H

/*Defines*/
#define clrscr()    puts ("\e[2J\e[1;1H")

#define GRID_SIZE_X (5)
#define GRID_SIZE_Y (5)

#define KEY_QUIT    'q'
#define KEY_SHOOT   'f'
#define KEY_UP      'w'
#define KEY_DOWN    's'
#define KEY_LEFT    'a'
#define KEY_RIGHT   'd'

#define NUM_PITS    (2)
#define NUM_BATS    (1)
#define NUM_ARR_OBJ (4) //number of arrows on the ground
#define NUM_ARR_PL  (5) //initial arrow count

//#define SEE_ALL       //uncomment to see hazards and items
#ifdef SEE_ALL
#define cEMPTY      ' '
#define cEXPLORED   '+'
#define cPLAYER     '@'
#define cWUMPUS     '#'
#define cPIT        'O'
#define cBAT        '^'
#define cARROW      '/'
#else
#define cEMPTY      ' '
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

typedef struct wumpus {
    point* pos;
} wumpus;

/*const arrays & enums*/
tile grid[GRID_SIZE_X][GRID_SIZE_Y];

const point DIRECTIONS[NUM_DIR] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

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

/*Prototypes*/
int isEmpty(point*);
int inBounds(point*);
point* getEmptyPoint(void);
void placeObj(point*, struct objs);
void initGrid(void);
void endGame(player* pl, wumpus* w);
void drawGrid(player*);
int input(void);
char* action(player*, wumpus*, int);
void game(void);

wumpus* initWumpus(void);
void wumpusMove(wumpus*);

player* initPlayer(void);
char* playerMove(player*, DIR, wumpus*);
char* playerShoot(player*, DIR, wumpus*);
void playerNear(player*);
void playerDie(player* pl, wumpus* w);

#endif //_MAIN_H
