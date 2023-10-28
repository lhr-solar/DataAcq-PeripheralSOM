/**
  ******************************************************************************
  * @file    Temperature.c
  * @brief   Temperature Sensor Driver - LMT87
  *          This file interfaces with the LMT87.
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

#include "Temperature.h"

/** Temperature Init
 * @brief Initialize the Temperature sensor
 * 
 * @return pdTRUE if initialization was successful, pdFALSE otherwise
*/
BaseType_t Temperature_Init(void) {
  // TODO: Initialize ADC
  // TODO: Initialize Sensor
}

/** Temperature Read Data
 * @brief Update temperature array with new data
 * 
 * @param Data Pointer to the temperature array
 * @return pdTRUE if data was successfully fetched from queue, pdFALSE if queue is empty
*/
BaseType_t Temperature_ReadData(TempData_t* Data){
  // TODO: Read data from sensor
}
