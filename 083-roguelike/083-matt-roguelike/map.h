#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ncurses.h>

#ifndef MAP_H
#define MAP_H

#include "types.h"
#include "object.h"

#define cEMPTY  ' '
#define cWALL   '#'
#define cFLOOR  '\''
#define cDOOR   '+'
#define cSTAIR  '>'

#define cGOLD   '*'
#define cWEAP   '/'
#define cPOTN   '?'
#define cARMR   '['

/*Prototypes*/
void setTile(Map* m, uint16_t x, uint16_t y, enum TILE_TYPE type);
enum TILE_TYPE getTile(Map* m, uint16_t x, uint16_t y);
uint8_t isEmptyPoint(Map* m, uint16_t x, uint16_t y);
uint8_t isInBounds(Map* m, int16_t x, int16_t y);
uint8_t canMove(Map* m, uint16_t x, uint16_t y);
Point* getEmptyPoint(Map* m);
void setRoomVis(Map* m, int16_t x, int16_t y);
void setRoomUnvis(Map* m, int16_t x, int16_t y);
void drawMap(Map* m);
#endif // MAP_H
