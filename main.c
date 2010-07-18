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

// Include Standard files
#include "algorithm.h"
#include "config.h"
#include "constants.h"
#include "motor.h"
#include "pio.h"
#include "sensor.h"
#include "target.h"

/* Software entry point
 */
int main(void) {
    int i;
    m_initialize();
    
    //setDirection(LEFT, FORWARD);
/*    //setDirection(RIGHT, FORWARD);
    setDirection(LEFT, REVERSE);
    setDirection(RIGHT, REVERSE);

    PORTB &= ~(BIT(1) | BIT(2));
    pio_output_high(MOTOR_ENLEFT);
    pio_output_high(MOTOR_ENRIGHT);*/
    m_forwards();
    _delay_ms(1000.0);
    m_reverse();
    _delay_ms(1000.0);
    
    m_rotate(RIGHT);
    _delay_ms(1000.0);
    m_rotate(LEFT);
    _delay_ms(1000.0);
    
    m_turn(LEFT);
    _delay_ms(1000.0);
    m_turn(RIGHT);
    _delay_ms(1000.0);
    m_stop();


}
