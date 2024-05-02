/*
 * Port_priv.h
 *
 *  Created on: Apr 17, 2024
 *      Author: Iyad
 */

#ifndef PORT_PRIV_H_
#define PORT_PRIV_H_

/*
 *  Software Module Version 1.0.0
 */
#define PORT_PRIV_SW_MAJOR_VERSION     (1U)
#define PORT_PRIV_SW_MINOR_VERSION     (0U)
#define PORT_PRIV_SW_PATCH_VERSION     (0U)

/*
 *  AUTOSAR Version 4.0.3
 */
#define PORT_PRIV_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_PRIV_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_PRIV_AR_RELEASE_PATCH_VERSION (3U)


#include<Port.h>

/* AUTOSAR checking between Port_priv.h and Port.h Modules */
#if ((PORT_PRIV_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PRIV_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PRIV_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port.h does not match the expected version"
#endif

/* Software checking between Port_priv.h and Port.h Modules */
#if((PORT_PRIV_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION )\
||  (PORT_PRIV_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION )\
||  (PORT_PRIV_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error"The SW version of Port.h does not match the expected version"
#endif


/*
 * Macros for Port Status
 */

#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* password code for lock register  */
#define LOCK_REG_PASS            (0x4C4F434B)

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/

/* Service ID for Port_Init */
#define Port_Init_SID                 (0x00)

/* Service ID for Port_SetPinDirection */
#define Port_SetPinDirection_SID      (0x01)

/* Service ID for Port_RefreshPortDirection */
#define Port_RefreshPortDirection_SID (0x02)

/* Service ID for Port_GetVersionInfo */
#define Port_GetVersionInfo_SID       (0x03)

/* Service ID for Port_SetPinMode */
#define Port_SetPinMode_SID           (0x04)

/*******************************************************************************
 *                              DET error Codes                                *
 *******************************************************************************/

/* DET error code to report invalid port pin ID*/
#define PORT_E_PARAM_PIN                   (0x0A)

/* DET error code to report port pin is not configured as changeable*/
#define PORT_E_DIRECTION_UNCHANGEABLE      (0x0B)

/* DET error code to report port_init service is called with wrong parameter*/
#define PORT_E_PARAM_CONFIG                (0x0C)

/* DET error code to report API Port_SetPinMode service called when mode is invalid*/
#define PORT_E_PARAM_INVALID_MODE          (0x0D)

/* DET error code to report API Port_SetPinMode service called when mode is unchangable*/
#define PORT_E_MODE_UNCHANGEABLE           (0x0E)

/* DET error code to report API service called without module initialization */
#define PORT_E_UNINIT                      (0x0F)

/* DET error code to report APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER               (0x10)

/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C


/*******************************************************************************
 *                            PCTL Register Masks                              *
 *******************************************************************************/


/***************************************Analog Modes*******************************************/

/* ADC Mode */
#define PCTL_ADC_MASK           (0x00)

/* USB Mode (Analog pins) */
#define PCTL_USB_ANALOG_MASK    (0x00)

/***************************************Digital Modes*******************************************/


/* USB Mode (Digital pins) */
#define PCTL_USB_DIGITAL_MASK    (0x08)

/* PWM Mode */
#define PCTL_PWM_M0_MASK         (0X04)
#define PCTL_PWM_M1_MASK         (0X05)

/* GPT Mode */
#define PCTL_GPT_MASK            (0X07)

/* NMI Mode */
#define PCTL_NMI_MASK            (0X08)

/* UART Mode */
#define PCTL_UART_MASK_1         (0x01)
#define PCTL_UART_MASK_2         (0x02)

/* SPI Mode */
#define PCTL_SPI_MASK_1         (0x01)
#define PCTL_SPI_MASK_2        (0x02)

/* I2C Mode */
#define PCTL_I2C_MASK           (0x03)

/* CAN Mode */
#define PCTL_CAN_MASK_1         (0x03)
#define PCTL_CAN_MASK_2         (0x08)


#endif /* PORT_PRIV_H_ */
