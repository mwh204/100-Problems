#ifndef GENERATE_H
#define GENERATE_H

#include "map.h"
#include "common.h"

#define NUM_ROOMS 10

#define ROOM_SIZE_MIN 5
#define ROOM_SIZE_MAX 13

#define MAX_ATTEMPTS 1000

int makeRoom(Map* m, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t dir);
void genDungeon(Map* m, uint8_t rooms);
#endif // GENERATE_H
