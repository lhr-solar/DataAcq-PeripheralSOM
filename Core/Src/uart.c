/* Copyright (c) 2018-2022 UT Longhorn Racing Solar */

#include "uart.h"

#define TX_SIZE     2048
#define RX_SIZE     64

USART_HandleTypeDef usart1;

void USART_Init() {
    USART_InitTypeDef UART_InitStruct;

    //Initialize UART2 and 3
    usart1.Instance = USART1;
    UART_InitStruct.BaudRate = 115200;
    UART_InitStruct.Mode = USART_MODE_TX_RX;
    UART_InitStruct.Parity = USART_PARITY_NONE;
    UART_InitStruct.StopBits = USART_STOPBITS_1;
    UART_InitStruct.WordLength = USART_WORDLENGTH_8B;
    usart1.Init = UART_InitStruct;
    HAL_USART_Init(&usart1);
}

/**
 * @brief   Gets one line of ASCII text that was received. The '\n' and '\r' characters will not be stored (tested on Putty on Windows)
 * @pre     str should be at least 128bytes long.
 * @param   data : pointer to buffer to store the data. This buffer should be initialized
 *                  before hand.
 * @return  number of bytes that was read
 */
uint32_t UART_Read(uint8_t *data) {

    HAL_USART_Receive(&usart1, data, 128, 1000);

    return 128;
}

/**
 * @brief   Transmits data to through UART line
 * @param   str : pointer to buffer with data to send.
 * @param   len : size of buffer
 * @return  number of bytes that were sent
 * 
 * @note This function uses a fifo to buffer the write. If that
 *       fifo is full, this function may block while waiting for
 *       space to open up. Do not call from timing-critical
 *       sections of code.
 */
HAL_StatusTypeDef UART_Write(char *str, uint32_t len) {
    return HAL_USART_Transmit(&usart1, str, len, 1000);
}
