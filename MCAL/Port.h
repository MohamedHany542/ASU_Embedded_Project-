 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Iyad Wael Abou-Elmagd
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Iyad's ID = 888 :) */
#define PORT_VENDOR_ID    (888U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 *  Software Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION     (1U)
#define PORT_SW_MINOR_VERSION     (0U)
#define PORT_SW_PATCH_VERSION     (0U)

/*
 *  AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_AR_RELEASE_PATCH_VERSION (3U)

#include "Common_Macros.h"

#include "Std_Types.h"
/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

#include"Port_Cfg.h"

/* AUTOSAR checking between Port_Cfg.h and Port.h Modules */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_cfg.h does not match the expected version"
#endif

/* Software checking between Port_Cfg.h and Port.h Modules */
#if((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION )\
||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION )\
||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error"The SW version of Port_cfg.h does not match the expected version"
#endif



/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

#define NUMBER_PINS  ((uint8) 43)
#define NUMBER_MODES ((uint8) 12)

/* Description:Variable the holds the symbolic name of a port pin*/
typedef uint8 Port_PinType;

/* Description:Variable the holds the mode_ID of the pin*/
typedef uint8 Port_PinModeType;

/* Description: Enum to hold Port Number*/
typedef enum
{
 PORTA,PORTB,PORTC,PORTD,PORTE,PORTF
}Port_Number_Type;

/* Description: Enum to hold Pin Number*/
typedef enum
{
 PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7
}Pin_Number_Type;

/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirectionType ;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;


/* Description: Enum to hold the pin alternative mode  */
typedef enum
{
 PORT_PIN_MODE_DIO,PORT_PIN_MODE_ADC,PORT_PIN_MODE_CAN,PORT_PIN_MODE_SPI,PORT_PIN_MODE_I2C,PORT_PIN_MODE_UART,\
 PORT_PIN_MODE_PWM,PORT_PIN_MODE_GPT,PORT_PIN_MODE_USB,PORT_PIN_MODE_NMI
}Port_Pin_Initial_Mode;

/* Description: Enum to hold the pin initial level */
typedef enum
{
    PORT_PIN_INITIAL_LOW,PORT_PIN_INITIAL_HIGH
}Port_Pin_Initial_Level;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT
 *	3. the mode of the pin (DIO,CAN,UART,....)
 *  4. the direction of pin --> INPUT or OUTPUT
 *  5. the initial value on this pin(If configured ad Output)
 *  6. the internal resistor --> Disable, Pull up or Pull down
 *  7. the change in mode     (If Permissible)
 *  8. the change in direction(If Permissible)
 */
typedef struct 
{
    Port_Number_Type port_num;
    Pin_Number_Type  pin_num;
    Port_PinModeType mode;
    Port_PinDirectionType direction;
    Port_Pin_Initial_Level initial_level;
    Port_InternalResistor resistor;
    Port_PinType      change_mode;
    Port_PinType      change_dir;
}Port_Config_pins;

typedef struct
{
    Port_Config_pins port_Channels [NUMBER_PINS];
}Port_ConfigType;

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_Configuration;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module
************************************************************************************/
void Port_Init
(
 const Port_ConfigType *ConfigPtr
);

/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin (Port Pin ID number) , Direction (Port Pin Direction)
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description: Sets the port pin direction
************************************************************************************/
#if(STD_ON == PORT_SET_PIN_DIRECTION_API)

void Port_SetPinDirection
(
    Port_PinType Pin,
    Port_PinDirectionType Direction
 );

#endif
/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description: Refreshes port direction
************************************************************************************/
void Port_RefreshPortDirection(void);

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in):    None
* Parameters (inout): None
* Parameters (out):   versioninfo(Pointer to where to store the version information of this module)
* Return value:       None
* Description: Returns the version information of this module
************************************************************************************/
#if(STD_ON == PORT_VERSION_INFO_API)

void Port_GetVersionInfo
(
    Std_VersionInfoType* versioninfo
);

#endif
/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in):Pin (Port Pin ID number) , Mode (New Port Pin mode to be set on port pin)
* Parameters (inout): None
* Parameters (out):   None
* Return value:       None
* Description: Sets the port pin mode
************************************************************************************/
#if(STD_ON == PORT_SET_PIN_MODE_API)

void Port_SetPinMode
(
    Port_PinType Pin,
    Port_PinModeType Mode
);

#endif

#endif /* PORT_H */
