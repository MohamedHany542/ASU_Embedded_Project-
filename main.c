/*

File name: main.c



Description: Main fn

Created:

Author:
        Mariam Ahmed Saeed Elsheikh
       Habiba Essam Eldin

*/









#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h> 
#include "Common_Macros.h"
#include "Compiler.h"
#include "Platform_Types.h "
#include "Std_Types.h"
#include "uart_1.h"
#include "uart0.h"
#include "gps.h"
#include "LedSwitchInitH.h"
#include "Gpt.h"
#include "EEPROM.h"





const double Earth_Radius = 6371000;
#define PI 3.14159265358979323846
#define GREEN_LED_mask    0x08

extern char counter;
double distance = 0;
double latitude [100];
double longitude [100];

int main () {

	 // initializations 
	LED_Green_int();
	switch1_int();
	 UART0_Init();
	  EEPROM_init();
EEPROMMassErase();
	
	while (1){
do{
	//function to read the data and get latitude , magnitude arrays 
	GPS_read(latitude, longitude);
	
	calc_distance ( latitude,  longitude);
	SysTick_Start(1000);
	
	
	
	
} while (distance <100);
	
// when distance 100m is reached , green led is turned on 
if (distance == 100){
	
if (read_switch1() != switch_mask ){
	
		
	save_eeprom();
		
		
		
}
	
	GREEN_LED_out (GREEN_LED_mask );

	}


if( UART0_ReceiveByte() == 'U'){
read_eeprom();
send_uart0 ();

}
}
	
}






