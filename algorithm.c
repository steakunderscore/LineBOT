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

    counter = counter >> 1;

    m_turn(direction2);
    while (counter-- > 0) {
        _delay_ms(10.0);
    }
}

void turnRight( void ) {
    m_stop();
    _delay_ms(120.0);
    if (s_check(CENTER) == S_WHITE && s_check(RIGHT) == S_WHITE) {
        m_rotate(RIGHT);
        _delay_ms(800.0);
        m_stop();
        if (s_check(CENTER) == S_WHITE && s_check(RIGHT) == S_WHITE) {
          m_forwards();
          _delay_ms(500.0);
          m_rotate(RIGHT);
          _delay_ms(800.0);
          m_stop();
        }
    }
}

void turnLeft( void ) {
    m_stop();
    _delay_ms(100.0);
    m_rotate(LEFT);
    _delay_ms(800.0);
    m_stop();
}

void goStraight( void ) {
    unsigned char center = S_BLACK,
                  right  = S_BLACK,
                  left   = S_WHITE;

    m_forwards();
    _delay_ms(100.0);
    while (center == S_BLACK && right == S_BLACK && left == S_WHITE) {
        center = s_check(CENTER);
        right = s_check(RIGHT);
        left = s_check(LEFT);
    }
    center = s_check(CENTER);
    right = s_check(RIGHT);
    left = s_check(LEFT);

    if (left == S_BLACK) {
        turnLeft();
    }
    else if (center == S_WHITE && right == S_WHITE) {
        turnRight();
    }
    else if (center == S_WHITE) {
        adjust(RIGHT, LEFT, CENTER);
    }
    else if (right == S_WHITE) {
        adjust(LEFT, RIGHT, RIGHT);
    }
}

void a_start( void ) {
    while (1) {
        goStraight();
    }
}
