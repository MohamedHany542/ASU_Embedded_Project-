/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description:  Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Iyad Wael Abou-Elmagd
 ******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 *  Software Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION     (1U)
#define PORT_CFG_SW_MINOR_VERSION     (0U)
#define PORT_CFG_SW_PATCH_VERSION     (0U)

/*
 *  AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION (3U)

/*******************************************************************************
 *                     Optional API's configuration                            *
 *******************************************************************************/
/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT      (STD_ON)

/* Pre-compile option for Set pin direction API */
#define PORT_SET_PIN_DIRECTION_API (STD_ON)

/* Pre-compile option for set pin mode API*/
#define PORT_SET_PIN_MODE_API      (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API      (STD_ON)


/*******************************************************************************
 *            Preprocessor Macros the set pin direction configuration          *
 *******************************************************************************/

/* Port A pins configuration*/
#define PORTA_PIN0_DIR_CHANGE        (STD_ON)
#define PORTA_PIN1_DIR_CHANGE        (STD_ON)
#define PORTA_PIN2_DIR_CHANGE        (STD_ON)
#define PORTA_PIN3_DIR_CHANGE        (STD_ON)
#define PORTA_PIN4_DIR_CHANGE        (STD_ON)
#define PORTA_PIN5_DIR_CHANGE        (STD_ON)
#define PORTA_PIN6_DIR_CHANGE        (STD_ON)
#define PORTA_PIN7_DIR_CHANGE        (STD_ON)

/* Port B pins configuration*/
#define PORTB_PIN0_DIR_CHANGE        (STD_ON)
#define PORTB_PIN1_DIR_CHANGE        (STD_ON)
#define PORTB_PIN2_DIR_CHANGE        (STD_ON)
#define PORTB_PIN3_DIR_CHANGE        (STD_ON)
#define PORTB_PIN4_DIR_CHANGE        (STD_ON)
#define PORTB_PIN5_DIR_CHANGE        (STD_ON)
#define PORTB_PIN6_DIR_CHANGE        (STD_ON)
#define PORTB_PIN7_DIR_CHANGE        (STD_ON)

/* Port C pins configuration*/
#define PORTC_PIN0_DIR_CHANGE        (STD_ON)
#define PORTC_PIN1_DIR_CHANGE        (STD_ON)
#define PORTC_PIN2_DIR_CHANGE        (STD_ON)
#define PORTC_PIN3_DIR_CHANGE        (STD_ON)
#define PORTC_PIN4_DIR_CHANGE        (STD_ON)
#define PORTC_PIN5_DIR_CHANGE        (STD_ON)
#define PORTC_PIN6_DIR_CHANGE        (STD_ON)
#define PORTC_PIN7_DIR_CHANGE        (STD_ON)

/* Port D pins configuration*/
#define PORTD_PIN0_DIR_CHANGE        (STD_ON)
#define PORTD_PIN1_DIR_CHANGE        (STD_ON)
#define PORTD_PIN2_DIR_CHANGE        (STD_ON)
#define PORTD_PIN3_DIR_CHANGE        (STD_ON)
#define PORTD_PIN4_DIR_CHANGE        (STD_ON)
#define PORTD_PIN5_DIR_CHANGE        (STD_ON)
#define PORTD_PIN6_DIR_CHANGE        (STD_ON)
#define PORTD_PIN7_DIR_CHANGE        (STD_ON)

/* Port E pins configuration*/
#define PORTE_PIN0_DIR_CHANGE        (STD_ON)
#define PORTE_PIN1_DIR_CHANGE        (STD_ON)
#define PORTE_PIN2_DIR_CHANGE        (STD_ON)
#define PORTE_PIN3_DIR_CHANGE        (STD_ON)
#define PORTE_PIN4_DIR_CHANGE        (STD_ON)
#define PORTE_PIN5_DIR_CHANGE        (STD_ON)

/* Port F pins configuration*/
#define PORTF_PIN0_DIR_CHANGE        (STD_OFF)
#define PORTF_PIN1_DIR_CHANGE        (STD_ON)
#define PORTF_PIN2_DIR_CHANGE        (STD_ON)
#define PORTF_PIN3_DIR_CHANGE        (STD_ON)
#define PORTF_PIN4_DIR_CHANGE        (STD_OFF)


/*******************************************************************************
 *            Preprocessor Macros the set pin mode configuration               *
 *******************************************************************************/

/* Port A pins configuration*/
#define PORTA_PIN0_MODE_CHANGE        (STD_ON)
#define PORTA_PIN1_MODE_CHANGE        (STD_ON)
#define PORTA_PIN2_MODE_CHANGE        (STD_ON)
#define PORTA_PIN3_MODE_CHANGE        (STD_ON)
#define PORTA_PIN4_MODE_CHANGE        (STD_ON)
#define PORTA_PIN5_MODE_CHANGE        (STD_ON)
#define PORTA_PIN6_MODE_CHANGE        (STD_ON)
#define PORTA_PIN7_MODE_CHANGE        (STD_ON)

/* Port B pins configuration*/
#define PORTB_PIN0_MODE_CHANGE        (STD_ON)
#define PORTB_PIN1_MODE_CHANGE        (STD_ON)
#define PORTB_PIN2_MODE_CHANGE        (STD_ON)
#define PORTB_PIN3_MODE_CHANGE        (STD_ON)
#define PORTB_PIN4_MODE_CHANGE        (STD_ON)
#define PORTB_PIN5_MODE_CHANGE        (STD_ON)
#define PORTB_PIN6_MODE_CHANGE        (STD_ON)
#define PORTB_PIN7_MODE_CHANGE        (STD_ON)

/* Port C pins configuration*/
#define PORTC_PIN0_MODE_CHANGE        (STD_ON)
#define PORTC_PIN1_MODE_CHANGE        (STD_ON)
#define PORTC_PIN2_MODE_CHANGE        (STD_ON)
#define PORTC_PIN3_MODE_CHANGE        (STD_ON)
#define PORTC_PIN4_MODE_CHANGE        (STD_ON)
#define PORTC_PIN5_MODE_CHANGE        (STD_ON)
#define PORTC_PIN6_MODE_CHANGE        (STD_ON)
#define PORTC_PIN7_MODE_CHANGE        (STD_ON)

/* Port D pins configuration*/
#define PORTD_PIN0_MODE_CHANGE        (STD_ON)
#define PORTD_PIN1_MODE_CHANGE        (STD_ON)
#define PORTD_PIN2_MODE_CHANGE        (STD_ON)
#define PORTD_PIN3_MODE_CHANGE        (STD_ON)
#define PORTD_PIN4_MODE_CHANGE        (STD_ON)
#define PORTD_PIN5_MODE_CHANGE        (STD_ON)
#define PORTD_PIN6_MODE_CHANGE        (STD_ON)
#define PORTD_PIN7_MODE_CHANGE        (STD_ON)

/* Port E pins configuration*/
#define PORTE_PIN0_MODE_CHANGE        (STD_ON)
#define PORTE_PIN1_MODE_CHANGE        (STD_ON)
#define PORTE_PIN2_MODE_CHANGE        (STD_ON)
#define PORTE_PIN3_MODE_CHANGE        (STD_ON)
#define PORTE_PIN4_MODE_CHANGE        (STD_ON)
#define PORTE_PIN5_MODE_CHANGE        (STD_ON)

/* Port F pins configuration*/
#define PORTF_PIN0_MODE_CHANGE        (STD_OFF)
#define PORTF_PIN1_MODE_CHANGE        (STD_ON)
#define PORTF_PIN2_MODE_CHANGE        (STD_ON)
#define PORTF_PIN3_MODE_CHANGE        (STD_ON)
#define PORTF_PIN4_MODE_CHANGE        (STD_OFF)

#endif /* PORT_CFG_H_ */
