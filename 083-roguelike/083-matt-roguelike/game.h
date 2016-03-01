#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<ncurses.h>

#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "map.h"
#include "mob.h"
#include "player.h"
#include "generate.h"
#include "inventory.h"
#include "game.h"
#include "types.h"

#define K_N         'k'
#define K_E         'l'
#define K_S         'j'
#define K_W         'h'
#define K_NE        'i'
#define K_SE        'm'
#define K_SW        'n'
#define K_NW        'u'
#define K_QUIT      'Q'
#define K_DRINK     'd'
#define K_WIELD     'w'
#define K_WEAR      'a'
#define K_DESCEND   '>'
#define K_INV       ','
#define K_DROP      'D'

/*Prototypes*/
void rogue(void);
void getInput(Game* g);
void printStatus(Game* g);
void drawAll(Game* g);
void initCurses(void);
Game* initGame(void);
void initFloor(Game* g);
void nextFloor(Game* g);
void endFloor(Game* g);
void endGame(Game* g);
#endif // GAME_H
