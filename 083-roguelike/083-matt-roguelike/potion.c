#include "potion.h"

void potionEffect(Game* g, enum EFFECTS eff){
    switch(eff){
        case PRAND:
            potionEffect(g, randRange(1, NUM_EFFECTS-1));
            break;
        case HEAL:
            msg(g, "you feel a little better");
            g->pl->hp += (g->pl->maxhp-g->pl->hp)/2;
            break;
        case FHEAL:
            msg(g, "You feel fully recovered");
            g->pl->hp = g->pl->maxhp;
            break;
        case EXP:
            msg(g, "you feel more experienced");
            playerExp(g, 4 * g->pl->level);
            break;
        case WBUFF:
            msg(g, "your sword feels more powerful");
            g->pl->weapon->obj.weapon.dmg++;
            nameObj(g->pl->weapon);
            break;
        case ABUFF:
            msg(g, "your armor feels stronger");
            g->pl->armor->obj.armor.prot_fact++;
            nameObj(g->pl->armor);
            break;
        case TELE:
            msg(g, "you teleport away");
            setRoomUnvis(&g->map, g->pl->pos->x, g->pl->pos->y);
            g->pl->pos = getEmptyPoint(&g->map);
            break;
        case NO_EFF:
            msg(g, "there was no effect");
        default: break;
    }
}
