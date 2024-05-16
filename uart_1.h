/******************************************************************************
 *
 * Module: UART1
 *
 * File Name: uart1.h
 *
 * Description: Header file for the TM4C123GH6PM UART1 driver
 *
 * Author: <Mahmoud Hussein Mahmoud>
 *
 *******************************************************************************/

#ifndef UART1_H_
#define UART1_H_

#include "std_types.h"

/*******************************************************************************
 *                             PreProcessor Macros                             *
 *******************************************************************************/

#define UART_DATA_5BITS          0x0
#define UART_DATA_6BITS          0x1
#define UART_DATA_7BITS          0x2
#define UART_DATA_8BITS          0x3
#define UART_DATA_8BITS_WITH_FIFOS  0x7
#define UART_LCRH_WLEN_BITS_POS  5
#define UART_LCRH_WLEN_BITS_POS_WITH_FIFOS  4
#define UART_CTL_UARTEN_MASK     0x00000001
#define UART_CTL_TXE_MASK        0x00000100
#define UART_CTL_RXE_MASK        0x00000200
#define UART_FR_TXFE_MASK        0x00000080
#define UART_FR_RXFE_MASK        0x00000010

/*******************************************************************************
 *                            Functions Prototypes                             *
 *******************************************************************************/

extern void UART1_Init(void);

extern void UART1_SendByte(uint8 data);

extern uint8 UART1_ReceiveByte(void);

extern void UART1_SendData(const uint8 *pData, uint32 uSize);

extern void UART1_ReceiveData(uint8 *pData, uint32 uSize);

extern void UART1_SendString(const uint8 *pData);

extern void UART1_ReceiveString(char *pData);

#endif
