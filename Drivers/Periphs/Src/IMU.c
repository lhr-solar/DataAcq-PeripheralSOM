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

const int imuInit[][2] = {
  {LSM6_CTRL_3, LSM6_reboot},  /*reboot IMU*/ 
  {LSM6_CFG_ACCESS, LSM6_cfg}, /*IMU feature configuration*/ 
  {LSM6_CTRL_1, LSM6_accel_start}, /*enable accelerometer*/
  {LSM6_CTRL_2, LSM6_gyro_start}   /*enable gyroscope*/
};

const int fifoInit[][2] = {
  {FIFO_CTRL_1, LSM6_FIFO_watermark},  /*FIFO watermark*/
  {FIFO_CTRL_2, LSM6_FIFO_data_cfg},   /*FIFO configuration*/
  {FIFO_CTRL_3, LSM6_FIFO_BDR},        /*FIFO batch data rate*/
  {FIFO_CTRL_4, LSM6_FIFO_start_cfg}  /*FIFO enable*/
};

const int fifoQXYZregisters[][2] = {
  {LSM6_FIFO_read_x_h, 0}, /*accelerometer and gyroscope xyz data from queue*/ 
  {LSM6_FIFO_read_x_l, 0},
  {LSM6_FIFO_read_y_h, 0},
  {LSM6_FIFO_read_z_l, 0},
  {LSM6_FIFO_read_y_l, 0},
  {LSM6_FIFO_read_z_h, 0}
};

const int readDataReg[][2] = {
  {LSM6_read_x_h_g, 0}, /*gyroscope xyz data*/
  {LSM6_read_x_l_g, 0}, 
  {LSM6_read_y_h_g, 0},
  {LSM6_read_y_l_g, 0},
  {LSM6_read_z_h_g, 0},
  {LSM6_read_z_l_g, 0},
  {LSM6_read_x_h_a, 0}, /*accelerometer xyz data*/
  {LSM6_read_x_l_a, 0},
  {LSM6_read_y_h_a, 0},
  {LSM6_read_y_l_a, 0},
  {LSM6_read_z_h_a, 0},
  {LSM6_read_z_l_a, 0}
};


/** IMU Init
 * @brief Initialize IMU to collect data
 * 
 * @param None
 * @return pdTRUE if initialization was successful, pdFALSE otherwise
 */
BaseType_t IMU_Init(void) {
  //Initialize SPI
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); // normally low, high when writing
  MX_SPI1_Init();

  // Initialize IMU, gyroscope, and accelerometer
  // NOTE: accelerometer and gyroscope features may be further configured, see IMU.h for more details
  // TODO: Configure gyroscope and accelerometer
  // TODO: now using 8 bit transfer 
  for(int i = 0; i < sizeof(imuInit)/sizeof(*imuInit); i ++){
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    HAL_SPI_Transmit(&hspi1, &imuInit[i], 2, NO_POLLING);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
  }

  // Initialize IMU hardware FIFO
  // NOTE: FIFO size, rate and mode may be further configured, see IMU.h for more details
  for(int i = 0; i < sizeof(fifoInit)/sizeof(*fifoInit); i ++){
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    HAL_SPI_Transmit(&hspi1, &fifoInit[i], 2, NO_POLLING); 
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
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
  int pTxData;
  int pRxData[2];
  // read for the length of the array, filling a buffer up with 
  for(int i = 0; i < sizeof(readDataReg)/sizeof(*readDataReg); i = i + 2){
    pTxData = readDataReg[i+1];
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    HAL_SPI_Transmit(&hspi1, &fifoInit[i], 1, NO_POLLING); 
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    pTxData = readDataReg[i+2];
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    HAL_SPI_Transmit(&hspi1, &fifoInit[i], 1, NO_POLLING); 
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    switch(i){ 
      case 0: Data->gyr_x = (pRxData1 << 8) | pRxData2; break;
      case 2: Data->gyr_y = (pRxData1 << 8) | pRxData2; break;
      case 4: Data->gyr_z = (pRxData1 << 8) | pRxData2; break;
      case 6: Data->accel_x = (pRxData1 << 8) | pRxData2; break;
      case 8: Data->accel_y = (pRxData1 << 8) | pRxData2; break;
      case 10: Data->accel_z = (pRxData1 << 8) | pRxData2; break;
     }
   }

}

/** IMU Read Data
 * 
 * @brief Update IMU struct with new data fetched from hardware FIFO
 * 
 * @param Data : Pointer to struct used to collect IMU Data
 * @return pdTRUE if data was successfully fetched from queue, pdFALSE if queue is empty
 */
BaseType_t IMU_ReadDataHWQueue(IMUData_t *Data){
  // TODO: test on hardware
  // ***WARNING***
  // behavior unpredictable until thourougly tested on hardware, recommend using IMU Read Data at the moment
  int pTxData = 0;
  int pRxData1 = 0;
  int pRxData2 = 0;

  pTxData = LSM6_FIFO_stored; /*check if FIFO empty*/
  HAL_SPI_TransmitReceive(&hspi1, &pTxData, &pRxData1, 1, NO_POLLING);
  if(pRxData1 == 0){
    return pdFalse;
  }
  pTxData = LSM6_FIFO_read_tag;  /*get tag*/
  HAL_SPI_TransmitReceive(&hspi1, &pTxData, &pRxData1, 1, NO_POLLING);

  if(pRxData == LSM6_Gyroscope_NC){ // may be the wrong FIFO tag, assumes gyroscope
    for(int i = 0; i < fifoQXYZregisters[0] - 1; i = i + 2){
      pTxData = fifoQXYZregisters[i+1];
      HAL_SPI_TransmitReceive(&hspi1, &pTxData, &pRxData1, 1, NO_POLLING);
     pTxData = fifoQXYZregisters[i+2];
     HAL_SPI_TransmitReceive(&hspi1, &pTxData, &pRxData2, 1, NO_POLLING);
     switch(i){
       case 0: Data->gyr_x = (pRxData1 << 8) | pRxData2; break;
       case 2: Data->gyr_y = (pRxData1 << 8) | pRxData2; break;
       case 4: Data->gyr_z = (pRxData1 << 8) | pRxData2; break;
     }
   }
  } else if(pRxData == LSM6_Accelerometer_NC){ // may be the wrong FIFO tag, assumes accelerometer
    for(int i = 0; i < fifoQXYZregisters[0] - 1; i = i + 2){
      pTxData = fifoQXYZregisters[i+1];
      HAL_SPI_TransmitReceive(&hspi1, &pTxData, &pRxData1, 1, NO_POLLING);
     pTxData = fifoQXYZregisters[i+2];
     HAL_SPI_TransmitReceive(&hspi1, &pTxData, &pRxData2, 1, NO_POLLING);
     switch(i){
       case 0: Data->accel_x = (pRxData1 << 8) | pRxData2; break;
       case 2: Data->accel_y = (pRxData1 << 8) | pRxData2; break;
       case 4: Data->accel_z = (pRxData1 << 8) | pRxData2; break;
     }
   }
  } else {
    // not accelerometer data
    return pdFalse;
  }

  return pdTrue;
}