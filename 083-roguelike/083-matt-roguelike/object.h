#include<stdint.h>
#include<string.h>

#ifndef OBJECT_H
#define OBJECT_H

#include "map.h"
#include "common.h"
#include "types.h"

#define NUM_GOLD    20
#define MIN_GOLD    2
#define MAX_GOLD    25
#define NUM_WEAP    3
#define NUM_POTN    5
#define NUM_ARMR    3

extern enum OBJ_TYPE OBJ_TYPE;
extern enum EFFECTS EFFECTS;
extern enum MATERIALS MATERIALS;

/*Prototypes*/
enum OBJ_TYPE getObj(Game* g, int16_t x, int16_t y);
void setObjType(Game* g, int16_t x, int16_t y, enum OBJ_TYPE type);
void setObj(Game* g, Object* o, int16_t x, int16_t y);
void nameObj(Object* o);
void placeAllObjects(Game* g);
void placeObject(Game* g, Object* o);
void copyObj(Object* dest, Object* src);
void swapObj(Object* a, Object* b);
Object* createObject(Game* g, enum OBJ_TYPE type);
uint16_t goldAmount(Game* g);
void placeGold(Game* g);
void placeWeapon(Game* g);
void placeArmor(Game* g);
void placePotion(Game* g);
#endif // OBJECT_H
