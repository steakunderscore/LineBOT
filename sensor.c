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

#include "sensor.h"


#include <avr/io.h>
#include <util/delay.h>

// Thresholds found 18/7 4:45
#define GREY_THRESH 140
#define WHITE_THRESH 240
#define S_TEST_PIN PIO_DEFINE(PORT_B, 7)
/*
ADCSRA
ADEN 7 enables ADC
ADSC 6 = start conversion
ADFR 5 = free runnning (dont want)
ADIF 4 = interupt flag (1 if complete) (dont want)
ADIE 3 = interupt enabler, this along with SREG I-bit enable ADC Interupt (dont want)
00000111 = prescalar selections, initial try no scaling

ADMUX
will try 
REFS1 7 = 0 ,
REFS0 6 = 0 (Vref is AREF Internal Vref off)

ADLAR 5 = 1 (left adjust) (want)
bit4 - 0
MUX3 3 = input selections
MUX2 2 = input selections
MUX1 1 = input selections
MUX0 0 = input selections

MUX3->0 :
0000 = ADC0
0001 = ADC1
0010 = ADC2
0011 = ADC3
0100 = ADC4
0101 = ADC5
0110 = ADC6
0111 = ADC7 - check to see which pins using.'
*/


/*static uint8_t s_left_white; //white threshold for white sensor, calculated from initialisation
static uint8_t s_right_white;
static uint8_t s_centre_black;*/

uint8_t s_check(uint8_t sensor)
{
    uint8_t s_result= 0;
    uint8_t s_adc = (uint8_t)(((uint16_t)s_value(sensor) + (uint16_t)s_value(sensor) + (uint16_t)s_value(sensor) + (uint16_t)s_value(sensor)) >> 2);
      
    
    if(s_adc < GREY_THRESH)
        s_result = S_BLACK;
    else if(s_adc < WHITE_THRESH)
        s_result = S_GREY;
    else
        s_result = S_WHITE;
    
    return s_result;
}

uint8_t s_value(uint8_t sensor)
{
    
    switch (sensor) {
        case RIGHT:  ADMUX =  BIT(ADLAR);              break; // RIGHT  = ADC0 = 0000   ADLAR = 1
        case CENTER: ADMUX = (BIT(ADLAR) | BIT(MUX0)); break; // CENTER = ADC1 = 0001
        case LEFT:   ADMUX = (BIT(ADLAR) | BIT(MUX1)); break; // LEFT   = ADC2 = 0010
    }
  
    
    ADCSRA |= BIT(ADSC); // starts ADC
    
    while(!(ADCSRA & BIT(ADIF))) {
        //waits for ADC CONVERSION
    }
    
    ADCSRA |= BIT(ADIF);

    return ADCH;
}

void s_test(uint8_t sensor)
{
    DDRB |= 1;
    if (s_check(sensor) == S_GREY)
        PORTB |= 1;
    else
        PORTB &= ~1;
}
    


void s_initialise()
{
    ADCSRA |= BIT(ADEN);
   /* uint16_t s_average = 0;
    uint8_t s_index
    for(i = 0; i <= 10; i++)
    {
        s_average = s_average + s_value(LEFT);
    }    
    s_left_white = s_average / 10;
    
    s_average = 0;
    for(i = 0; i <= 10; i++)
    {
        s_average = s_average + s_value(CENTER);
    }    
    s_centre_black = s_average / 10;
    
    s_average = 0;
    for(i = 0; i <= 10; i++)
    {
        s_average = s_average + s_value(RIGHT);
    }    
    s_centre_black = s_average / 10;*/
}
