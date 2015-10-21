#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<ncurses.h>

#include "types.h"

#ifndef COMMON_H
#define COMMON_H

typedef enum { N, E, S, W, NE, SE, SW, NW, NUM_DIR } DIR;

/*Prototypes*/
void msg(Game* g, char* msg);
uint32_t max(uint32_t a, uint32_t b);
uint32_t min(uint32_t a, uint32_t b);
uint32_t randRange(uint32_t min, uint32_t max);
double frand(void);
uint8_t frand_weighted(double weight);
uint32_t lowBiasRand(double weight, uint32_t min, uint32_t max);
#endif // COMMON_H
