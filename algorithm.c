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

void findGray() {
    if (s_check(LEFT) == S_GREY /*&& (s_check(RIGHT)  == S_GREY || s_check(CENTER) == S_GREY )*/)  {
       m_stop();
       while (1) {
          PORTB |= 1;
          _delay_ms(1000.0);
          PORTB &= ~1;
          _delay_ms(1000.0);
       }
    }
}

void adjust( unsigned char direction1, unsigned char direction2, unsigned char sensor ) {
    unsigned int counter = 0;

    m_turn(direction1);
    while (s_check(sensor) == S_WHITE) {
        _delay_ms(10.0);
        counter++;
    }
    if (s_check(sensor) == S_GREY)
        findGray();

    counter = counter >> 1;

    m_turn(direction2);
    while (counter-- > 0) {
        if (s_check(sensor) == S_GREY)
            findGray();
        _delay_ms(10.0);
    }
}

void turnRight( void ) {
    m_stop();
    _delay_ms(100.0);
    m_forwards();
    _delay_ms(5.0);
    m_stop();
    _delay_ms(100.0);
    if (s_check(CENTER) == S_WHITE && s_check(RIGHT) == S_WHITE) {
        m_rotate(RIGHT);
        _delay_ms(900.0);
        _delay_ms(30.0);
        m_stop();
        if (s_check(CENTER) == S_WHITE && s_check(RIGHT) == S_WHITE) {
          m_forwards();
          _delay_ms(400.0);
          m_rotate(RIGHT);
          _delay_ms(800.0);
          _delay_ms(30.0);
          m_stop();
        }
    }
}

void turnLeft( void ) {
    m_rotate(LEFT);
    _delay_ms(900.0);
    _delay_ms(30.0);
    m_stop();
}

void goStraight( void ) {
    unsigned char center = S_BLACK,
                  right  = S_BLACK,
                  left   = S_WHITE;

    m_forwards();
    _delay_ms(50.0);
    while (center == S_BLACK && right == S_BLACK && left == S_WHITE) {
        center = s_check(CENTER);
        right = s_check(RIGHT);
        left = s_check(LEFT);
    }
    if (center == S_GREY || right == S_GREY) {
        findGray();
    }
    _delay_ms(200.0);
    center = s_check(CENTER);
    right = s_check(RIGHT);
    left = s_check(LEFT);
    if (center == S_GREY || right == S_GREY) {
        findGray();
    }

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
