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
#include <util/delay.h>

void adjust( unsigned char direction1, unsigned char direction2, unsigned char sensor ) {
    unsigned int counter = 0;

    m_turn(direction1);
    while (s_check(sensor) != S_BLACK) {
        _delay_ms(1.0);
        counter++;
    }

    counter = counter >> 1;

    m_turn(direction2);
    while (counter-- > 0) {
        _delay_ms(1.0);
    }
}

void turnLeft( void ) {
    m_rotate(LEFT);
    while (s_check(LEFT) != S_BLACK) ;
}

void goStraight( void ) {
    unsigned char center = S_BLACK,
                  right  = S_BLACK,
                  left   = S_WHITE;

    m_forwards();
    while (center == S_BLACK && right == S_BLACK && left == S_WHITE) {
        center = s_check(CENTER);
        right = s_check(RIGHT);
    }

    if (center == S_WHITE) {
        adjust(RIGHT, LEFT, CENTER);
    }
    else if (right == S_WHITE) {
        adjust(LEFT, RIGHT, RIGHT);
    }
    else if (left == S_BLACK) {
        turnLeft();
    }
}

void a_start( void ) {
    while (1) {
        goStraight();
    }
}
