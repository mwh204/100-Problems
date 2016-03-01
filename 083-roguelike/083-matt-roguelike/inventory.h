#include<ncurses.h>

#ifndef INVENTORY_H
#define INVENTORY_H

#include "object.h"
#include "types.h"

/*Prototypes*/
void inv_add(Game* g);
void inv_drop(Game* g, int index);
void inv_del(Game* g, int index);
int getInvIndex(Game* g);
void printInv(Game* g);
#endif // INVENTORY_H
