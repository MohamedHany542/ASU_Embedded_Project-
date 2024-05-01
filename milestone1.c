#include "Common_Macros.h"
#include "Compiler.h"
#include "Platform_Types.h "
#include "Std_Types.h"
#include "tm4c123gh6pm_registers.h"
#include "LedSwitchInitH.h"


unsigned char green_led = GREEN_LED_mask ;
unsigned char switch_press; 
unsigned char Prev_Switch;
	
int main (){
		
 switch1_int();  //initialize switch

 LED_Green_int();  // initialize green led
	

	
while (1){
	
switch_press = read_switch1();	// read switch

if (switch_press != switch_mask ) { 
	
	GREEN_LED_out ( green_led );                                   // if switch is pressed the led is on
	
}
	else {
	
	  GREEN_LED_clear ()   ;                              // if switch is pressed the led is on
	
}
	
	}
	

		}