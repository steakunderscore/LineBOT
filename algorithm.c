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

#define true 0
#define false 1

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
void checkForStraight(int direction) {
    unsigned int firstSensor = direction ? S_LEFT  : S_RIGHT;
    unsigned int otherSensor = direction ? S_RIGHT : S_LEFT;
    
    unsigned int firstDirection = direction ? M_LEFT  : M_RIGHT;
    unsigned int otherDirection = direction ? M_RIGHT : M_LEFT;
    
    if (s_check(firstSensor) == S_BLACK && s_check(otherSensor) == S_WHITE) {
        m_turn(firstDirection);
        while (s_check(firstSensor) == S_BLACK && s_check(otherSensor) == S_WHITE) {
            /* DO NOTHING */
        }
        m_stop();
        
        if (s_check(firstSensor) == S_WHITE && s_check(otherSensor) == S_WHITE) {
            return true;
        }
        if (s_check(firstSensor) == S_BLACK && s_check(otherSensor) == S_WHITE) {
            return false;
        }
    }
    else {
        return true;
    }
}