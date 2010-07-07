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

#include "motor.h"

#include <avr/io.h>
#include <util/delay.h>

void m_initialize( void )
{
    /*
       TCCR0 - Timer Counter Control Register (TIMER0)
       -----------------------------------------------
       BITS DESCRIPTION


       NO:   NAME   DESCRIPTION
       --------------------------
       BIT 7 : FOC0   Force Output Compare [Not used in this]
       BIT 6 : WGM00  Wave form generartion mode [SET to 1]
       BIT 5 : COM01  Compare Output Mode        [SET to 1]
       BIT 4 : COM00  Compare Output Mode        [SET to 0]
       
       BIT 3 : WGM01  Wave form generation mode [SET to 1]
       BIT 2 : CS02   Clock Select               [SET to 0]
       BIT 1 : CS01   Clock Select               [SET to 1]
       BIT 0 : CS00   Clock Select               [SET to 1]
       
       The above settings are for
       --------------------------
       
       Timer Clock = CPU Clock/64
       Mode        = Fast PWM
       PWM Output  = Non Inverted

     */


    TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00)|(1<<CS01);

    // Set OC1A and OC1B pins as the outputs.

    DDRB|=(1<<PB1)|(1<<PB2);

    //Set the output to off.
    OC1A=0;
    OC1B=0;
}

void m_foward(uint8_t speed) {
    // Set both motors in foward direction
    PD0 = 1;
    PD1 = 1;

    // Adjust the motor speeds.
    OC1A=speed;
    OC1B=speed;
}

void m_reverse(uint8_t speed) {
    // Set both motors in foward direction
    PD0 = 0;
    PD1 = 0;

    // Adjust the motor speeds.
    OC1A=speed;
    OC1B=speed;
}
