/******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.h
 *
 * Description: Header file for the LED driver
 *
 * Author: Mahmoud Hussein
 *
 *******************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "Std_types.h"
#include "Dio.h"
#include "Port.h"
#include "Gpt.h"


typedef enum  {
    red = 0x02,
    blue = 0x04,
    green = 0x08,
    white = 0x0E,
    yellow = 0x0A,
    magenta = 0x06,
    cyan = 0x0C
} colors;

typedef struct 
{   
    colors RGB_Color ;
}RGB_Config;


void RGB_ON(RGB_Config *ptr);
void RGB_OFF(void);
#endif /* LED_H_ */