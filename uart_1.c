/******************************************************************************
 *
 * Module: UART1
 *
 * File Name: UART1.c
 *
 * Description: Source file for the TM4C123GH6PM UART1 driver
 *
 * Author: Mahmoud Hussein Mahmoud
 *
 *******************************************************************************/

#include "uart_1.h"
#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 *                         Private Functions Definitions                       *
 *******************************************************************************/

//static void GPIO_SetupUART1Pins(void)
//{
//    SYSCTL_RCGCGPIO_REG  |= 0x02;         /* Enable clock for GPIO PORTB */
//    while(!(SYSCTL_PRGPIO_REG & 0x02));   /* Wait until GPIO PORTB clock is activated and it is ready for access*/
//
//    GPIO_PORTB_AMSEL_REG &= ~0x03;         /* Disable Analog on PB0 & PB1 */
//    GPIO_PORTB_DIR_REG   &= 0xFE;         /* Configure PB0 as input pin */
//    GPIO_PORTB_DIR_REG   |= 0x02;         /* Configure PB1 as output pin */
//    GPIO_PORTB_AFSEL_REG |= 0x03;         /* Enable alternative function on PA0 & PA1 */
//    /* Set PMCx bits for PA0 & PA1 with value 1 to use PA0 as UART1 RX pin and PA1 as UART1 Tx pin */
//    GPIO_PORTB_PCTL_REG  = (GPIO_PORTB_PCTL_REG & 0xFFFFFF00) | 0x00000011;
//    GPIO_PORTB_DEN_REG   |= 0x03;         /* Enable Digital I/O on PA0 & PA1 */
//}

/*******************************************************************************
 *                         Public Functions Definitions                        *
 *******************************************************************************/

void UART1_Init(void)
{
//    /* Setup UART1 pins PA0 --> U0RX & PA1 --> U0TX */
    //  GPIO_SetupUART1Pins();

    SYSCTL_RCGCUART_REG |= 0x02;          /* Enable clock for UART1 */
    while(!(SYSCTL_PRUART_REG & 0x02));   /* Wait until UART1 clock is activated and it is ready for access*/

    UART1_CTL_REG = 0;                    /* Disable UART1 at the beginning */

    UART1_CC_REG  = 0;                    /* Use System Clock*/

    /* To Configure UART1 with Baud Rate 9600 */
    UART1_IBRD_REG = 104;
    UART1_FBRD_REG = 11;

    /* UART Line Control Register Settings
     * BRK = 0 Normal Use
     * PEN = 0 Disable Parity
     * EPS = 0 No affect as the parity is disabled
     * STP2 = 0 1-stop bit at end of the frame
     * FEN = 0 FIFOs are disabled
     * WLEN = 0x3 8-bits data frame
     * SPS = 0 no stick parity
     */
    UART1_LCRH_REG = (UART_DATA_8BITS_WITH_FIFOS << UART_LCRH_WLEN_BITS_POS_WITH_FIFOS);

    /* UART Control Register Settings
     * RXE = 1 Enable UART Receive
     * TXE = 1 Enable UART Transmit
     * HSE = 0 The UART is clocked using the system clock divided by 16
     * UARTEN = 1 Enable UART
     */
    UART1_CTL_REG = UART_CTL_UARTEN_MASK | UART_CTL_TXE_MASK | UART_CTL_RXE_MASK;


    /* Setup UART1 pins PA0 --> U0RX & PA1 --> U0TX */
       // GPIO_SetupUART1Pins();

//        SYSCTL_RCGCUART_REG |= 0x04;          /* Enable clock for UART1 */
//        while(!(SYSCTL_PRUART_REG & 0x04));   /* Wait until UART1 clock is activated and it is ready for access*/
//
//        UART2_CTL_REG = 0;                    /* Disable UART1 at the beginning */
//
//        UART2_CC_REG  = 0;                    /* Use System Clock*/
//
//        /* To Configure UART1 with Baud Rate 9600 */
//        UART2_IBRD_REG = 104;
//        UART2_FBRD_REG = 11;
//
//        /* UART Line Control Register Settings
//         * BRK = 0 Normal Use
//         * PEN = 0 Disable Parity
//         * EPS = 0 No affect as the parity is disabled
//         * STP2 = 0 1-stop bit at end of the frame
//         * FEN = 0 FIFOs are disabled
//         * WLEN = 0x3 8-bits data frame
//         * SPS = 0 no stick parity
//         */
//        UART2_LCRH_REG = (UART_DATA_8BITS_WITH_FIFOS << UART_LCRH_WLEN_BITS_POS_WITH_FIFOS);
//
//        /* UART Control Register Settings
//         * RXE = 1 Enable UART Receive
//         * TXE = 1 Enable UART Transmit
//         * HSE = 0 The UART is clocked using the system clock divided by 16
//         * UARTEN = 1 Enable UART
//         */
//        UART2_CTL_REG = UART_CTL_UARTEN_MASK | UART_CTL_TXE_MASK | UART_CTL_RXE_MASK;
}

void UART1_SendByte(uint8 data)
{
    while(!(UART1_FR_REG & UART_FR_TXFE_MASK)); /* Wait until the transmit FIFO is empty */
    UART1_DR_REG = data; /* Send the byte */
}

uint8 UART1_ReceiveByte(void)
{
     while(UART1_FR_REG & UART_FR_RXFE_MASK); /* Wait until the receive FIFO is not empty */

     return UART1_DR_REG; /* Read the byte */

//    while(UART1_FR_REG & 0x0010 != 0);
//    return (char) (UART1_DR_REG & 0xFF);
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART1_SendString(const uint8 *pData)
{
    uint32 uCounter =0;
    /* Transmit the whole string */
    while(pData[uCounter] != '\0')
    {
        UART1_SendByte(pData[uCounter]); /* Send the byte */
        uCounter++; /* increment the counter to the next byte */
    }
}

/*
 * Description :
 * Receive the required string until the '*' symbol through UART from the other UART device.
 */
void UART1_ReceiveString(char  *pData)
{
    uint32 uCounter =0;

    // char test_receive = UART1_ReceiveByte();

    while (UART1_ReceiveByte() != '$');

    pData[uCounter] = UART1_ReceiveByte(); /* Receive the first byte */

    /* Receive the whole string until the '#' */
    while(pData[uCounter] != '*')
    {
        uCounter++;
        pData[uCounter] = UART1_ReceiveByte();
    }
    /* After receiving the whole string plus the '#', replace the '#' with '\0' */
    pData[uCounter] = '\0';
}

/*
 * Description :
 * Send the required number of bytes through UART to the other UART device.
 */
void UART1_SendData(const uint8 *pData, uint32 uSize)
{
    /* Transmit the number of bytes requested on the UART port */
    while(uSize--)
    {

        UART1_SendByte(*pData); /* Send the byte */
        pData++; /* increment pointer to the next byte */
    }
}

/*
 * Description :
 * receive the required number of bytes through UART from the other UART device.
 */
void UART1_ReceiveData(uint8 *pData, uint32 uSize)
{
    /* Receive the number of bytes requested on the UART port */
    while(uSize--)
    {
        *pData = UART1_ReceiveByte(); /* receive a byte from the UART */
         pData++; /* increment pointer to receive the next byte in the next location */
    }
}





