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
  pTxData = LSM6_reboot;          /*reboot IMU*/
  HAL_SPI_Transmit(&hspi1, &pTxData, 1, NO_POLLING);
  pTxData = LSM6_cfg;             /*IMU feature configuration*/
  HAL_SPI_Transmit(&hspi1, &pTxData, 1, NO_POLLING);
  pTxData = LSM6_accel_start;     /*enable accelerometer*/
  HAL_SPI_Transmit(&hspi, &pTxData, 1, NO_POLLING);
  pTxData = LSM6_gyro_start;      /*enable gyroscope*/
  HAL_SPI_Transmit(&hspi, &pTxData, 1, NO_POLLING);
  // NOTE: accelerometer and gyroscope features may be further configured, see IMU.h for more details

  pTxData = LSM6_FIFO_watermark;  /*FIFO watermark*/
  HAL_SPI_Transmit(&hspi, &pTxData, 1, NO_POLLING);
  pTxData = LSM6_FIFO_data_cfg;   /*FIFO configuration*/
  HAL_SPI_Transmit(&hspi, &pTxData, 1, NO_POLLING);
  pTxData = LSM6_FIFO_BDR;        /*FIFO batch data rate*/
  HAL_SPI_Transmit(&hspi, &pTxData, 1, NO_POLLING);
  pTxData = LSM6_FIFO_start_cfg;  /*FIFO enable*/
  HAL_SPI_Transmit(&hspi, &pTxData, 1, NO_POLLING);
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
  int pRxData = 0;

  pTxData = LSM6_FIFO_stored; /*check if FIFO empty*/
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  if(pRxData == 0){
    return pdFalse;
  }

  pTxData = LSM6_FIFO_read_tag;  
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  if(pRxData == LSM6_Gyroscope_NC){ // may be a fabrication

  pTxData = LSM6_FIFO_read_x_h; 
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  Data->gyr_x = pRxData;
  pTxData = LSM6_FIFO_read_x_l; 
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  Data->gyr_x = (Data->gyr_x << 8) || pRxData;

  pTxData = LSM6_FIFO_read_y_h; 
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  Data->gyr_y = pRxData;
  pTxData = LSM6_FIFO_read_y_l; 
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  Data->gyr_y = (Data->gyr_y << 8) || pRxData;

  pTxData = LSM6_FIFO_read_z_h; 
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  Data->gyr_z = pRxData;
  pTxData = LSM6_FIFO_read_z_l; 
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  Data->gyr_z = (Data->gyr_z << 8) || pRxData;


  } else if(pRxData == LSM6_Accelerometer_NC){ // may be a fabrication

  pTxData = LSM6_FIFO_read_x_h; 
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  Data->accel_x = pRxData;
  pTxData = LSM6_FIFO_read_x_l; 
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  Data->accel_x = (Data->gyr_x << 8) || pRxData;

  pTxData = LSM6_FIFO_read_y_h; 
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  Data->accel_y = pRxData;
  pTxData = LSM6_FIFO_read_y_l; 
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  Data->accel_y = (Data->gyr_y << 8) || pRxData;

  pTxData = LSM6_FIFO_read_z_h; 
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  Data->accel_z = pRxData;
  pTxData = LSM6_FIFO_read_z_l; 
  HAL_SPI_TransmitReceive(&hspi, &pTxData, &pRxData, 1, NO_POLLING);
  Data->accel_z = (Data->accel_z << 8) || pRxData;

  } else {
    return pdFalse;
  }
  return pdTrue;
}
