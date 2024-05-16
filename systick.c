#include "tm4c123gh6pm.h"
#include "io.h"
#include <stdint.h>
#include "systick.h"

void SysTick_Init(void){
NVIC_ST_CTRL_R = 0; // disable SysTick during setup
NVIC_ST_RELOAD_R = 0x00FFFFFF; // Maximum reload value
NVIC_ST_CURRENT_R = 0; 
NVIC_ST_CTRL_R = 0x00000005; // enable SysTick with core clock
}

// The delay parameter is in units of the 16 MHz core clock(62.5 ns)
void SysTick_Wait(uint32_t delay){
NVIC_ST_RELOAD_R = delay-1;
NVIC_ST_CURRENT_R = 0;
while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for flag
}
}

// Call this routine to wait for delay 1s
void delay_one_sec(void){
unsigned long i;
SysTick_Wait(16000000); // wait 1 s

}
