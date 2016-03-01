/**
Code from http://www.openprocessing.org/sketch/18822

Do not attempt to read, understand or edit this code
I will hopefully replace it sometime
*/
#include "generate.h"

int makeRoom(Map* m, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t dir){

    int xlen = randRange(ROOM_SIZE_MIN, w);
    int ylen = randRange(ROOM_SIZE_MIN, h);

    if( !(dir >= 0 && dir < NUM_DIR)) dir = 0;

    if(y-ylen <= 0 || y+ylen >= MAP_SIZE_Y || x-xlen <= 0 || x+xlen >= MAP_SIZE_X) return 0;

    switch(dir){
    case 0: // north
        //Check if there's enough space left for it
        for (int ytemp = y; ytemp > (y-ylen); ytemp--) {
            if (ytemp < 0 || ytemp >= MAP_SIZE_Y) return 0;
                for (int xtemp = (x-xlen/2); xtemp < (x+(xlen+1)/2); xtemp++) {
                    if (xtemp < 0 || xtemp >= MAP_SIZE_X) return 0;
                    if (getTile(m, xtemp, ytemp) != EMPTY) return 0; //no space left...
            }
        }
        //we're still here, build
        for (int ytemp = y; ytemp > (y-ylen); ytemp--) {
            for (int xtemp = (x-xlen/2); xtemp < (x+(xlen+1)/2); xtemp++) {
                //start with the walls
                if (xtemp == (x-xlen/2)) setTile(m, xtemp, ytemp, WALL);
                else if (xtemp == (x+(xlen-1)/2)) setTile(m, xtemp, ytemp, WALL);
                else if (ytemp == y) setTile(m, xtemp, ytemp, WALL);
                else if (ytemp == (y-ylen+1)) setTile(m, xtemp, ytemp, WALL);
                //and then fill with the floor
                else setTile(m, xtemp, ytemp, FLOOR);
            }
        }
        break;
    case 1: // east
        for (int ytemp = (y-ylen/2); ytemp < (y+(ylen+1)/2); ytemp++) {
            if (ytemp < 0 || ytemp > MAP_SIZE_Y) return 0;
            for (int xtemp = x; xtemp < (x+xlen); xtemp++) {
                if (xtemp < 0 || xtemp > MAP_SIZE_X) return 0;
                if (getTile(m, xtemp, ytemp) != EMPTY) return 0;
            }
        }

        for (int ytemp = (y-ylen/2); ytemp < (y+(ylen+1)/2); ytemp++) {
            for (int xtemp = x; xtemp < (x+xlen); xtemp++) {
                if (xtemp == x) setTile(m, xtemp, ytemp, WALL);
                else if (xtemp == (x+xlen-1)) setTile(m, xtemp, ytemp, WALL);
                else if (ytemp == (y-ylen/2)) setTile(m, xtemp, ytemp, WALL);
                else if (ytemp == (y+(ylen-1)/2)) setTile(m, xtemp, ytemp, WALL);
                else setTile(m, xtemp, ytemp, FLOOR);
            }
        }
        break;

    case 2: // south
        for (int ytemp = y; ytemp < (y+ylen); ytemp++) {
            if (ytemp < 0 || ytemp > MAP_SIZE_Y) return 0;
            for (int xtemp = (x-xlen/2); xtemp < (x+(xlen+1)/2); xtemp++) {
                if (xtemp < 0 || xtemp > MAP_SIZE_X) return 0;
                if (getTile(m, xtemp, ytemp) != EMPTY) return 0;
            }
        }

        for (int ytemp = y; ytemp < (y+ylen); ytemp++) {
            for (int xtemp = (x-xlen/2); xtemp < (x+(xlen+1)/2); xtemp++) {
                if (xtemp == (x-xlen/2)) setTile(m, xtemp, ytemp, WALL);
                else if (xtemp == (x+(xlen-1)/2)) setTile(m, xtemp, ytemp, WALL);
                else if (ytemp == y) setTile(m, xtemp, ytemp, WALL);
                else if (ytemp == (y+ylen-1)) setTile(m, xtemp, ytemp, WALL);
                else setTile(m, xtemp, ytemp, FLOOR);
            }
        }
        break;

    case 3: // west
        for (int ytemp = (y-ylen/2); ytemp < (y+(ylen+1)/2); ytemp++) {
            if (ytemp < 0 || ytemp > MAP_SIZE_Y) return 0;
            for (int xtemp = x; xtemp > (x-xlen); xtemp--) {
                if (xtemp < 0 || xtemp > MAP_SIZE_X) return 0;
                if (getTile(m, xtemp, ytemp) != EMPTY) return 0;
            }
        }

        for (int ytemp = (y-ylen/2); ytemp < (y+(ylen+1)/2); ytemp++) {
            for (int xtemp = x; xtemp > (x-xlen); xtemp--) {
                if (xtemp == x) setTile(m, xtemp, ytemp, WALL);
                else if (xtemp == (x-xlen+1)) setTile(m, xtemp, ytemp, WALL);
                else if (ytemp == (y-ylen/2)) setTile(m, xtemp, ytemp, WALL);
                else if (ytemp == (y+(ylen-1)/2)) setTile(m, xtemp, ytemp, WALL);
                else setTile(m, xtemp, ytemp, FLOOR);
            }
        }
        break;
    }
    return 1;
}

void genDungeon(Map* m, uint8_t rooms){
    for (int y = 0; y < MAP_SIZE_Y; y++) {
      for (int x = 0; x < MAP_SIZE_X; x++) {
        setTile(m, x, y, EMPTY);
        m->map[y][x].obj.type = NO_OBJ;
        m->map[y][x].vis = 0;
      }
    }
    //start with making a room in the middle, which we can start building upon
    makeRoom(m, MAP_SIZE_X/2, MAP_SIZE_Y/2, 8, 6, randRange(0,3));

    //keep count of the number of "NUM_ROOMS" we've made
    int currentFeatures = 1; //+1 for the first room we just made

    rooms = rooms < NUM_ROOMS ? NUM_ROOMS : rooms;
    //then we start the main loop
    for (int countingTries = 0; countingTries < MAX_ATTEMPTS && currentFeatures != rooms; countingTries++) {

      //start with a random wall
      int newx = 0;
      int xmod = 0;
      int newy = 0;
      int ymod = 0;
      int validTile = -1;

      //1000 chances to find a suitable object (room or corridor)..
      for (int testing = 0; testing < MAX_ATTEMPTS; testing++) {
        newx = randRange(1, MAP_SIZE_X-1);
        newy = randRange(1, MAP_SIZE_Y-2);
        validTile = -1;

        if (getTile(m, newx, newy) == WALL) {
          //check if we can reach the place
          if (getTile(m, newx, newy+1) == FLOOR) {
            validTile = 0; //
            xmod = 0;
            ymod = -1;
          }
          else if (getTile(m, newx-1, newy) == FLOOR) {
            validTile = 1; //
            xmod = +1;
            ymod = 0;
          }

          else if (getTile(m, newx, newy-1) == FLOOR) {
            validTile = 2; //
            xmod = 0;
            ymod = +1;
          }

          else if (getTile(m, newx+1, newy) == FLOOR) {
            validTile = 3; //
            xmod = -1;
            ymod = 0;
          }

          //check that we haven't got another door nearby, so we won't get alot of openings besides each other

          if (validTile > -1) {
            if (getTile(m, newx, newy+1) == DOOR) //north
              validTile = -1;
            else if (getTile(m, newx-1, newy) == DOOR)//east
              validTile = -1;
            else if (getTile(m, newx, newy-1) == DOOR)//south
              validTile = -1;
            else if (getTile(m, newx+1, newy) == DOOR)//west
              validTile = -1;
          }

          //if we can, jump out of the loop and continue with the rest
          if (validTile > -1) break;
        }
      }

      if (validTile > -1) {
        if (makeRoom(m, (newx+xmod), (newy+ymod), 8, 6, validTile)) {
          currentFeatures++; //add to our quota

          //then we mark the wall opening with a door
          setTile(m, newx, newy, DOOR);

          //clean up infront of the door so we can reach it
          setTile(m, (newx+xmod), (newy+ymod), FLOOR);
        }
      }
    }

    /*******************************************************************************
      *
      All done with the building, let's finish this one off

      *******************************************************************************/

    //sprinkle out the bonusstuff (stairs, chests etc.) over the map
    int newx = 0;
    int newy = 0;
    int ways = 0; //from how many directions we can reach the random spot from
    int state = 0; //the state the loop is in, start with the stairs

    while (state != 10) {
      for (int testing = 0; testing < 1000; testing++) {
        newx = randRange(1, MAP_SIZE_X-1);
        newy = randRange(1, MAP_SIZE_Y-2); //cheap bugfix, pulls down newy to 0<y<24, from 0<y<25
        //System.out.println("x: " + newx + "\ty: " + newy);
        ways = 4; //the lower the better

        //check if we can reach the spot
        if (getTile(m, newx, newy+1) == FLOOR) {
          //north
          if (getTile(m, newx, newy+1) != DOOR)
            ways--;
        }

        if (getTile(m, newx-1, newy) == FLOOR) {
          //east
          if (getTile(m, newx-1, newy) != DOOR)
            ways--;
        }

        if (getTile(m, newx, newy-1) == FLOOR) {
          //south
          if (getTile(m, newx, newy-1) != DOOR)
            ways--;
        }

        if (getTile(m, newx+1, newy) == FLOOR) {
          //west
          if (getTile(m, newx+1, newy) != DOOR)
            ways--;
        }

        if (ways == 0) {
          setTile(m, newx, newy, STAIR);
          state = 10;
          break;
        }
      }
    }
}//createDungeon
