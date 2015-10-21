#include<ncurses.h>

#ifndef PLAYER_H
#define PLAYER_H

#include "inventory.h"
#include "potion.h"
#include "map.h"
#include "mob.h"
#include "common.h"
#include "types.h"

#define cPLAYER         '@'

#define BASE_HP         12
#define BASE_DMG        3
#define ARM_PROT_FCT    0.15
/*Prototypes*/
Player* initPlayer(void);
void endPlayer(Player* pl);
void playerMove(Game* g, DIR d);
void playerFastMove(Game* g, DIR d);
void playerAttack(Game* g, DIR d);
void playerDamage(Game* g, uint16_t damage);
void playerPickup(Game* g);
void playerDrop(Game* g);
void playerDrink(Game* g);
void playerWield(Game* g);
void playerWear(Game* g);
void playerExp(Game* g, uint8_t exp);
void playerLevelUp(Game* g);
void drawPlayer(Player* pl);
#endif // PLAYER_H
