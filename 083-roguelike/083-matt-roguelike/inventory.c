#include "inventory.h"

void inv_add(Game* g){
    char message[80];
    int type = getObj(g, g->pl->pos->x, g->pl->pos->y);
    if(type == GOLD){
        uint16_t amt = g->map.map[g->pl->pos->y][g->pl->pos->x].obj.obj.gold.amount;
        g->pl->gold += amt;
        setObjType(g, g->pl->pos->x, g->pl->pos->y, NO_OBJ);
        sprintf(message, "Picked up %d gold", amt);
        msg(g, message);
    }else if(type != NO_OBJ && g->pl->num_items_inventory < MAX_ITEMS_INV-1){
        copyObj(&g->pl->inv[g->pl->num_items_inventory], &g->map.map[g->pl->pos->y][g->pl->pos->x].obj);
        setObjType(g, g->pl->pos->x, g->pl->pos->y, NO_OBJ);
        g->pl->num_items_inventory++;
        sprintf(message, "Picked up a %s", g->pl->inv[g->pl->num_items_inventory-1].name);
        msg(g, message);
    }else{
        msg(g, "Inventory full");
    }
}

void inv_drop(Game* g, int index){
    if(g->pl->num_items_inventory <= 0) return;
    if(getObj(g, g->pl->pos->x, g->pl->pos->y) != NO_OBJ) return;

    setObj(g, &g->pl->inv[index], g->pl->pos->x, g->pl->pos->y);
    inv_del(g, index);
}

void inv_del(Game* g, int index){
    g->pl->inv[index].type = NO_OBJ;
    for(int i=index; i<g->pl->num_items_inventory; i++){
        g->pl->inv[i] = g->pl->inv[i+1];
    }
    g->pl->num_items_inventory--;
}

int getInvIndex(Game* g){
    char ch = 0;
    int i;
    if(g->pl->num_items_inventory == 0) return -1;
    WINDOW *invWin = newwin(10, 25, 1, 1);
    wrefresh(invWin);
    for(i=0; i<g->pl->num_items_inventory; i++){
        mvwprintw(invWin, i, 0, "%d: %s", i, &g->pl->inv[i].name);
    }
    i=0;
    do{
        mvwprintw(invWin, i, 3, "%s", &g->pl->inv[i].name);
        switch( ch ) {
            case 'q':
                return -1;
            case 'k':
                i--;
                i = i<0? g->pl->num_items_inventory-1 : i;
                break;
            case 'j':
                i++;
                i = i>g->pl->num_items_inventory-1? 0 : i;
                break;
        }
        wattron(invWin, A_STANDOUT);
        mvwprintw(invWin, i, 3, "%s", &g->pl->inv[i].name);
        wattroff(invWin, A_STANDOUT);
    }while(( ch = wgetch(invWin)) != '\n');
    delwin(invWin);
    return i;
}

void printInv(Game* g){
    int i;
    if(g->pl->num_items_inventory <= 0) return;
    WINDOW *invWin = newwin(10, 20, 1, 1);
    wrefresh(invWin);
    mvwaddstr(invWin, 0, 0, "Inventory:");
    for(i=0; i<g->pl->num_items_inventory; i++){
        mvwprintw(invWin, i+1, 0, "%d: %s", i, &g->pl->inv[i].name);
    }
    wrefresh(invWin);
    getch();
    delwin(invWin);
}
