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

void success() {
    // Celebrate
}

// Use true for left edge, false for right edge.
// Returns true for back on track, false if there is a problem.
unsigned char checkForStraight(unsigned char direction, unsigned char checkOther) {
    unsigned char firstDirection = direction ? LEFT  : RIGHT;
    unsigned char otherDirection = direction ? RIGHT : LEFT;
    
    m_stop();

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
}

void straightAhead() {
    m_straight();
    while (1) {
        if (s_check(CENTER) == S_GRAY) {
            m_stop();
            success();
        }

        if (s_check(CENTER) == S_WHITE) {
            m_straight(20);

            if (s_check(CENTER) == S_WHITE)
                turnAround();

            m_straight();
        }
        
        if (s_check(LEFT) != S_WHITE && !checkForStraight(true)) {
                //We're at a lefthand corner, a lefthand T junction or a cross junction.
                turnLeft();
        }

        if (s_check(RIGHT) != S_WHITE && !checkForStraight(false)) {
                //We're at a righthand corner, a righthand T junction or a cross junction.
        }
    }
}

