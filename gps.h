/*
* file name: gps.h
*description: header file for GPS module
 * 
 *  Author: shahd ahmed
 Mariam Ahmed Saeed Elsheikh
 */ 
#include "STD_Types.h"
#ifndef GPS_H_
#define GPS_H_


void GPS_read(double* latitude, double* longitude);
void save_eeprom ();
void send_uart0 ();
void read_eeprom ();
void calc_distance (double* latitude, double* longitude);



#endif /* GPS_H_ */