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

#define FOWARD_DELAY_TIME 100

void m_initialize( void )
{
    /* Setup the output for the motor direction control */
    pio_config_set (MOTOR_DRLEFT, PIO_OUTPUT);
    pio_config_set (MOTOR_DRRIGHT, PIO_OUTPUT);
    
    pio_config_set (MOTOR_ENLEFT, PIO_OUTPUT);
    pio_config_set (MOTOR_ENRIGHT, PIO_OUTPUT);
}

void m_turn(unsigned char direction) {
    // Stop the motors first to stop jittering
    m_stop();

    //Make sure both of the motors are if forward direction
    pio_output_high (MOTOR_DRLEFT);
    pio_output_high (MOTOR_DRRIGHT);
    
    switch (direction) {
        case LEFT:
            pio_output_low (MOTOR_ENLEFT);
            pio_output_high (MOTOR_ENRIGHT);
            break;
        case RIGHT:
            pio_output_high (MOTOR_ENLEFT);
            pio_output_low (MOTOR_ENRIGHT);
            break;  
        default:
            break;
    }
}

void m_rotate(unsigned char direction) {
    // Stop the motors first to stop jittering
    m_stop();
    
    if (direction == LEFT) {
        // Set the motors in opposite directions
        pio_output_low (MOTOR_DRLEFT);
        pio_output_high (MOTOR_DRRIGHT);
    }
    else if (direction == RIGHT) {
        // Set the motors in opposite directions
        pio_output_high (MOTOR_DRLEFT);
        pio_output_low (MOTOR_DRRIGHT);
    }
    // turn both the motors on
    pio_output_high (MOTOR_ENLEFT);
    pio_output_high (MOTOR_ENRIGHT);
}

void m_forwards( void ) {
    // Set both motors in forwards direction
    pio_output_low (MOTOR_DRLEFT);
    pio_output_low (MOTOR_DRRIGHT);

    // Adjust the motor speeds to full speed
    pio_output_high (MOTOR_ENLEFT);
    pio_output_high (MOTOR_ENRIGHT);
}

void m_forwardsD(unsigned char distance) {
    int i;
    m_forwards();
    
    // Wait for a distance in mm time to shift
    for (i = 0; i < distance; i++) {
        _delay_ms(FOWARD_DELAY_TIME);
    }
    m_stop();
}

void m_reverse( void ) {
    // Set both motors in reverse direction
    pio_output_low (MOTOR_DRLEFT);
    pio_output_low (MOTOR_DRRIGHT);

    // Adjust the motor speeds.
    pio_output_high (MOTOR_ENLEFT);
    pio_output_high (MOTOR_ENRIGHT);
}

void m_reverseD(unsigned char distance) {
    int i;
    m_reverse();
    
    // Wait for a distance in mm time to shift
    for (i = 0; i < distance; i++) {
        _delay_ms(FOWARD_DELAY_TIME);
    }
    m_stop();
}

void m_stop( void ) {
    // Set PWM to be 0%
    pio_output_low (MOTOR_ENLEFT);
    pio_output_low (MOTOR_ENRIGHT);
}

