/******************************************************************************
*
* Module: Gpt
*
* File Name: Gpt.h
*
* Description: Header file for TM4C123GH6PM Microcontroller - SysTick Timer Driver.
*
* Author: Iyad Wael
******************************************************************************/

#ifndef GPT_H_
#define GPT_H_

#include "Std_Types.h"

/*******************************************************************************
 *                      Pre-Proccessor Macros                                  *
 *******************************************************************************/

#define SYSTICK_PRIORITY_MASK  0x1FFFFFFF
#define SYSTICK_INTERRUPT_PRIORITY  3
#define SYSTICK_PRIORITY_BITS_POS   29
#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 364


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/


/************************************************************************************
* Service Name: SysTick_Start
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Tick_Time - Time in miliseconds
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the SysTick Timer configuration to count n miliseconds:
*              - Set the Reload value
*              - Enable SysTick Timer with System clock 16Mhz
*              - Enable SysTick Timer Interrupt and set its priority
************************************************************************************/
void SysTick_Start(uint16 Tick_Time);

/************************************************************************************
* Service Name: SysTick_Stop
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Stop the SysTick Timer.
************************************************************************************/
void SysTick_Stop(void);

/************************************************************************************
* Service Name: SysTick_SetCallBack
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Ptr2Func - Call Back function address
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the SysTick Timer call back
************************************************************************************/
void SysTick_SetCallBack(void (*Ptr2Func)(void));

/************************************************************************************
* Service Name: _delay_ms
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Long Long (delay time in milliseconds)
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the SysTick delay
************************************************************************************/

void _delay_ms(unsigned long long n)
{
    volatile uint64 count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}

#endif /* GPT_H */


#endif /* GPT_H_ */
