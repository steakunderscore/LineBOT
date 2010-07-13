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

// Starts the robot turning in the specified direction, this keeps the
// direction wheel still and drives the other wheel.
void m_turn(unsigned char direction);

// Starts the robot rotating in the specified direction, this drives the
// direction wheel in reverse and the other wheel fowards.
void m_rotate(unsigned char direction);

// Starts the robot moving forwards.
void m_forwards( void );

// Moves the robot forward approximately distance mm.
void m_forwardsD(unsigned char distance);

// Starts the robot moving backwards.
void m_reverse( void );

// Moves the robot backwards approximately distance mm.
void m_reverseD(unsigned char distance);

// Stops the robot.
void m_stop( void );
