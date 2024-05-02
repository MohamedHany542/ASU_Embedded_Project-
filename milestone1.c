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
	
unsigned char distance = 100;

while (1){
	
if (BIT_IS_CLEAR(GPIO_PORTF_DATA_REG,SW1_MASK) && (distance >= 100) )
{
	
	GREEN_LED_out ( green_led ); // if switch is pressed the led is on
	
}
	else
	{
	  /********* Do Nothing  *******/

    }
	
	}
	

		}
