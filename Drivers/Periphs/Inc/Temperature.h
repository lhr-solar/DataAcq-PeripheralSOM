/**
  ******************************************************************************
  * @file    Temperature.h
  * @brief   Temperature Sensor API - LMT87
  *          This file contains all the function prototypes for Temperature.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 LHR Solar.
  * All rights reserved.
  *
  * To be deployed on LHRS Peripheral SOM.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

#include "FreeRTOS.h"
#include <stdint.h>

#define TEMP_ERR_OUT_BOUNDS 42424242

typedef struct {
    int16_t temp1;
    int16_t temp2;
    int16_t temp3;
} TempData_t;

/** Temperature Init
 * @brief Initialize the Temperature sensor
 * 
 * @return pdTRUE if initialization was successful, pdFALSE otherwise
*/
BaseType_t Temperature_Init(void);

/** Temperature Read Data
 * @brief Update temperature array with new data
 * 
 * @param Data Pointer to the temperature array
 * @return pdTRUE if data was successfully fetched from queue, pdFALSE if queue is empty
*/
BaseType_t Temperature_ReadData(TempData_t* Data);

#endif /* __TEMPERATURE_H__ */