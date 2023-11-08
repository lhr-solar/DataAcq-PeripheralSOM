/* Copyright (c) 2018-2022 UT Longhorn Racing Solar */

#ifndef BSP_UART_H
#define BSP_UART_H

#include "stm32l4xx_hal.h"

extern USART_HandleTypeDef usart1;

//enum to describe what UART port you are trying to access
typedef enum {UART_USB, UART_BLE, NUM_UART} UART_Port;

/**
 * @brief   Initializes the USART peripheral
 */
void USART_Init();

/**
 * @brief   Gets one 128 characters from USART
 * @pre     str should be at least 128 bytes long.
 * @param   str : pointer to string to store the data. This buffer should be initialized before hand.   
 * @return  number of bytes that was read
 */
uint32_t UART_Read(uint8_t *data);

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
HAL_StatusTypeDef UART_Write(char *str, uint32_t len);

#endif
