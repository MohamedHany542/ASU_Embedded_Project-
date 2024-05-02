#include "Common_Macros.h"
#include "Compiler.h"
#include "Platform_Types.h "
#include "Std_Types.h"
#include "tm4c123gh6pm_registers.h"
#define switch_mask  0x10
#define GREEN_LED_mask    0x08

void switch1_int(){        //PF4
	
	SYSCTL_RCGCGPIO_REG |=0x20;                   // enable port F clock
	while((SYSCTL_PRGPIO_REG & 0x20) ==0 );     //checking the clock is set 
	
	GPIO_PORTF_LOCK_REG =0x4C4F434B;
	GPIO_PORTF_CR_REG    |= switch_mask;               //enable p4 programming
	GPIO_PORTF_DIR_REG   &= ~switch_mask;              //set as input 
	GPIO_PORTF_AFSEL_REG &= ~switch_mask;              // disable ulternate function    
	GPIO_PORTF_PUR_REG   |= switch_mask;               // negative logic switch 
	GPIO_PORTF_DEN_REG   |= switch_mask;               // digital enable    
	GPIO_PORTF_AMSEL_REG &= ~switch_mask;              //disable analog function
	GPIO_PORTF_PCTL_REG  =0x000F0000;
		
	}

	void LED_Green_int(){         //pf3
		
	SYSCTL_RCGCGPIO_REG |=0x20;                   // enable port F clk
	while((SYSCTL_PRGPIO_REG & 0x20) ==0 );       //checking the clock is set 
	
	GPIO_PORTF_LOCK_REG =0x4C4F434B;
	GPIO_PORTF_CR_REG    |=  GREEN_LED_mask;              //enable p4 programming
	GPIO_PORTF_DIR_REG   |=  GREEN_LED_mask;              //set as OUTPUT
  GPIO_PORTF_DATA_REG  &=~ GREEN_LED_mask;              // initially off 
	GPIO_PORTF_AFSEL_REG &=~ GREEN_LED_mask;             // disable ulternate function    
	GPIO_PORTF_DEN_REG   |=  GREEN_LED_mask;              // digital enable    
	GPIO_PORTF_AMSEL_REG &=~ GREEN_LED_mask;             //disable analog function
	GPIO_PORTF_PCTL_REG  =0x0000F000;
		
	}
	//1
	unsigned char read_switch1(){
		
		return (GPIO_PORTF_DATA_REG & switch_mask) ;      //clear the previous switch data      // take new data 
	}
	//2
	void GREEN_LED_out (unsigned char LED_in ){
		
		//GPIO_PORTF_DATA_REG &=~ GREEN_LED_mask ;      //clear the previous LED data 
		GPIO_PORTF_DATA_REG |=LED_in ;        // take new data 
		 
	}
	
	void GREEN_LED_clear (void){
		
		GPIO_PORTF_DATA_REG &=~ GREEN_LED_mask ;      //clear the previous LED data 
		
		 
	}
