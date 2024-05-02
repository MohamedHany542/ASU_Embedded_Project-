 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Iyad Wael Abou-Elmagd
 ******************************************************************************/

#include "Port_priv.h"
#include "tm4c123gh6pm_registers.h"

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

STATIC volatile uint32* PortGpio_Ptr = NULL_PTR;
STATIC const Port_Config_pins* portInit_Ptr = NULL_PTR;
STATIC uint8 Port_status = PORT_NOT_INITIALIZED;


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
void Port_Init(const Port_ConfigType *ConfigPtr)
{

    /* Enable clock for All PORTs and wait for clock to start */
        SYSCTL_RCGCGPIO_REG |= 0x3F;
        while(!(SYSCTL_PRGPIO_REG & 0x3F));

 boolean error_status = FALSE;

/* Check on det errors if Det error detection is enabled */
#if(STD_ON == PORT_DEV_ERROR_DETECT)

    if(NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,Port_Init_SID,PORT_E_PARAM_CONFIG);
        error_status = TRUE;

    }
    else

#endif
    {
        Port_status = PORT_INITIALIZED;
        portInit_Ptr = ConfigPtr -> port_Channels;
    }

/* Traversing on the array of structures of type Port_Config_pins to configure all MCU pins */
if(error_status == FALSE)
{

uint8 i;

for(i=0;i<NUMBER_PINS;i++)
{
    if(i == 16)
    {
        i = 20;
    }
    else
    {
        /* Do Nothing */
    }

    /*******************************************************************************
     *                       Selecting port number                                 *
     *******************************************************************************/

  switch(portInit_Ptr[i].port_num)
  {
  case PORTA:
      PortGpio_Ptr =  (volatile uint32*) GPIO_PORTA_BASE_ADDRESS;
      break;
  case PORTB:
      PortGpio_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS;
        break;
  case PORTC:
      PortGpio_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS;
        break;
  case PORTD:
      PortGpio_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS;
        break;
  case PORTE:
      PortGpio_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS;
        break;
  case PORTF:
      PortGpio_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS;
        break;
  default:
      /* Do Nothing */
        break;
  }

  /*******************************************************************************
   *                  Handling JTAG pins(PC0,PC1,PC2,PC3),PD7,PF0                    *
   *******************************************************************************/

  if(((PORTD==portInit_Ptr[i].port_num) && (PIN7==portInit_Ptr[i].pin_num))|| \
    ((PORTF==portInit_Ptr[i].port_num)  && (PIN0==portInit_Ptr[i].pin_num)))
  {
    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = LOCK_REG_PASS;                     /* Unlock the GPIOCR register */
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , portInit_Ptr[i].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
  }
  else if((PORTC==portInit_Ptr[i].port_num) && (portInit_Ptr[i].pin_num <= PIN3))
  {
      /* Do Nothing ...  this is the JTAG pins */

  }
  else
  {
      /* Do Nothing ... No need to unlock the commit register for this pin */
  }

  /*******************************************************************************
   *       Configuring Pins Directions,Initial Level (Output),Resistor(Input)    *
   *******************************************************************************/
  if(PORT_PIN_OUT == portInit_Ptr[i].direction)
      {
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,portInit_Ptr[i].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

          if(portInit_Ptr[i].initial_level == STD_HIGH)
          {
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , portInit_Ptr[i].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
          }
          else
          {
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , portInit_Ptr[i].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
          }
      }
      else if(PORT_PIN_IN == portInit_Ptr[i].direction)
      {
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,portInit_Ptr[i].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

          if(portInit_Ptr[i].resistor == PULL_UP)
          {
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , portInit_Ptr[i].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
          }
          else if(portInit_Ptr[i].resistor == PULL_DOWN)
          {
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) ,portInit_Ptr[i].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
          }
          else
          {
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) ,portInit_Ptr[i].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) ,portInit_Ptr[i].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
          }
}
      else
          {
              /* Do Nothing */
          }

  /*******************************************************************************
   *                          Configuring Pins Mode                              *
   *******************************************************************************/


  /***************************************Analog Modes*******************************************/

switch(portInit_Ptr[i].mode)
{
case PORT_PIN_MODE_ADC: /************************** ADC Mode Initialization******************************/
case PORT_PIN_MODE_USB: /************************** USB Mode Initialization******************************/

    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,portInit_Ptr[i].pin_num);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

    CLEAR_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num));         /* Clear corresponding bits to the bit in the PCTL Reg*/

    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,portInit_Ptr[i].pin_num);      /* Enable the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , portInit_Ptr[i].pin_num);     /* Disable the corresponding bit in the GPIODEN register to disable digital functionality on this pin */

    if(PORT_PIN_MODE_ADC == portInit_Ptr[i].mode)
    {
      INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_ADC_MASK);
    }
    else if(PORT_PIN_MODE_USB == portInit_Ptr[i].mode)
    {

       if((PORTB == portInit_Ptr[i].port_num) && (PIN1 >= portInit_Ptr[i].pin_num) || \
         (PORTD == portInit_Ptr[i].port_num) && (PIN5 >= portInit_Ptr[i].pin_num))
       {
           INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_USB_ANALOG_MASK); /* Insert the suitable mask in the PCTL register*/

       }
       else
       {
           /**************************Digital Pins in USB Module***************************************/
       }
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,portInit_Ptr[i].pin_num);      /* Disable the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) ,portInit_Ptr[i].pin_num);         /*  Enable the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
           INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_USB_DIGITAL_MASK); /* Insert the suitable mask in the PCTL register*/

       }

    else
    {
        /* Do Nothing */
    }

    break;

    /***************************************Digital Modes*******************************************/


    /************************** DIO Mode Initialization******************************/

    case PORT_PIN_MODE_DIO:
    case PORT_PIN_MODE_PWM:
    case PORT_PIN_MODE_GPT:
    case PORT_PIN_MODE_NMI:
    case PORT_PIN_MODE_UART:
    case PORT_PIN_MODE_SPI:
    case PORT_PIN_MODE_I2C:
    case PORT_PIN_MODE_CAN:

        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , portInit_Ptr[i].pin_num);      /* Disable the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , portInit_Ptr[i].pin_num);     /* Enable the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        CLEAR_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num));         /* Clear corresponding bits to the bit in the PCTL Reg*/
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , portInit_Ptr[i].pin_num);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */


        if(PORT_PIN_MODE_DIO == portInit_Ptr[i].mode) /************************** DIO Mode Initialization ******************************/
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , portInit_Ptr[i].pin_num);             /* Disable Alternative function for this pin by clearing the corresponding bit in GPIOAFSEL register */
        }

        else if(PORT_PIN_MODE_PWM == portInit_Ptr[i].mode) /************************** PWM Mode Initialization (M0) only ******************************/
        {
            INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_PWM_M0_MASK); /* Insert the suitable mask in the PCTL register*/

        }

        else if(PORT_PIN_MODE_GPT == portInit_Ptr[i].mode) /************************** GPT Mode Initialization ******************************/
        {
            INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_GPT_MASK); /* Insert the suitable mask in the PCTL register*/

        }

        else if(PORT_PIN_MODE_NMI == portInit_Ptr[i].mode) /************************** NMI Mode Initialization ******************************/
        {
            INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_NMI_MASK); /* Insert the suitable mask in the PCTL register*/
        }

        else if(PORT_PIN_MODE_UART == portInit_Ptr[i].mode) /************************** UART Mode Initialization ******************************/
         {
            if((PORTC == portInit_Ptr[i].port_num) && (PIN5 >= portInit_Ptr[i].pin_num))
            {
                INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_UART_MASK_2); /* Insert the suitable mask in the PCTL register*/
            }

            else
            {
                INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_UART_MASK_1); /* Insert the suitable mask in the PCTL register*/
            }

          }

        else if(PORT_PIN_MODE_SPI == portInit_Ptr[i].mode) /************************** SPI Mode Initialization ******************************/
                {
            if((PORTD == portInit_Ptr[i].port_num) && (PIN3 >= portInit_Ptr[i].pin_num))
                        {
                            INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_SPI_MASK_1); /* Insert the suitable mask in the PCTL register*/
                        }

                        else
                        {
                            INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_SPI_MASK_2); /* Insert the suitable mask in the PCTL register*/
                        }

                }

        else if(PORT_PIN_MODE_I2C == portInit_Ptr[i].mode) /************************** I2C Mode Initialization ******************************/
               {
                   INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_I2C_MASK); /* Insert the suitable mask in the PCTL register*/
               }

        else if(PORT_PIN_MODE_CAN == portInit_Ptr[i].mode) /************************** CAN Mode Initialization ******************************/
                        {
                    if((PORTF == portInit_Ptr[i].port_num) && ((PIN0 == portInit_Ptr[i].pin_num)||(PIN3 == portInit_Ptr[i].pin_num)))
                                {
                                    INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_CAN_MASK_1); /* Insert the suitable mask in the PCTL register*/
                                }

                                else
                                {
                                    INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[i].pin_num),PCTL_CAN_MASK_2); /* Insert the suitable mask in the PCTL register*/
                                }

                        }

        else
        {
            /* Do Nothing */
        }

        break;

    default:
        /* Do Nothing */
        break;

}

}

}

}

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

void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction)
{
    boolean error_status = FALSE;

#if(STD_ON ==PORT_DEV_ERROR_DETECT )

   if(Port_status == PORT_NOT_INITIALIZED)
   {
       Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,Port_SetPinDirection_SID,PORT_E_UNINIT);
       error_status = TRUE;
   }
   else if(STD_OFF == portInit_Ptr[Pin].change_dir)
   {
       Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,Port_SetPinDirection_SID,PORT_E_DIRECTION_UNCHANGEABLE);
       error_status = TRUE;

   }
   else if (NUMBER_PINS < Pin)
   {
       Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,Port_SetPinDirection_SID,PORT_E_PARAM_PIN);
              error_status = TRUE;
   }

   else
   {
       /* Do Nothing */
   }

#endif

   if(error_status == FALSE)
   {
       uint8 i;
    for(i=0;i<NUMBER_PINS;i++)
    {

   if(PORT_PIN_OUT == Direction)
   {
       SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , portInit_Ptr[i].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                 if(portInit_Ptr[i].initial_level == STD_HIGH)
                 {
                     SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , portInit_Ptr[i].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                 }

                 else
                 {
                     CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , portInit_Ptr[i].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                 }
   }

   else if(PORT_PIN_IN == Direction)
         {
             CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , portInit_Ptr[i].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

             if(portInit_Ptr[i].resistor == PULL_UP)
             {
                 SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , portInit_Ptr[i].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
             }

             else if(portInit_Ptr[i].resistor == PULL_DOWN)
             {
                 SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , portInit_Ptr[i].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
             }

             else
             {
                 CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , portInit_Ptr[i].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                 CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) ,portInit_Ptr[i].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
             }

}

   else
   {
       /* Do Nothing */
   }

   }

   }

}

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

void Port_RefreshPortDirection(void)
{

 boolean error_status = FALSE;

#if(STD_ON ==PORT_DEV_ERROR_DETECT )

   if(Port_status == PORT_NOT_INITIALIZED)
   {
       Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,Port_RefreshPortDirection_SID,PORT_E_UNINIT);
       error_status = TRUE;
   }

   else
   {
       /* Do Nothing */
   }

#endif

if(FALSE == error_status)
{
    uint8 i;
    for(i=0;i<NUMBER_PINS;i++)
    {

if(STD_OFF == portInit_Ptr[i].change_dir)
{

 if(PORT_PIN_OUT == portInit_Ptr[i].direction)
 {
     SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,portInit_Ptr[i].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                      if(portInit_Ptr[i].initial_level == STD_HIGH)
                      {
                          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , portInit_Ptr[i].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                      }

                      else
                      {
                          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , portInit_Ptr[i].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                      }
 }

 else if(PORT_PIN_IN == portInit_Ptr[i].direction)
 {
     CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , portInit_Ptr[i].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                 if(portInit_Ptr[i].resistor == PULL_UP)
                 {
                     SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) ,portInit_Ptr[i].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                 }

                 else if(portInit_Ptr[i].resistor == PULL_DOWN)
                 {
                     SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , portInit_Ptr[i].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                 }

                 else
                 {
                     CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , portInit_Ptr[i].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                     CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , portInit_Ptr[i].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                 }

 }

 else
 {
     /* Do Nothing */
 }

}

else
{
    /* Do Nothing */
}

}

}

}


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

void Port_GetVersionInfo( Std_VersionInfoType* versioninfo)
{

boolean error_status = FALSE;

#if(STD_ON == PORT_DEV_ERROR_DETECT)

    if(Port_status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,Port_GetVersionInfo_SID,PORT_E_UNINIT);
        error_status = TRUE;
    }

    else if(NULL_PTR == versioninfo)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,Port_GetVersionInfo_SID,PORT_E_PARAM_POINTER);
        error_status = TRUE;

    }
    else
    {
        /* Do Nothing */
    }

#endif

    if(error_status == FALSE)
    {
                /* Copy the vendor Id */
                versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
                /* Copy the module Id */
                versioninfo->moduleID = (uint16)PORT_MODULE_ID;
                /* Copy Software Major Version */
                versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
                /* Copy Software Minor Version */
                versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
                /* Copy Software Patch Version */
                versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }

    else
    {
        /* Do Nothing */
    }

}

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

void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode)
{

  boolean error_status = FALSE;

#if(STD_ON == PORT_DEV_ERROR_DETECT)

    if(Port_status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,Port_SetPinMode_SID,PORT_E_UNINIT);
        error_status = TRUE;
    }

    else if(STD_OFF == portInit_Ptr[Pin].change_mode)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,Port_SetPinMode_SID,PORT_E_MODE_UNCHANGEABLE);
        error_status = TRUE;

    }

    else if(NUMBER_MODES < Mode)
    {
        Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,Port_SetPinMode_SID,PORT_E_PARAM_INVALID_MODE);
                error_status = TRUE;
    }

    else if(NUMBER_PINS < Pin)
        {
            Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,Port_SetPinMode_SID,PORT_E_PARAM_PIN);
                    error_status = TRUE;
        }

    else
    {
        /* Do Nothing */
    }

#endif

if(FALSE == error_status)
{
    /*******************************************************************************
      *                          Configuring Pins Mode                              *
      *******************************************************************************/


     /***************************************Analog Modes*******************************************/

   switch(portInit_Ptr[Pin].mode)
   {
   case PORT_PIN_MODE_ADC: /************************** ADC Mode Initialization******************************/
   case PORT_PIN_MODE_USB: /************************** USB Mode Initialization******************************/

       SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , portInit_Ptr[Pin].pin_num);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

       CLEAR_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num));         /* Clear corresponding bits to the bit in the PCTL Reg*/

       SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , portInit_Ptr[Pin].pin_num);      /* Enable the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , portInit_Ptr[Pin].pin_num);     /* Disable the corresponding bit in the GPIODEN register to disable digital functionality on this pin */

       if(PORT_PIN_MODE_ADC == portInit_Ptr[Pin].mode)
       {

         INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_ADC_MASK);
       }
       else if(PORT_PIN_MODE_USB == portInit_Ptr[Pin].mode)
       {
          if((PORTB == portInit_Ptr[Pin].port_num) && (PIN1 >= portInit_Ptr[Pin].pin_num) || \
            (PORTD == portInit_Ptr[Pin].port_num) && (PIN5 >= portInit_Ptr[Pin].pin_num))
          {

              INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_USB_ANALOG_MASK); /* Insert the suitable mask in the PCTL register*/

          }
          else
          {
              /**************************Digital Pins in USB Module***************************************/
          }
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , portInit_Ptr[Pin].pin_num);      /* Disable the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , portInit_Ptr[Pin].pin_num);         /*  Enable the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
              INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_USB_DIGITAL_MASK); /* Insert the suitable mask in the PCTL register*/

          }

       else
       {
           /* Do Nothing */
       }

       break;

       /***************************************Digital Modes*******************************************/


       /************************** DIO Mode Initialization******************************/

       case PORT_PIN_MODE_DIO:
       case PORT_PIN_MODE_PWM:
       case PORT_PIN_MODE_GPT:
       case PORT_PIN_MODE_NMI:
       case PORT_PIN_MODE_UART:
       case PORT_PIN_MODE_SPI:
       case PORT_PIN_MODE_I2C:
       case PORT_PIN_MODE_CAN:

           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , portInit_Ptr[Pin].pin_num);      /* Disable the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , portInit_Ptr[Pin].pin_num);     /* Enable the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
           CLEAR_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num));         /* Clear corresponding bits to the bit in the PCTL Reg*/
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , portInit_Ptr[Pin].pin_num);             /* Enable Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */


           if(PORT_PIN_MODE_DIO == portInit_Ptr[Pin].mode) /************************** DIO Mode Initialization ******************************/
           {
               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , portInit_Ptr[Pin].pin_num);             /* Disable Alternative function for this pin by clearing the corresponding bit in GPIOAFSEL register */
           }

           else if(PORT_PIN_MODE_PWM == portInit_Ptr[Pin].mode) /************************** PWM Mode Initialization (M0) only ******************************/
           {
               INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_PWM_M0_MASK); /* Insert the suitable mask in the PCTL register*/

           }

           else if(PORT_PIN_MODE_GPT == portInit_Ptr[Pin].mode) /************************** GPT Mode Initialization ******************************/
           {
               INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_GPT_MASK); /* Insert the suitable mask in the PCTL register*/

           }

           else if(PORT_PIN_MODE_NMI == portInit_Ptr[Pin].mode) /************************** NMI Mode Initialization ******************************/
           {
               INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_NMI_MASK); /* Insert the suitable mask in the PCTL register*/
           }

           else if(PORT_PIN_MODE_UART == portInit_Ptr[Pin].mode) /************************** UART Mode Initialization ******************************/
            {
               if((PORTC == portInit_Ptr[Pin].port_num) && (PIN5 >= portInit_Ptr[Pin].pin_num))
               {
                   INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_UART_MASK_2); /* Insert the suitable mask in the PCTL register*/
               }

               else
               {
                   INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_UART_MASK_1); /* Insert the suitable mask in the PCTL register*/
               }

             }

           else if(PORT_PIN_MODE_SPI == portInit_Ptr[Pin].mode) /************************** SPI Mode Initialization ******************************/
                   {
               if((PORTD == portInit_Ptr[Pin].port_num) && (PIN3 >= portInit_Ptr[Pin].pin_num))
                           {
                               INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_SPI_MASK_1); /* Insert the suitable mask in the PCTL register*/
                           }

                           else
                           {
                               INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_SPI_MASK_2); /* Insert the suitable mask in the PCTL register*/
                           }

                   }

           else if(PORT_PIN_MODE_I2C == portInit_Ptr[Pin].mode) /************************** I2C Mode Initialization ******************************/
                  {
                      INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_I2C_MASK); /* Insert the suitable mask in the PCTL register*/
                  }

           else if(PORT_PIN_MODE_CAN == portInit_Ptr[Pin].mode) /************************** CAN Mode Initialization ******************************/
                           {
                       if((PORTF == portInit_Ptr[Pin].port_num) && ((PIN0 == portInit_Ptr[Pin].pin_num)||(PIN3 == portInit_Ptr[Pin].pin_num)))
                                   {
                                       INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_CAN_MASK_1); /* Insert the suitable mask in the PCTL register*/
                                   }

                                   else
                                   {
                                       INSERT_HALF_BYTE(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET),(portInit_Ptr[Pin].pin_num),PCTL_CAN_MASK_2); /* Insert the suitable mask in the PCTL register*/
                                   }

                           }

           else
           {
               /* Do Nothing */
           }

           break;

       default:
           /* Do Nothing */
           break;
}

}

}

#endif
