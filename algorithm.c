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

void straightAhead() {
    m_straight();
    
    while (s_check(S_LEFT) == S_WHITE && s_check(S_RIGHT) == S_WHITE) {
        /* DO NOTHING */
    }
    
    m_stop();
    
    checkForStraight(true);
    checkForStraight(false);
}

// Use true for left edge, false for right edge.
// Returns true for back on track, false if there is a problem.
unsigned int checkForStraight(unsigned int direction) {
    unsigned int firstDirection = direction ? LEFT  : RIGHT;
    unsigned int otherDirection = direction ? RIGHT : LEFT;
    
    if (s_check(firstDirection) == S_BLACK && s_check(otherDirection) == S_WHITE) {
        m_turn(firstDirection);
        while (s_check(firstDirection) == S_BLACK && s_check(otherDirection) == S_WHITE) {
            /* DO NOTHING */
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
}
