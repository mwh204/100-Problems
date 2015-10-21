#include "map.h"

extern enum TILE_TYPE TILE_TYPE;

const char cDraw[NUM_TILE_TYPES] = {cEMPTY, cWALL, cFLOOR, cDOOR, cSTAIR};
const char cObj[NUM_OBJ_TYPES] = {0, cGOLD, cWEAP, cPOTN, cARMR};

void setTile(Map* m, uint16_t x, uint16_t y, enum TILE_TYPE type){
    if (isInBounds(m, x, y)){
        m->map[y][x].type = type;
    }
}

enum TILE_TYPE getTile(Map* m, uint16_t x, uint16_t y){
    return m->map[y][x].type;
}

uint8_t isEmptyPoint(Map* m, uint16_t x, uint16_t y){
    return getTile(m, x, y) == FLOOR;
}

uint8_t isInBounds(Map* m, int16_t x, int16_t y){
    return  x > 0 && x < MAP_SIZE_X &&
            y > 0 && y < MAP_SIZE_Y;
}

uint8_t canMove(Map* m, uint16_t x, uint16_t y){
    enum TILE_TYPE tile = getTile(m, x, y);
    return tile == FLOOR || tile == DOOR || tile == STAIR;
}

Point* getEmptyPoint(Map* m){
    Point* p = malloc(sizeof(Point));
    uint16_t x, y;
    do{
        x = randRange(0, MAP_SIZE_X-1);
        y = randRange(0, MAP_SIZE_Y-1);
    }while(!isEmptyPoint(m, x, y));
    p->x = x; p->y = y;
    return p;
}

void setRoomVis(Map* m, int16_t x, int16_t y){
    int tile = getTile(m, x, y);
    if(tile == DOOR || tile == WALL) m->map[y][x].vis = 1;
    if((tile == FLOOR || tile == STAIR) && !m->map[y][x].vis) {
        m->map[y][x].vis = 1;
        setRoomVis(m, x+1, y);
        setRoomVis(m, x-1, y);
        setRoomVis(m, x, y-1);
        setRoomVis(m, x, y+1);
        setRoomVis(m, x+1, y+1);
        setRoomVis(m, x-1, y+1);
        setRoomVis(m, x+1, y-1);
        setRoomVis(m, x-1, y-1);
    }else{
        return;
    }
}

void setRoomUnvis(Map* m, int16_t x, int16_t y){
    if(getTile(m, x, y) == FLOOR && m->map[y][x].vis){
        m->map[y][x].vis = 0;
        setRoomUnvis(m, x+1, y);
        setRoomUnvis(m, x-1, y);
        setRoomUnvis(m, x, y-1);
        setRoomUnvis(m, x, y+1);
    }else{
        return;
    }
}

void drawMap(Map* m){
    uint32_t i, j;
    char ch;
    for(i=0; i<MAP_SIZE_Y; i++){
        for(j=0; j<MAP_SIZE_X; j++){
            ch = cDraw[m->map[i][j].type];
            if(m->map[i][j].obj.type != NO_OBJ) ch = cObj[m->map[i][j].obj.type];
            if(m->map[i][j].vis)
                mvaddch(i, j, ch);
            else
                mvaddch(i, j, cEMPTY);
            //*/
        }
    }
}
