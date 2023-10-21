/**
  ******************************************************************************
  * @file    IMU.c
  * @brief   Inertial Measurement Unit Driver - LSM6DSV
  *          This file interfaces with the LSM6DSV. 
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

#include "IMU.h"
#include "spi.h"

/** IMU Init
 * @brief Initialize IMU to collect data
 * 
 * @param None
 * @return pdTRUE if initialization was successful, pdFALSE otherwise
 */
BaseType_t IMU_Init(void) {
  // TODO: Initialize SPI
  // TODO: Initialize Sensor
}

/** IMU Read Data
 * 
 * @brief Update IMU struct with new data
 * 
 * @param Data : Pointer to struct used to collect IMU Data
 * @return pdTRUE if data was successfully fetched from queue, pdFALSE if queue is empty
 */
BaseType_t IMU_ReadData(IMUData_t *Data) {
  // TODO: Read data from queue
}
