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

  // Initialize IMU, gyroscope, and accelerometer
  // NOTE: accelerometer and gyroscope features may be further configured, see IMU.h for more details
  // TODO: Configure gyroscope and accelerometer
  for(int i = 0; i < imuInit[0]; i ++){
    pTxData = imuInit[i+1];
    HAL_SPI_Transmit(&hspi1, &pTxData, 1, NO_POLLING);
  }

  // Initialize IMU hardware FIFO
  // NOTE: FIFO size, rate and mode may be further configured, see IMU.h for more details
  for(int i = 0; i < fifoInit[0], i ++){
    pTxData = fifoInit[i+1];
    HAL_SPI_Transmit(&hspi, &pTxData, 1, NO_POLLING);
  }
}

/** IMU Read Data
 * 
 * @brief Update IMU struct with new data
 * 
 * @param Data : Pointer to struct used to collect IMU Data
 * @return pdTRUE if data was successfully fetched from queue, pdFALSE if queue is empty
 */
BaseType_t IMU_ReadData(IMUData_t *Data) {
  // TODO: test on hardware
  int pTxData = 0;
  int pRxData1 = 0;
  int pRxData2 = 0;

  pTxData = LSM6_FIFO_stored; /*check if FIFO empty*/
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData1, 1, NO_POLLING);
  if(pRxData1 == 0){
    return pdFalse;
  }
  pTxData = LSM6_FIFO_read_tag;  /*get tag*/
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData1, 1, NO_POLLING);

  if(pRxData == LSM6_Gyroscope_NC){ // may be the wrong FIFO tag, assumes gyroscope
    for(int i = 0; i < fifoXYZregisters[0] - 1; i = i + 2){
      pTxData = fifoXYZregisters[i+1];
      HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData1, 1, NO_POLLING);
     pTxData = fifoXYZregisters[i+2];
     HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData2, 1, NO_POLLING);
     switch(i){
       case 0: Data->gyr_x = (pRxData1 << 8) | pRxData2;
       case 2: Data->gyr_y = (pRxData1 << 8) | pRxData2;
       case 4: Data->gyr_z = (pRxData1 << 8) | pRxData2;
     }
   }
  } else if(pRxData == LSM6_Accelerometer_NC){ // may be the wrong FIFO tag, assumes accelerometer
    for(int i = 0; i < fifoXYZregisters[0] - 1; i = i + 2){
      pTxData = fifoXYZregisters[i+1];
      HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData1, 1, NO_POLLING);
     pTxData = fifoXYZregisters[i+2];
     HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData2, 1, NO_POLLING);
     switch(i){
       case 0: Data->accel_x = (pRxData1 << 8) | pRxData2;
       case 2: Data->accel_y = (pRxData1 << 8) | pRxData2;
       case 4: Data->accel_z = (pRxData1 << 8) | pRxData2;
     }
   }
  } else {
    // not accelerometer data
    return pdFalse;
  }

  return pdTrue;
}
