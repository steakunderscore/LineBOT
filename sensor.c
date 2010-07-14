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

#define GREY_THRESH 128     // NOTE: these are currently might as well be random numbers and assume that complete blackness = 0, white = 256
#define WHITE_THRESH 192
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

static uint8_t s_left_white; //white threshold for white sensor, calculated from initialisation
static uint8_t s_right_white;
static uint8_t s_centre_black;

uint8_t s_check(uint8_t sensor)
{
    uint8_t s_result= 0;
    uint8_t s_adc = s_value(sensor);                       //check addresses are correct
      
    
    if(s_adc < GREY_THRESH)
    {    
        s_result = S_BLACK;
    }
    else if(s_adc < WHITE_THRESH)
    {
        s_result = S_GREY;
    }    
    else
        s_result = S_WHITE;
    
    return s_result;
}

uint8_t s_value(uint8_t sensor)
{
    
    if(sensor == LEFT) 
    {
        ADMUX = (BIT(ADLAR) | BIT(MUX1));
    }
    
    else if(sensor == RIGHT)
    {
        ADMUX = BIT(ADLAR); //set for right sensor ADLAR = 1, fills ADHC before ADLC
    }
    
    else if(sensor == CENTER)
    {
        ADMUX = (BIT(ADLAR)|BIT(MUX0));
    }
    
    ADCSRA = ADCSRA | BIT(ADSC); // starts ADC
    
    while((ADCSRA & BIT(ADSC)) & BIT(ADSC)) //waits for ADC CONVERTION
    {
        continue;
    }
    
    return ADCH;
}

void s_test(uint8_t sensor)
{
    
    pio_config_set(S_TEST_PIN, PIO_OUTPUT);       //setup out put pin PB7 (pin 10)
    uint8_t s_colour = s_value(sensor);
    uint8_t s_index = 0;
    pio_output_high (S_TEST_PIN);    //sets pin 10 high
    for(s_index = 0; s_index < 256; s_index++)
    {
        if(s_index >= s_colour)
        {
            pio_output_low(S_TEST_PIN); //sets pin 10 low.
        }
    }
}
    

void s_initialise()
{
    ADCSRA = BIT(ADEN);
    
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