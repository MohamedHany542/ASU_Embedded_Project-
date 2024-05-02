/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBfg.h
 *
 * Description:  Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Iyad Wael Abou-Elmagd
 ******************************************************************************/

/*
 *  Software Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION     (1U)
#define PORT_PBCFG_SW_MINOR_VERSION     (0U)
#define PORT_PBCFG_SW_PATCH_VERSION     (0U)

/*
 *  AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION (3U)

#include"port.h"

/* AUTOSAR checking between Port_Cfg.h and Port.h Modules */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port.h does not match the expected version"
#endif

/* Software checking between Port_Cfg.h and Port.h Modules */
#if((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION )\
||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION )\
||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error"The SW version of Port.h does not match the expected version"
#endif


/*******************************************************************************
 *                   Configuration Structure Definition                        *
 *******************************************************************************/
const Port_ConfigType Port_Configuration =
{
 /**********************************************************************************************************************************
 *                                                     Port A                                                                      *
 **********************************************************************************************************************************/

                          /**************** Pin 0 ****************/
PORTA,PIN0,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTA_PIN0_MODE_CHANGE,PORTA_PIN0_DIR_CHANGE,

                         /**************** Pin 1 ****************/
PORTA,PIN1,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTA_PIN1_MODE_CHANGE,PORTA_PIN1_DIR_CHANGE,

                        /**************** Pin 2 ****************/
PORTA,PIN2,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTA_PIN2_MODE_CHANGE,PORTA_PIN2_DIR_CHANGE,

                       /**************** Pin 3 ****************/
PORTA,PIN3,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTA_PIN3_MODE_CHANGE,PORTA_PIN3_DIR_CHANGE,

                      /**************** Pin 4 ****************/
PORTA,PIN4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTA_PIN4_MODE_CHANGE,PORTA_PIN4_DIR_CHANGE,

                     /**************** Pin 5 ****************/
PORTA,PIN5,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTA_PIN5_MODE_CHANGE,PORTA_PIN5_DIR_CHANGE,

                    /**************** Pin 6 ****************/
PORTA,PIN6,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTA_PIN6_MODE_CHANGE,PORTA_PIN6_DIR_CHANGE,

                    /**************** Pin 7 ****************/
PORTA,PIN7,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTA_PIN7_MODE_CHANGE,PORTA_PIN7_DIR_CHANGE,


/**********************************************************************************************************************************
*                                                     Port B                                                                      *
**********************************************************************************************************************************/

                   /**************** Pin 0 ****************/
PORTB,PIN0,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTB_PIN0_MODE_CHANGE,PORTB_PIN0_DIR_CHANGE,

                  /**************** Pin 1 ****************/
PORTB,PIN1,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTB_PIN1_MODE_CHANGE,PORTB_PIN1_DIR_CHANGE,

                 /**************** Pin 2 ****************/
PORTB,PIN2,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTB_PIN2_MODE_CHANGE,PORTB_PIN2_DIR_CHANGE,

                /**************** Pin 3 ****************/
PORTB,PIN3,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTB_PIN3_MODE_CHANGE,PORTB_PIN3_DIR_CHANGE,

               /**************** Pin 4 ****************/
PORTB,PIN4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTB_PIN4_MODE_CHANGE,PORTB_PIN4_DIR_CHANGE,

               /**************** Pin 5 ****************/
PORTB,PIN5,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTB_PIN5_MODE_CHANGE,PORTB_PIN5_DIR_CHANGE,

               /**************** Pin 6 ****************/
PORTB,PIN6,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTB_PIN6_MODE_CHANGE,PORTB_PIN6_DIR_CHANGE,

              /**************** Pin 7 ****************/
PORTB,PIN7,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTB_PIN7_MODE_CHANGE,PORTB_PIN7_DIR_CHANGE,


/**********************************************************************************************************************************
*                                                     Port C                                                                      *
**********************************************************************************************************************************/


                          /**************** Pin 0 ****************/
PORTC,PIN0,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTC_PIN0_MODE_CHANGE,PORTC_PIN0_DIR_CHANGE,

                         /**************** Pin 1 ****************/
PORTC,PIN1,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTC_PIN1_MODE_CHANGE,PORTC_PIN1_DIR_CHANGE,

                         /**************** Pin 2 ****************/
PORTC,PIN2,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTC_PIN2_MODE_CHANGE,PORTC_PIN2_DIR_CHANGE,

                         /**************** Pin 3 ****************/
PORTC,PIN3,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTC_PIN3_MODE_CHANGE,PORTC_PIN3_DIR_CHANGE,

                        /**************** Pin 4 ****************/
PORTC,PIN4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTC_PIN4_MODE_CHANGE,PORTC_PIN4_DIR_CHANGE,

                        /**************** Pin 5 ****************/
PORTC,PIN5,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTC_PIN5_MODE_CHANGE,PORTC_PIN5_DIR_CHANGE,

                        /**************** Pin 6 ****************/
PORTC,PIN6,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTC_PIN6_MODE_CHANGE,PORTC_PIN6_DIR_CHANGE,

                       /**************** Pin 7 ****************/
PORTC,PIN7,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTC_PIN7_MODE_CHANGE,PORTC_PIN7_DIR_CHANGE,


/**********************************************************************************************************************************
*                                                     Port D                                                                      *
**********************************************************************************************************************************/


                          /**************** Pin 0 ****************/
PORTD,PIN0,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTD_PIN0_MODE_CHANGE,PORTD_PIN0_DIR_CHANGE,

                         /**************** Pin 1 ****************/
PORTD,PIN1,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTD_PIN1_MODE_CHANGE,PORTD_PIN1_DIR_CHANGE,

                         /**************** Pin 2 ****************/
PORTD,PIN2,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTD_PIN2_MODE_CHANGE,PORTD_PIN2_DIR_CHANGE,

                         /**************** Pin 3 ****************/
PORTD,PIN3,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTD_PIN3_MODE_CHANGE,PORTD_PIN3_DIR_CHANGE,

                        /**************** Pin 4 ****************/
PORTD,PIN4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTD_PIN4_MODE_CHANGE,PORTD_PIN4_DIR_CHANGE,

                        /**************** Pin 5 ****************/
PORTD,PIN5,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTD_PIN5_MODE_CHANGE,PORTD_PIN5_DIR_CHANGE,

                        /**************** Pin 6 ****************/
PORTD,PIN6,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTD_PIN6_MODE_CHANGE,PORTD_PIN6_DIR_CHANGE,

                       /**************** Pin 7 ****************/
PORTD,PIN7,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTD_PIN7_MODE_CHANGE,PORTD_PIN7_DIR_CHANGE,


/**********************************************************************************************************************************
*                                                     Port E                                                                      *
**********************************************************************************************************************************/


                          /**************** Pin 0 ****************/
PORTE,PIN0,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTE_PIN0_MODE_CHANGE,PORTE_PIN0_DIR_CHANGE,

                         /**************** Pin 1 ****************/
PORTE,PIN1,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTE_PIN1_MODE_CHANGE,PORTE_PIN1_DIR_CHANGE,

                         /**************** Pin 2 ****************/
PORTE,PIN2,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTE_PIN2_MODE_CHANGE,PORTE_PIN2_DIR_CHANGE,

                         /**************** Pin 3 ****************/
PORTE,PIN3,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTE_PIN3_MODE_CHANGE,PORTE_PIN3_DIR_CHANGE,

                        /**************** Pin 4 ****************/
PORTE,PIN4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTE_PIN4_MODE_CHANGE,PORTE_PIN4_DIR_CHANGE,

                        /**************** Pin 5 ****************/
PORTE,PIN5,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTE_PIN5_MODE_CHANGE,PORTE_PIN5_DIR_CHANGE,


/**********************************************************************************************************************************
*                                                     Port F                                                                      *
**********************************************************************************************************************************/


                          /**************** Pin 0 ****************/
PORTF,PIN0,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_LOW,OFF,PORTF_PIN0_MODE_CHANGE,PORTF_PIN0_DIR_CHANGE,

                         /**************** Pin 1 ****************/
PORTF,PIN1,PORT_PIN_MODE_DIO,PORT_PIN_OUT,PORT_PIN_INITIAL_LOW,OFF,PORTF_PIN1_MODE_CHANGE,PORTF_PIN1_DIR_CHANGE,

                         /**************** Pin 2 ****************/
PORTF,PIN2,PORT_PIN_MODE_DIO,PORT_PIN_OUT,PORT_PIN_INITIAL_LOW,OFF,PORTF_PIN2_MODE_CHANGE,PORTF_PIN2_DIR_CHANGE,

                         /**************** Pin 3 ****************/
PORTF,PIN3,PORT_PIN_MODE_DIO,PORT_PIN_OUT,PORT_PIN_INITIAL_LOW,OFF,PORTF_PIN3_MODE_CHANGE,PORTF_PIN3_DIR_CHANGE,

                        /**************** Pin 4 ****************/
PORTF,PIN4,PORT_PIN_MODE_DIO,PORT_PIN_IN,PORT_PIN_INITIAL_HIGH,PULL_UP,PORTF_PIN4_MODE_CHANGE,PORTF_PIN4_DIR_CHANGE,

};
