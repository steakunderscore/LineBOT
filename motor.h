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

#include "constants.h"

// Initialize the motor controller interface
void m_initialize( void );

// Starts the robot turning on the spot in the specified direction.
void m_turn(unsigned char direction);

// Set the forward direction
void m_foward(uint8_t speed);

// Set the reverse direction
void m_reverse(uint8_t speed);
