
/*

File name: gps.c

Module: GPS

Description: GPS driver

Created:

Author: Haneen Ahmed Abdelfattah
        Mariam Ahmed Saeed Elsheikh
        MennaAllah Adel Khairat 
        Mohamed Hany Sarhan Ahmed


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
#include "EEPROM.h"

#define PI 3.14159265358979323846

char counter = 0;
char GPS_logname[]="GPRMC";
double distance = 0;
 char counter;

double latitude [100];
double longitude [100];
double new_latitude [100];
double new_longitude [100];

#define  EARTH_RADIUS  6371000

 float64 DEC_TO_RAD (double DEC)
{
        return (float64) ( (DEC*PI) / (180) );
}

void GPS_read(double* latitude, double* longitude)
{
char NS, EW;
	int i;
char while_exit_flag = 0;
char msg_arr[280];
char status;
	char *tokens;
while (while_exit_flag == 0)
{
	UART1_ReceiveString(msg_arr);
	*msg_arr = (char)strstr(msg_arr, GPS_logname);
	if (msg_arr != '\0'){
		while_exit_flag = 1;
	}
}



*tokens = (char) strtok(msg_arr,",");
for(i=0;i<7;i++)
{
  tokens = strtok(NULL,",");
 switch(i)
 {
	case 2:
    latitude[counter]  = atof(tokens);
 
    break;

	case 3:
	NS  = *tokens;

	break;
	
	case 4:
	longitude[counter]   = atof(tokens);
	break;

	case 5:
	EW  = *tokens;

	break;

	default:
break;


	 }  
} 
 latitude[counter]  *= (NS == 'N')? 1:-1;
 longitude[counter]  *= (EW == 'E')? 1:-1;
 counter++;
}



void calc_distance (double* latitude, double* longitude)
{
  
  if(counter > 0)
  {
      distance += ( (acos((sin(DEC_TO_RAD(latitude[counter-1])) * sin(DEC_TO_RAD(latitude[counter]))) + (cos(DEC_TO_RAD(latitude[counter-1])) * cos(DEC_TO_RAD(latitude[counter]))) * (cos(DEC_TO_RAD(longitude[counter]) - DEC_TO_RAD(longitude[counter-1])))) * EARTH_RADIUS))  ;
      
  }
	
	
}


void save_eeprom (){
	EEPROM_Write (latitude, 0,(sizeof(latitude)/sizeof (double)));
 EEPROM_Write (longitude, sizeof(latitude),(sizeof(longitude)/sizeof (double)));

}

void send_uart0 (){


UART0_SendData ( latitude ,(sizeof(latitude)/sizeof (double)));
	UART0_SendData ( longitude ,(sizeof(longitude)/sizeof (double)));


}


void read_eeprom (){


EEPROMRead (new_latitude, 0,(int)(sizeof(new_latitude)/sizeof (double)));
 EEPROMRead (new_longitude,(int)(sizeof(new_latitude)) ,(int)(sizeof(new_longitude)/sizeof (double)));

}











