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
    while (1) {
        m_forwards();
        _delay_ms(30.0);
        m_stop();
        _delay_ms(30.0);
    }
}
