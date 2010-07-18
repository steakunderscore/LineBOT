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
        _delay_ms(10.0);
        counter++;
    }
    m_turn(direction2);
    while (counter-- > 0) {
        _delay_ms(10.0);
    }
}
void adjustRight( void ) {
    adjust(RIGHT, LEFT, CENTER);
}

void adjustLeft( void ) {
    adjust(LEFT, RIGHT, CENTER);
}

void goStraight( void ) {
    unsigned char center = S_BLACK,
                  right  = S_BLACK;

    m_forwards();
    while (center == S_BLACK && right == S_BLACK) {
        center = s_check(CENTER);
        right = s_check(RIGHT);
    }

    if (center != S_BLACK) {
        adjustRight();
    }
    else if (right != S_BLACK) {
        adjustLeft();
    }
}

void a_start( void ) {
    while (1) {
        goStraight();
    }
}
