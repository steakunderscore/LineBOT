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
#include "delay.h"
#include "motor.h"
#include "pio.h"
#include "sensor.h"
#include "target.h"

/* Software entry point
 */
int main(void) {
    DDRC |= BIT(PC3) | BIT(PC4) | BIT(PC5);
    while (1) {
        PORTC &= ~(BIT(PC3) | BIT(PC4) | BIT(PC5));
        _delay_ms(1000.0);
        PORTC |= BIT(PC3) | BIT(PC4) | BIT(PC5);
        _delay_ms(1000.0);
    }
}
