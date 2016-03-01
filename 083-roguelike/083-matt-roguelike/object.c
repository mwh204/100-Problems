#include "object.h"

enum OBJ_TYPE getObj(Game* g, int16_t x, int16_t y){
    return g->map.map[y][x].obj.type;
}

void setObjType(Game* g, int16_t x, int16_t y, enum OBJ_TYPE type){
    if (isInBounds(&g->map, x, y)){
        g->map.map[y][x].obj.type = type;
    }
}

void copyObj(Object* dest, Object* src){
    memcpy((Object* )dest, (Object* )src, sizeof(Object));
}

void swapObj(Object* a, Object* b){
    Object* temp = malloc(sizeof(Object));
    copyObj(temp, a);
    copyObj(a, b);
    copyObj(b, temp);
    free(temp);
}

void setObj(Game* g, Object* o, int16_t x, int16_t y){
    setObjType(g, x, y, o->type);
    copyObj(&g->map.map[y][x].obj, o);
}

void nameObj(Object* o){
const char* sMat[NUM_MATERIALS] = {"iron", "steel", "addy"};
const char* sPot[NUM_EFFECTS] = {"random", "useless", "healing", "exp", "buff weapon", "teleport", "buff armor", "full heal"};
    switch(o->type){
        case WEAPON:
            sprintf(o->name, "+%d %s sword", o->obj.weapon.dmg, sMat[o->obj.weapon.mat]);
            break;
        case ARMOR:
            sprintf(o->name, "+%d %s armor", o->obj.armor.prot_fact, sMat[o->obj.weapon.mat]);
            break;
        case POTION:
            sprintf(o->name, "%s potion", sPot[o->obj.potion.eff]);
            break;
        default: break;
    }
}

void placeAllObjects(Game* g){
    placeGold(g);
    placeWeapon(g);
    placePotion(g);
    placeArmor(g);
}

void placeObject(Game* g, Object* o){
    Point* p = getEmptyPoint(&g->map);
    setObj(g, o, p->x, p->y);
    free(p);
}

Object* createObject(Game* g, enum OBJ_TYPE type){
    Object* o = malloc(sizeof(Object));
    o->type = type;
    switch(type){
        case GOLD:
            o->obj.gold.amount = goldAmount(g);
            break;
        case WEAPON:
            o->obj.weapon.mat = lowBiasRand(0.5, IRON, NUM_MATERIALS-1);
            o->obj.weapon.dmg = lowBiasRand(0.5, 0, (g->map.current_floor+1));
            break;
        case ARMOR:
            o->obj.armor.mat = lowBiasRand(0.6, IRON, NUM_MATERIALS-1);
            o->obj.armor.prot_fact = lowBiasRand(0.5, 0, (g->map.current_floor+1));
            break;
        case POTION:
            o->obj.potion.eff = randRange(0, NUM_EFFECTS-1);
            break;
        default: break;
    }
    nameObj(o);
    return o;
}

uint16_t goldAmount(Game* g){
    return randRange(MIN_GOLD, MAX_GOLD) + randRange(0, NUM_GOLD * g->map.current_floor);
}

void placeGold(Game* g){
    uint16_t i;
    Object* o;
    for(i=0; i<randRange(0, NUM_GOLD); i++){
        o = createObject(g, GOLD);
        placeObject(g, o);
        free(o);
    }
}

void placeWeapon(Game* g){
    uint16_t i;
    Object* o;
    for(i=0; i<lowBiasRand(0.25, 0, NUM_WEAP + g->map.current_floor/2); i++){
        o = createObject(g, WEAPON);
        placeObject(g, o);
        free(o);
    }
}

void placeArmor(Game* g){
    uint16_t i;
    Object* o;
    for(i=0; i<lowBiasRand(0.4, 0, NUM_ARMR + g->map.current_floor/2); i++){
        o = createObject(g, ARMOR);
        placeObject(g, o);
        free(o);
    }
}

void placePotion(Game* g){
    uint16_t i;
    Object* o;
    for(i=0; i<randRange(0, NUM_POTN + g->map.current_floor/2); i++){
        o = createObject(g, POTION);
        placeObject(g, o);
        free(o);
    }
}
