#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>

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
    point* p = malloc(sizeof(point));
    do{
        p->x = rand() % GRID_SIZE_X;
        p->y = rand() % GRID_SIZE_Y;
    }while(!isEmpty(p));
    return p;
}

void placeObj(point* p, struct objs a){
    grid[p->x][p->y].object = a.type;
}

void rmObj(point* p, struct objs a){
    if(grid[p->x][p->y].explored){
        grid[p->x][p->y].object = OBJECTS[EXPLORED].type;
    }else{
        grid[p->x][p->y].object = OBJECTS[NONE].type;
    }
}

void initGrid(void){
    int i,j;
    for(i=PIT; i<NUM_OBJ_TYPES; i++){
        for(j=0; j<OBJECTS[i].num; j++){
            point* p = getEmptyPoint();
            placeObj(p, OBJECTS[i]);
            free(p);
        }
    }
}

player* initPlayer(OBJ_TYPE type){
    player *pl = malloc(sizeof(player));
    pl->arrows = NUM_ARR_PL;
    pl->pos = getEmptyPoint();
    placeObj(pl->pos, OBJECTS[type]);
    return pl;
}

void wumpusMove(player* w){
    rmObj(w->pos, OBJECTS[WUMPUS]);
    free(w->pos);
    w->pos = getEmptyPoint();
    placeObj(w->pos, OBJECTS[WUMPUS]);
}

void playerNear(player* pl){
    int8_t i, x0, y0;
    for(i=0; i<NUM_DIR; i++){
        x0 = pl->pos->x + DIRECTIONS[i].x;
        y0 = pl->pos->y + DIRECTIONS[i].y;
        point p = {x0, y0};
        if(inBounds(&p)){
            switch(grid[x0][y0].object){
                case WUMPUS: printf("You smell a Wumpus\n"); break;
                case PIT: printf("You feel a breeze\n"); break;
                case BAT: printf("You hear flapping\n"); break;
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
                rmObj(pl->pos, OBJECTS[PLAYER]);
                grid[pl->pos->x][pl->pos->y].explored = 1;
                pl->pos = getEmptyPoint();
                placeObj(pl->pos, OBJECTS[PLAYER]);
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
            printf("Congratulations! you have killed the Wumpus\n");
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
    free(pl->pos);
    free(pl);
    free(w->pos);
    free(w);
    exit(EXIT_SUCCESS);
}

void playerDie(player* pl, player* w){
    printf("You are dead\n");
    endGame(pl, w);
}

void drawGrid(player* pl){
    int i,j,k;
    clrscr();
    for(k=0;k<(2*GRID_SIZE_X)+1;k++){
        putchar('-');
    }
    putchar('\n');
    for(i=0; i<GRID_SIZE_X; i++){
        for(j=0;j<GRID_SIZE_Y;j++){
            putchar('|');
            putchar(OBJECTS[grid[i][j].object].ch);
        }
        putchar('|');
        putchar('\n');
        if(i<GRID_SIZE_X+1){
            for(k=0;k<(2*GRID_SIZE_X)+1;k++){
                putchar('-');
            }
            putchar('\n');
        }
    }
    printf("ARROWS: %d\n", pl->arrows);
}

int input(void){
    char c = 0;
    printf("Enter a direction(wasd), or press f then a direction to fire\n:");
    do{ c = getchar(); } while(c == '\n');
    while('\n'!=getchar());
    return (int)c;
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
    srand((uint32_t)time(NULL));
    initGrid();
    player* pl = initPlayer(PLAYER);
    player* w = initPlayer(WUMPUS);
    char* msg = "";
    while(1){
        drawGrid(pl);
        printf(msg);
        playerNear(pl);
        msg = action(pl, w, input());
    }
}

int main(void){
    game();
}
