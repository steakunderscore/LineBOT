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
#include "avr/delay.h"

void success( void ) {
    m_stop();
    // Celebrate
}

// Use true for left edge, false for right edge.
// Returns true for back on track, false if there is a problem.
unsigned char checkForStraight(unsigned char direction) {
    unsigned char firstDirection = direction ? LEFT  : RIGHT;
    unsigned char otherDirection = direction ? RIGHT : LEFT;
    
    m_stop();

    if (s_check(firstDirection) == S_BLACK && s_check(otherDirection) == S_WHITE) {
        m_rotate(firstDirection);
        while (s_check(firstDirection) == S_BLACK && s_check(otherDirection) == S_WHITE) {
            // DO NOTHING
        }
        m_stop();
        
        if (s_check(firstDirection) == S_WHITE) {
            return true;
        }
        if (s_check(firstDirection) == S_BLACK) {
            return false;
        }
    }
    else {
        return true;
    }
}

void turnAround( void ) {
    m_reverse();
    while (s_check(CENTER) == S_WHITE) {
        // DO NOTHING
    }
    m_reverseD(40);

    m_rotate(LEFT);
    while (s_check(LEFT) == S_WHITE) {
        // DO NOTHING
    }
    while (s_check(LEFT) == S_BLACK) {
        // DO NOTHING
    }

    m_stop();
}

void turnLeft( void ) {
    m_stop();

    m_turn(LEFT);
    while (s_check(RIGHT) == S_BLACK) {
        // DO NOTHING
    }

    m_stop();
}

void turnRight( void ) {
    m_stop();

    m_turn(RIGHT);
    while (s_check(LEFT) == S_BLACK) {
        // DO NOTHING
    }

    m_stop();
}

void testStraightAhead( void ) {
    m_stop();
    m_forwardsD(40);

    if (s_check(CENTER) == S_WHITE)
        turnAround();
}

void straightAhead( void ) {
    unsigned char left, center, right;
    while (1) {
        m_forwards();

        left = s_check(LEFT);
        center = s_check(CENTER);
        right = s_check(RIGHT);

        if (center == S_GREY) {
            m_stop();
            success();
        }

        if (center == S_WHITE) {
            testStraightAhead();
        }
        
        if (left != S_WHITE && !checkForStraight(true)) {
            //We're at a lefthand corner, a lefthand T junction or a cross junction.
            turnLeft();
        }

        if (right != S_WHITE && !checkForStraight(false)) {
            //We're at a righthand corner, a righthand T junction or a cross junction.
            testStraightAhead();
        }
        _delay_ms(30.0);
    }
}

void a_start( void ) {
    straightAhead();
}
