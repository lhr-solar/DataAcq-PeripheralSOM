/**
  ******************************************************************************
  * @file    IMU.h
  * @brief   Inertial Measurement Unit API - LSM6DSV
  *          This file contains all the function prototypes for IMU.c
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
#ifndef __IMU_H__
#define __IMU_H__

#include "FreeRTOS.h"
#include <stdint.h>

typedef struct {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyr_x;
    int16_t gyr_y;
    int16_t gyr_z;
} IMUData_t;

/** IMU Init
 * @brief Initialize IMU to collect data
 * 
 * @param None
 * @return pdTRUE if initialization was successful, pdFALSE otherwise
 */
BaseType_t IMU_Init(void);

/** IMU Read Data
 * 
 * @brief Update IMU struct with new data
 * @param Data : Pointer to struct used to collect IMU Data
 * @return pdTRUE if data was successfully fetched from queue, pdFALSE if queue is empty
 */
BaseType_t IMU_ReadData(IMUData_t *Data);

#endif /* __IMU_H__ */
