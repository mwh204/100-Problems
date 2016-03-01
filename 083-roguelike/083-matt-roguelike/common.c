#include "common.h"

#define BIAS_WEIGHT 0.4

const Point DIRECTIONS[NUM_DIR] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}, {1, -1}, {1, 1}, {-1, 1}, {-1, -1}};

void msg(Game* g, char* msg){
    mvaddstr(MAP_SIZE_Y+2, 0, "\t\t\t\t\t\t\t");
    mvaddstr(MAP_SIZE_Y+2, 0, msg);
    move(g->pl->pos->y, g->pl->pos->x);
}

uint32_t max(uint32_t a, uint32_t b){
    return a > b ? a : b;
}

uint32_t min(uint32_t a, uint32_t b){
    return a < b ? a : b;
}

uint32_t randRange(uint32_t min, uint32_t max){
    uint32_t r;
    const uint32_t range = 1 + max - min;
    const uint32_t buckets = RAND_MAX / range;
    const uint32_t limit = buckets * range;

    do{
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

double frand(void){
    return((double)rand()/(double)RAND_MAX);
}

uint8_t frand_weighted(double weight){
    return (uint8_t)(frand() > weight);
}

uint32_t lowBiasRand(double weight, uint32_t min, uint32_t max){
    uint32_t i;
    for(i = min; i<max; i++){
        if(frand_weighted(weight)) break;
    }
    return i;
}
