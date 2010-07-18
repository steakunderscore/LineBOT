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
#include <avr/delay.h>

void adjustRight( void ) {
    unsigned int counter;
    m_turn(RIGHT);
    while (s_check(CENTER) != S_BLACK) {
        _delay_ms(10.0);
        counter++;
    }
    m_turn(LEFT);
    while (counter-- > 0) {
        _delay_ms(10.0);
    }
}

void adjustLeft( void ) {
    unsigned int counter;
    m_turn(LEFT);
    while (s_check(RIGHT) != S_BLACK) {
        _delay_ms(10.0);
        counter++;
    }
    m_turn(RIGHT);
    while (counter-- > 0) {
        _delay_ms(10.0);
    }
}

void goStraight( void ) {
    unsigned char center, right;

/*    if (s_check(LEFT) == S_BLACK) {
        turnLeft();
    }
*/
    center = s_check(CENTER);
    right = s_check(RIGHT);

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
