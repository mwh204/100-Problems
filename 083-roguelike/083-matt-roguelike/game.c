#include "game.h"

void rogue(void){
    initCurses();
    Game* g = initGame();
    while(g->pl->alive){
        mobAct(g);
        setRoomVis(&g->map, g->pl->pos->x, g->pl->pos->y);
        drawAll(g);
        getInput(g);
    }
    endGame(g);
}

void getInput(Game* g){
    char ch;
    switch(ch = getch()){
        case K_N:
            playerMove(g, N);
            break;
        case K_N-32:
            playerFastMove(g, N);
            break;
        case K_E:
            playerMove(g, E);
            break;
        case K_E-32:
            playerFastMove(g, E);
            break;
        case K_S:
            playerMove(g, S);
            break;
        case K_S-32:
            playerFastMove(g, S);
            break;
        case K_W:
            playerMove(g, W);
            break;
        case K_W-32:
            playerFastMove(g, W);
            break;
        case K_NE:
            playerMove(g, NE);
            break;
        case K_SE:
            playerMove(g, SE);
            break;
        case K_SW:
            playerMove(g, SW);
            break;
        case K_NW:
            playerMove(g, NW);
            break;
        case K_DESCEND:
            nextFloor(g);
            break;
        case K_DRINK:
            playerDrink(g);
            break;
        case K_WEAR:
            playerWear(g);
            break;
        case K_WIELD:
            playerWield(g);
            break;
        case K_INV:
            printInv(g);
            break;
        case K_DROP:
            playerDrop(g);
            break;
        case K_QUIT:
            g->pl->alive = 0;
        default: break;
    }
}

void printStatus(Game* g){
    char status[80];
    sprintf(status, "floor: %d gold: %d hp: %d/%d dmg: %d armor: %d exp: %d/%d",
        g->map.current_floor,
        g->pl->gold,
        g->pl->hp,
        g->pl->maxhp,
        g->pl->dmg + g->pl->weapon->obj.weapon.dmg + g->pl->weapon->obj.weapon.mat,
        g->pl->armor->obj.armor.prot_fact + g->pl->armor->obj.armor.mat,
        g->pl->level,
        g->pl->exp
        );
    mvaddstr(MAP_SIZE_Y+1, 0, status);
}

void drawAll(Game* g){
    drawMap(&g->map);
    drawMob(g, g->num_mobs);
    printStatus(g);
    drawPlayer(g->pl);
}

void initCurses(void){
    initscr();
	raw();
	noecho();
}

Game* initGame(void){
    Game* g = malloc(sizeof(Game));
    g->map.current_floor = 0;
    g->pl = initPlayer();
    g->pl->armor = createObject(g, ARMOR);
    g->pl->weapon = createObject(g, WEAPON);
    initFloor(g);
    return g;
}

void initFloor(Game* g){
    genDungeon(&g->map, NUM_ROOMS + 2*g->map.current_floor);
    g->num_mobs = g->map.current_floor + randRange(MIN_MOBS, MAX_MOBS);
    createAllMob(g, g->num_mobs);
    placeAllObjects(g);
    g->map.current_floor++;
    g->pl->pos = getEmptyPoint(&g->map);
}

void nextFloor(Game* g){
    if(getTile(&g->map, g->pl->pos->x, g->pl->pos->y) == STAIR){
        endFloor(g);
        initFloor(g);
    }
}

void endFloor(Game* g){
    free(g->pl->pos);
    for(int i=0; i<g->num_mobs; i++){
        free(g->mobList[i]);
    }
}

void endGame(Game* g){
    endFloor(g);
    endPlayer(g->pl);
    free(g);
    endwin();
}

