#include "player.h"

extern Point DIRECTIONS[NUM_DIR];
const int LEVEL[] = {0, 10, 20, 45, 90, 150, 300, 400, 500, 750, 900, 1024, 1337, 1500, 3000, 999999999};


Player* initPlayer(void){
    Player* pl = malloc(sizeof(Player));
    pl->alive = 1;
    pl->num_items_inventory = 0;
    pl->gold = 0;
    pl->exp = 0;
    pl->level = 1;
    pl->hp = BASE_HP;
    pl->maxhp = BASE_HP;
    pl->dmg = BASE_DMG;
    return pl;
}

void playerMove(Game* g, DIR d){
    int16_t x0 = g->pl->pos->x + DIRECTIONS[d].x;
    int16_t y0 = g->pl->pos->y + DIRECTIONS[d].y;
    Point p0 = {x0, y0};

    if(isMobAt(g, &p0) >= 0){
        playerAttack(g, d);
    }else if(canMove(&g->map, x0, y0)){
        if(getTile(&g->map, x0, y0) == DOOR) setRoomUnvis(&g->map, g->pl->pos->x, g->pl->pos->y);
        g->pl->pos->x += DIRECTIONS[d].x;
        g->pl->pos->y += DIRECTIONS[d].y;
        if(getObj(g, x0, y0) != NO_OBJ) playerPickup(g);
    }
}

void playerFastMove(Game* g, DIR d){
    enum TILE_TYPE t0 = getTile(&g->map, g->pl->pos->x, g->pl->pos->y);
    int n = g->pl->num_items_inventory;
    do{
        playerMove(g, d);
    }while( getTile(&g->map, g->pl->pos->x + DIRECTIONS[d].x, g->pl->pos->y + DIRECTIONS[d].y) == t0 &&
            n == g->pl->num_items_inventory);
}

void playerAttack(Game* g, DIR d){
    int16_t x0 = g->pl->pos->x + DIRECTIONS[d].x;
    int16_t y0 = g->pl->pos->y + DIRECTIONS[d].y;
    Point p0 = {x0, y0};

    int8_t i = isMobAt(g, &p0);
    if(i < 0) return;
    g->mobList[i]->state = AGGRO;
    char message[80];

    if(frand_weighted(0.4 + (double)(g->pl->level/14.0) )){
        if(mobAttack(g, g->mobList[i], &p0)){
            sprintf(message, "you hit the %s and the %s hits you", g->mobList[i]->name, g->mobList[i]->name);
            msg(g, message);
            g->mobList[i]->hp -= g->pl->dmg + g->pl->weapon->obj.weapon.dmg + g->pl->weapon->obj.weapon.mat;
        }else{
            sprintf(message, "you hit the %s and the %s misses you", g->mobList[i]->name, g->mobList[i]->name);
            msg(g, message);
            g->mobList[i]->hp -= g->pl->dmg + g->pl->weapon->obj.weapon.dmg + g->pl->weapon->obj.weapon.mat;
        }
    }else{
        if(mobAttack(g, g->mobList[i], &p0)){
            sprintf(message, "you miss the %s and the %s hits you", g->mobList[i]->name, g->mobList[i]->name);
            msg(g, message);
        }else{
            sprintf(message, "you miss the %s and the %s misses you", g->mobList[i]->name, g->mobList[i]->name);
            msg(g, message);
        }
    }

    if(g->mobList[i]->hp <= 0){
        mobKill(g, i);
    }
}

void playerDamage(Game* g, uint16_t damage){
    g->pl->hp -= (damage * (ARM_PROT_FCT * (g->pl->armor->obj.armor.prot_fact + g->pl->armor->obj.armor.mat)));
    if(g->pl->hp <= 0){
        g->pl->alive = 0;
    }
}

void playerPickup(Game* g){
    if(getObj(g, g->pl->pos->x, g->pl->pos->y) != NO_OBJ){
        inv_add(g);
    }
}

void playerDrop(Game* g){
    int i = getInvIndex(g);
    if(i >= 0) inv_drop(g, i);
}

void playerDrink(Game* g){
    int i = getInvIndex(g);
    if(i < 0) return;
    if(g->pl->inv[i].type == POTION){
        potionEffect(g, g->pl->inv[i].obj.potion.eff);
        inv_del(g, i);
    }
}

void playerWield(Game* g){
    int i = getInvIndex(g);
    if(i < 0) return;
    if(g->pl->inv[i].type == WEAPON){
        swapObj(g->pl->weapon, &g->pl->inv[i]);
    }
}

void playerWear(Game* g){
    int i = getInvIndex(g);
    if(i < 0) return;
    if(g->pl->inv[i].type == ARMOR){
        swapObj(g->pl->armor, &g->pl->inv[i]);
    }
}

void playerExp(Game* g, uint8_t exp){
    g->pl->exp += exp;
    if(g->pl->exp >= LEVEL[g->pl->level]){
        playerLevelUp(g);
    }
}

void playerLevelUp(Game* g){
    g->pl->level++;
    g->pl->maxhp += max(8, g->pl->level);
    g->pl->hp += max(8, g->pl->level);
    char lmsg[50];
    sprintf(lmsg, "You are now level %d", g->pl->level);
    msg(g, lmsg);
}

void endPlayer(Player* pl){
    free(pl);
}

void drawPlayer(Player* pl){
    mvaddch(pl->pos->y, pl->pos->x, cPLAYER);
    move(pl->pos->y, pl->pos->x);
}
