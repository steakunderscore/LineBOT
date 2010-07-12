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
#ifndef SENSOR_H
#define SENSOR_H

#include "config.h"
#include "constants.h"

#define S_WHITE ((unsigned char) 1)
#define S_BLACK ((unsigned char) 2)
#define S_GREY  ((unsigned char) 3)

/**Checks the given sensor and returns S_WHITE, S_BLACK or S_GREY depending on the result.
@param sensor the identifier for the sensor (LEFT, RIGHT, CENTER)
@returns S_WHITE (1), S_BLACK (2), S_GREY (3)
*/
unsigned char s_check(unsigned char sensor);


/** calculate raw sensor value from ADC
@param sensor the identifier for the sensor (LEFT, RIGHT, CENTER)
@returns 8-bit sensor value
*/
uint8_t s_value(uint8_t sensor)

/**initialises ADC ready for conversions, attempts a calibration of the sensors
*/
void s_initialise(void);

#endif
