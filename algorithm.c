/*
 * Authors:
 *      Wim Looman
 *      Henry Jenkins
 *      Kate Markman
 *      Ben Snalam
 * Copyright:
 *      Copyright (c) 2010 Wim Looman, Henry Jenkins, Kate Markman, Ben Snalam
 * License:
 *      GNU General Public License (see LICENSE in root folder)
 */

#include "algorithm.h"

#define UNKNOWN  ((unsigned char) 0)

// The types of the cells.
#define STRAIGHT ((unsigned char) 1)
#define CORNER   ((unsigned char) 2)
#define T_JUNCT  ((unsigned char) 3)
#define CROSS    ((unsigned char) 4)

/* The orientation of the cells, use the following tables to determine the layouts:
 *
 * STRAIGHT piece:
 *  NORTH/SOUTH EAST/WEST
 *    +-----+    +-----+
 *    | | | |    |     |
 *    | | | |    |-----|
 *    | | | |    |     |
 *    | | | |    |-----|
 *    | | | |    |     |
 *    +-----+    +-----+
 * CORNER piece:
 *   EAST    NORTH   WEST    SOUTH
 *  +-----+ +-----+ +-----+ +-----+
 *  |     | | | | | | | | | |     |
 *  | +---| | | +-| |-+ | | |---+ |
 *  | |   | | |   | |   | | |   | |
 *  | | +-| | +---| |---+ | |-+ | |
 *  | | | | |     | |     | | | | |
 *  +-----+ +-----+ +-----+ +-----+
 * T_JUNCT piece:
 *   EAST    NORTH   WEST    SOUTH
 *  +-----+ +-----+ +-----+ +-----+
 *  | | | | | | | | | | | | |     |
 *  | | +-| |-+ +-| |-+ | | |-----|
 *  | |   | |     | |   | | |     |
 *  | | +-| |-----| |-+ | | |-+ +-|
 *  | | | | |     | | | | | | | | |
 *  +-----+ +-----+ +-----+ +-----+
 * CROSS doesn't matter:
 *  NORTH/SOUTH/EAST/WEST
 *         +-----+
 *         | | | |
 *         |-+ +-|
 *         |     |
 *         |-+ +-|
 *         | | | |
 *         +-----+
 */
#define NORTH ((unsigned char) 1)
#define EAST  ((unsigned char) 2)
#define WEST  ((unsigned char) 3)
#define SOUTH ((unsigned char) 4)

typedef struct cell {
    unsigned char type;
    unsigned char orient;
} Cell;

static struct loc {
    unsigned char x;
    unsigned char y;
    unsigned char orient;
} location = {50, 50, NORTH};

static Cell map[100][100];


void determineCell() {

}




/*
void straightAhead() {
    m_straight();
    
    while (s_check(LEFT) == S_WHITE && s_check(RIGHT) == S_WHITE) {
        // DO NOTHING
    }
    
    m_stop();
    
    if (!checkForStraight(true)) {
        //We're at a lefthand corner, a lefthand T junction or a cross junction.
        if (!checkFor
    }
    else if (!checkForStraight(false)) {
        //We're at a righthand corner, a righthand T junction or a cross junction.
    }
}

// Use true for left edge, false for right edge.
// Returns true for back on track, false if there is a problem.
unsigned int checkForStraight(unsigned int direction, unsigned int checkOther) {
    unsigned int firstDirection = direction ? LEFT  : RIGHT;
    unsigned int otherDirection = direction ? RIGHT : LEFT;
    
    if (s_check(firstDirection) == S_BLACK && s_check(otherDirection) == S_WHITE) {
        m_turn(firstDirection);
        while (s_check(firstDirection) == S_BLACK && s_check(otherDirection) == S_WHITE) {
            // DO NOTHING
        }
        m_stop();
        
        if (s_check(firstDirection) == S_WHITE && s_check(otherDirection) == S_WHITE) {
            return true;
        }
        if (s_check(firstDirection) == S_BLACK && s_check(otherDirection) == S_WHITE) {
            return false;
        }
    }
    else {
        return true;
    }
}*/
