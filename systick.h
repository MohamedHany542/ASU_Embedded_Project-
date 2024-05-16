#include <stdint.h>
#ifndef Systick_H
#define Systick_H

void SysTick_Init(void);
void SysTick_Wait(uint32_t delay);
void delay_one_sec(void);
	
#endif