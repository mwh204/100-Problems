#include<stdint.h>
#include<ncurses.h>

#ifndef MOB_H
#define MOB_H

#include "map.h"
#include "player.h"
#include "common.h"
#include "types.h"

#define cRAT        'r'
#define cKOBOLD     'k'
#define cCRAB       'c'
#define cDINGO      'd'
#define cSNAKE      's'
#define cGOBLIN     'g'
#define cZOMBIE     'Z'
#define cSKELETON   'S'
#define cOGRE       'O'
#define cLIZPERSN   'L'
#define cTROLL      'T'
#define cCENTAUR    'C'
#define cMINOTAUR   'M'
#define cDEMON      '&'

extern enum MOB_TYPES MOB_TYPES;
extern enum MOB_STATE MOB_STATE;

/*Prototypes*/
Mob* createMob(Game* g, enum MOB_TYPES type);
void createAllMob(Game* g, int n);
void mobAct(Game* g);
void mobMove(Game* g, Mob* m, Point* p);
void mobKill(Game* g, uint8_t index);
int8_t isMobAt(Game* g, Point* p);
void moveTowards(Game* g, Mob* m, Point* p);
uint8_t mobAttack(Game* g, Mob* m, Point* p);
void moveRand(Game* g, Mob* m);
void drawMob(Game* g, int n);
#endif // MOB_H
