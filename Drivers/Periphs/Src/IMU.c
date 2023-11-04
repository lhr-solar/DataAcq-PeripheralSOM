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
#include <cstdint>
#define NO_POLLING 0

/** IMU Init
 * @brief Initialize IMU to collect data
 * 
 * @param None
 * @return pdTRUE if initialization was successful, pdFALSE otherwise
 */
BaseType_t IMU_Init(void) {
  int pTxData = 0;
  int pRxData = 0;

  IMUCommands_t IMUcommands;
  //Initialize SPI
  MX_SPI1_Init();
  // TODO: Configure gyroscope and accelerometer
  pTxData = LSM6_reboot;  /*reboot IMU*/
  HAL_SPI_Transmit(&hspi1, &pTxData, 1, NO_POLLING);
  pTxData = LSM6_cfg;    /*IMU feature configuration*/
  HAL_SPI_Transmit(&hspi1, &pTxData, 1, NO_POLLING);
  pTxData = LSM6_accel_start; /*enable accelerometer*/
  HAL_SPI_Transmit(&hspi, &pTxData, 1, NO_POLLING);
  pTxData = LSM6_gyro_start;  /*enable gyroscope*/
  HAL_SPI_Transmit(&hspi, &pTxData, 1, NO_POLLING);
  // NOTE: accelerometer and gyroscope features may be further configured, see IMU.h for more details
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
