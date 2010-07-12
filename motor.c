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
       TCCR1 - Timer Counter Control Register (TIMER1)
       -----------------------------------------------
       BITS DESCRIPTION

       TCCR1A
       NO:   NAME   DESCRIPTION
       --------------------------
       BIT 0 : WGM10 [SET to 1]
       BIT 1 : WGM11 [SET to 0]
       BIT 2 : Don't care
       BIT 3 : Don't care
       BIT 4 : COM1B0 Invert selection           [SET to 0]
       BIT 5 : COM1B1 Enable OC1B PWM            [SET to 1]
       BIT 6 : COM1A0 Invert selection           [SET to 0]
       BIT 7 : COM1A1 Enable OC1A PWM            [SET to 1]
       
       TCCR1B
       NO:   NAME   DESCRIPTION
       --------------------------
       BIT 0 : CS10 [SET to 0]
       BIT 1 : CS11 [SET to 1]
       BIT 2 : CS12 [SET to 0]
       BIT 3 : WGM12 [SET to 1]
       BIT 4 : WGM13 [SET to 0]
       Rest of bits we don't care about
       
       
       The above settings are for
       --------------------------
       
       Timer Clock = CPU Clock/8
       Mode        = Fast PWM
       PWM Output  = Non Inverted
       Outputs     = OC1A and OC1B

     */

    TCCR1A = BIT(WGM10) | BIT(COM1B1) | BIT(COM1A1);
    TCCR1B = BIT(CS11) | BIT(WGM12);

    // Set OC1A and OC1B pins as the outputs.

    //TODO: Im unsure about this line
    DDRB|=(1<<PB1)|(1<<PB2);

    //Set the output to off.
    OC1A=0;
    OC1B=0;

    // Zero the counter
    TCNT1 = 0;
}

void m_turn(unsigned char direction) {
    // Stop the motors first to stop jittering
    OC1A = 0xFF;
    OC1B = 0xFF;
    if (direction == LEFT) {
        // Set the motors in opposite directions
        PD0 = 0;
        PD1 = 1;
    }
    else if (direction == RIGHT) {
        // Set the motors in opposite directions
        PD0 = 1;
        PD1 = 0;
    }
    // turn both the motors on
    OC1A = 0xFF;
    OC1B = 0xFF;
}

void m_foward(uint8_t speed) {
    // Set both motors in forward direction
    PD0 = 1;
    PD1 = 1;

    // Adjust the motor speeds.
    OC1A=speed;
    OC1B=speed;
}

void m_reverse(uint8_t speed) {
    // Set both motors in forward direction
    PD0 = 0;
    PD1 = 0;

    // Adjust the motor speeds.
    OC1A=speed;
    OC1B=speed;
}
