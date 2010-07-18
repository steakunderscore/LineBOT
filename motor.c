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

void setDirection (unsigned char motor, unsigned char direction) {
    switch (motor) {
        case LEFT:
            switch (direction) {
                case REVERSE:
                    pio_output_low(MOTOR_DRLEFT1);
                    pio_output_high(MOTOR_DRLEFT2);
                    break;
                case FORWARD:
                    pio_output_low(MOTOR_DRLEFT2);
                    pio_output_high(MOTOR_DRLEFT1);
                    break;
            }
            break;
        case RIGHT:
            switch (direction) {
                case REVERSE:
                    pio_output_low(MOTOR_DRRIGHT1);
                    pio_output_high(MOTOR_DRRIGHT2);
                    break;
                case FORWARD:
                    pio_output_low(MOTOR_DRRIGHT2);
                    pio_output_high(MOTOR_DRRIGHT1);
                    break;
            }
            break;
    }
}

void m_initialize( void )
{
    /* Setup the output for the motor direction control */
    pio_config_set (MOTOR_DRLEFT1, PIO_OUTPUT);
    pio_config_set (MOTOR_DRLEFT2, PIO_OUTPUT);
    pio_config_set (MOTOR_DRRIGHT1, PIO_OUTPUT);
    pio_config_set (MOTOR_DRRIGHT2, PIO_OUTPUT);
    
    pio_config_set (MOTOR_ENLEFT, PIO_OUTPUT);
    pio_config_set (MOTOR_ENRIGHT, PIO_OUTPUT);
    
    pio_output_high (MOTOR_ENRIGHT);
    pio_output_high (MOTOR_ENLEFT);
}

void m_turn(unsigned char direction) {
    // Stop the motors first to stop jittering
    m_stop();

    //Make sure both of the motors are if forward direction
    
    switch (direction) {
        case LEFT:
            setDirection (RIGHT, FORWARD);
            break;
        case RIGHT:
            setDirection ( LEFT, FORWARD);
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
        setDirection ( LEFT, REVERSE);
        setDirection (RIGHT, FORWARD);
    }
    else if (direction == RIGHT) {
        // Set the motors in opposite directions
        setDirection ( LEFT, FORWARD);
        setDirection (RIGHT, REVERSE);
    }
}

void m_forwards( void ) {
    m_stop();
    // Set both motors in forwards direction
    setDirection ( LEFT, FORWARD);
    setDirection (RIGHT, FORWARD);

}

void m_forwardsD(unsigned char distance) {
    m_forwards();
    
    // Wait for a distance in mm time to shift
    _delay_ms(FOWARD_DELAY_TIME * distance);
    m_stop();
}

void m_reverse( void ) {
    m_stop();
    // Set both motors in reverse direction
    setDirection ( LEFT, REVERSE);
    setDirection (RIGHT, REVERSE);
}

void m_reverseD(unsigned char distance) {
    m_reverse();
    
    // Wait for a distance in mm time to shift
    _delay_ms(FOWARD_DELAY_TIME * distance);
    m_stop();
}

void m_stopMotor(unsigned char motor) {
    switch(motor) {
        case(LEFT):
            pio_output_low(MOTOR_DRLEFT1);
            pio_output_low(MOTOR_DRLEFT2);
        case(RIGHT):
            pio_output_low(MOTOR_DRRIGHT1);
            pio_output_low(MOTOR_DRRIGHT2);
    }
}
void m_stop( void ) {
    // Turn off both motors 
    m_stopMotor(LEFT);
    m_stopMotor(RIGHT);
    _delay_ms(10.0);
}

