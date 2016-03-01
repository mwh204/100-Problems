#ifndef POTION_H
#define POTION_H

#include "object.h"
#include "inventory.h"
#include "player.h"
#include "common.h"
#include "types.h"

extern enum EFFECTS EFFECTS;

/*Prototypes*/
void potionEffect(Game* g, enum EFFECTS eff);
#endif // POTION_H
