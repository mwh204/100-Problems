#include<math.h>
#include "mob.h"

extern Point DIRECTIONS[NUM_DIR];

const char cMob[NUM_MOB_TYPES] ={
    NO_MOB,
    cRAT,
    cKOBOLD,
    cCRAB,
    cDINGO,
    cSNAKE,
    cGOBLIN,
    cZOMBIE,
    cSKELETON,
    cOGRE,
    cLIZPERSN,
    cTROLL,
    cCENTAUR,
    cMINOTAUR,
    cDEMON
};

const struct mob_stats{
    enum MOB_TYPES type;
    enum MOB_STATE state;
    uint16_t exp;
    uint16_t minhp;
    uint16_t maxhp;
    uint16_t base_dmg;
    char* name;
} MOB_STATS[] = {
    {NO_MOB,    STILL,  0,  0,  0,  0,  ""},
    {RAT,       RAND,   2,  3,  5,  1,  "rat"},
    {KOBOLD,    STILL,  3,  5,  7,  2,  "kobold"},
    {CRAB,      RAND,   2,  4,  5,  1,  "crab"},
    {DINGO,     AGGRO,  3,  6,  8,  2,  "dingo"},
    {SNAKE,     STILL,  3,  4,  8,  2,  "snake"},
    {GOBLIN,    AGGRO,  4,  5,  10, 3,  "goblin"},
    {ZOMBIE,    STILL,  6,  10, 15, 4,  "zombie"},
    {SKELETON,  AGGRO,  5,  11, 16, 3,  "skeleton"},
    {OGRE,      AGGRO,  6,  15, 17, 2,  "ogre"},
    {LIZPRSN,   STILL,  10, 10, 10, 4,  "lizard person"},
    {TROLL,     AGGRO,  9,  15, 20, 3,  "troll"},
    {CENTAUR,   AGGRO,  15, 10, 15, 6,  "centaur"},
    {MINOTAUR,  AGGRO,  20, 16, 20, 8,  "minotaur"},
    {DEMON,     AGGRO,  30, 20, 25, 10, "demon"}
};

Mob* createMob(Game* g, enum MOB_TYPES type){
    Mob* newMob = malloc(sizeof(Mob));
    newMob->type = type;
    newMob->name = MOB_STATS[type].name;
    newMob->state = MOB_STATS[type].state;
    newMob->exp = MOB_STATS[type].exp;
    newMob->hp = randRange(MOB_STATS[type].minhp, MOB_STATS[type].maxhp);
    newMob->dmg = MOB_STATS[type].base_dmg;
    newMob->pos = getEmptyPoint(&g->map);

    return newMob;
}

void createAllMob(Game* g, int n){
    uint16_t i;
    enum MOB_TYPES type;
    free(g->mobList);
    g->mobList = malloc(n * sizeof(Mob));
    for(i=0; i<n; i++){
        type = randRange(1, (uint8_t)fmin(g->map.current_floor + 3, NUM_MOB_TYPES-1));
        g->mobList[i] = createMob(g, type);
    }
}

void mobAct(Game* g){
    uint16_t i;
    for(i=0; i<g->num_mobs; i++){
        switch(g->mobList[i]->state){
        case RAND:
            moveRand(g, g->mobList[i]);
            break;
        case AGGRO:
            moveTowards(g, g->mobList[i], g->pl->pos);
        default: break;
        }
    }
}

void mobMove(Game* g, Mob* m, Point* p){
    if(p->x == g->pl->pos->x && p->y == g->pl->pos->y){
        m->state = AGGRO;
        mobAttack(g, m, p);
    }else if(canMove(&g->map, p->x, p->y) && isMobAt(g, p) == -1){
        *m->pos = *p;
    }
}

void mobKill(Game* g, uint8_t index){
    int i;
    if(g->num_mobs <= 0) return;

    char message[80];
    sprintf(message, "you kill the %s", g->mobList[index]->name);
    msg(g, message);
    playerExp(g, g->mobList[index]->exp);
    for(i=index; i<g->num_mobs-1; i++){
        g->mobList[i] = g->mobList[i+1];
    }
    g->num_mobs--;
}

int8_t isMobAt(Game* g, Point* p){
    int8_t i, mob=-1;
    for(i=0; i<g->num_mobs; i++){
        if((p->x == g->mobList[i]->pos->x) && (p->y == g->mobList[i]->pos->y)){
            mob = i;
            break;
        }
    }
    return mob;
}

uint8_t mobAttack(Game* g, Mob* m, Point* p){
    uint8_t ret = 0;
    if( (ret = frand_weighted(0.4 + (double)(g->map.current_floor/10.0))) ){
        playerDamage(g, m->dmg);
    }
    return ret;
}

void moveTowards(Game* g, Mob* m, Point* p){
    int16_t x0, y0, xx, yy;
    xx = (p->x - m->pos->x);
    yy = (p->y - m->pos->y);
    x0 = xx == 0 ? 0 : xx/abs(xx);
    y0 = yy == 0 ? 0 : yy/abs(yy);
    Point n = {(x0 + m->pos->x), (y0 + m->pos->y)};
    mobMove(g, m, &n);
}

void moveRand(Game* g, Mob* m){
    int d = randRange(N, NUM_DIR-1);
    Point n = {m->pos->x + DIRECTIONS[d].x, m->pos->y + DIRECTIONS[d].y};
    mobMove(g, m, &n);
}

void drawMob(Game* g, int n){
    uint32_t i, x, y;
    for(i=0; i<n; i++){
        x = g->mobList[i]->pos->x;
        y = g->mobList[i]->pos->y;
        if(g->map.map[y][x].vis)
            mvaddch(y, x, cMob[g->mobList[i]->type]);
    }
}
