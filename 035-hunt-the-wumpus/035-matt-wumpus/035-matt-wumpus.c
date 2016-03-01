#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>

#include<curses.h>

#include "main.h"

int isEmpty(point* pos){
    return  (grid[pos->x][pos->y].object == NONE) ||
            (grid[pos->x][pos->y].object == EXPLORED);
}

int inBounds(point* pos){
    return  pos->x>=0 && pos->x<GRID_SIZE_X &&
            pos->y>=0 && pos->y<GRID_SIZE_Y;
}

point* getEmptyPoint(void){
    uint32_t i = 0;
    point* p = malloc(sizeof(point));
    do{
        p->x = rand() % GRID_SIZE_X;
        p->y = rand() % GRID_SIZE_Y;
    }while(!isEmpty(p) && i++<PROB_MAX);
    if(i>=PROB_MAX){
        printw("Board size not large enough\n");
        endGame(NULL, NULL);
    }
    return p;
}

void placeObj(point* p, OBJ_TYPE a){
    grid[p->x][p->y].object = a;
}

void rmObj(point* p){
    if(grid[p->x][p->y].explored){
        placeObj(p, EXPLORED);
    }else{
        placeObj(p, NONE);
    }
}

void initGrid(void){
    int i,j;
    for(i=PIT; i<NUM_OBJ_TYPES; i++){
        for(j=0; j<OBJECTS[i].num; j++){
            point* p = getEmptyPoint();
            placeObj(p, OBJECTS[i].type);
            free(p);
        }
    }
}

player* initPlayer(OBJ_TYPE type){
    player *pl = malloc(sizeof(player));
    pl->arrows = NUM_ARR_PL;
    pl->pos = getEmptyPoint();
    placeObj(pl->pos, type);
    return pl;
}

void wumpusMove(player* w){
    rmObj(w->pos);
    free(w->pos);
    w->pos = getEmptyPoint();
    placeObj(w->pos, WUMPUS);
}

void playerNear(player* pl){
    int8_t i, x0, y0;
    for(i=0; i<NUM_DIR; i++){
        x0 = pl->pos->x + DIRECTIONS[i].x;
        y0 = pl->pos->y + DIRECTIONS[i].y;
        point p = {x0, y0};
        if(inBounds(&p)){
            switch(grid[x0][y0].object){
                case WUMPUS: printw("You smell a Wumpus\n"); break;
                case PIT: printw("You feel a breeze\n"); break;
                case BAT: printw("You hear flapping\n"); break;
                default: break;
            }
        }
    }
}

char* playerMove(player* pl, DIR a, player* w){
    char* msg = "";
    int8_t x0 = pl->pos->x + DIRECTIONS[a].x;
    int8_t y0 = pl->pos->y + DIRECTIONS[a].y;
    point p = {x0, y0};
    if(inBounds(&p)){
        switch(grid[x0][y0].object){
            case WUMPUS:
                printf("You have been eaten by the wumpus!\n");
                playerDie(pl, w);
                break;
            case PIT:
                printf("You fell down a pit!\n");
                playerDie(pl, w);
                break;
            case BAT:
                msg = "Bats carried you away!\n";
                rmObj(pl->pos);
                grid[pl->pos->x][pl->pos->y].explored = 1;
                pl->pos = getEmptyPoint();
                placeObj(pl->pos, PLAYER);
                break;
            case ARROW:
                msg = "You found an arrow!\n";
                pl->arrows++;
            default:
                grid[pl->pos->x][pl->pos->y].object = OBJECTS[EXPLORED].type;
                grid[pl->pos->x][pl->pos->y].explored = 1;
                pl->pos->x = x0;
                pl->pos->y = y0;
                grid[pl->pos->x][pl->pos->y].object = OBJECTS[PLAYER].type;
                grid[pl->pos->x][pl->pos->y].explored = 1;
                break;
        }
    }
    return msg;
}

char* playerShoot(player* pl, DIR a, player* w){
    char* msg = "";
    if(pl->arrows > 0){
        pl->arrows--;
        if(grid[pl->pos->x+DIRECTIONS[a].x][pl->pos->y+DIRECTIONS[a].y].object == OBJECTS[WUMPUS].type){
            printw("Congratulations! you have killed the Wumpus\n");
            endGame(pl, w);
        }else{
            wumpusMove(w);
            msg = "You missed the Wumpus, and he has moved\n";
        }
    }else{
        msg = "You don't have any arrows left\n";
    }
    return msg;
}

void endGame(player* pl, player* w){
    getch();
    if(pl){
        free(pl->pos);
        free(pl);
    }
    if(w){
        free(w->pos);
        free(w);
    }
    endwin();
    exit(EXIT_SUCCESS);
}

void playerDie(player* pl, player* w){
    printw("You are dead\n");
    endGame(pl, w);
}

void drawGrid(player* pl, char* msg){
    int i, j;
    clear();
    for(i=0; i<GRID_SIZE_Y; i++){
        for(j=0; j<GRID_SIZE_X; j++){
            mvaddch(i, j, OBJECTS[grid[j][i].object].ch);
        }
    }
    mvprintw(GRID_SIZE_Y+1, 0, msg);
}

int input(void){
    return getch();
}

char* action(player* pl, player* w, int in){
    char* msg = "";
    switch(in){
        case KEY_UP:
            msg = playerMove(pl, UP, w);
            break;
        case KEY_DOWN:
            msg = playerMove(pl, DOWN, w);
            break;
        case KEY_LEFT:
            msg = playerMove(pl, LEFT, w);
            break;
        case KEY_RIGHT:
            msg = playerMove(pl, RIGHT, w);
            break;
        case KEY_SHOOT:
            switch(in = input()){
                case KEY_DOWN: msg = playerShoot(pl, DOWN, w); break;
                case KEY_LEFT: msg = playerShoot(pl, LEFT, w); break;
                case KEY_RIGHT: msg = playerShoot(pl, RIGHT, w); break;
                case KEY_UP: msg = playerShoot(pl, UP, w); break;
                default: break;
            }
            break;
        case KEY_QUIT:
            endGame(pl, w);
            break;
        default: break;
    }
    return msg;
}

void game(void){
    /*ncurses stuff:*/
    initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);

    srand((uint32_t)time(NULL));
    initGrid();
    player* pl = initPlayer(PLAYER);
    player* w = initPlayer(WUMPUS);
    char* msg = "";
    while(1){
        drawGrid(pl, msg);
        playerNear(pl);
        msg = action(pl, w, input());
    }
}

int main(void){
    game();
}
