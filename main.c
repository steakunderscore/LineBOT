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
    m_initialize();
    pio_output_high (MOTOR_DRRIGHT1);
    pio_output_low  (MOTOR_DRRIGHT2);
    while (1) {
        pio_output_high (MOTOR_ENRIGHT);
        _delay_ms(1000.0);
        pio_output_low  (MOTOR_ENRIGHT);
        _delay_ms(1000.0);
    }
}
