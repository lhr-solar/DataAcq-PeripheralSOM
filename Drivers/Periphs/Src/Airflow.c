/**
  ******************************************************************************
  * @file    Airflow.c
  * @brief   Air Velocity Sensor Driver - FS3000
  *          This file interfaces with the FS3000.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 LHR Solars.
  * All rights reserved.
  *
  * To be deployed on LHRS Peripheral SOM.
  *
  ******************************************************************************
  */

#include "Airflow.h"
#include "i2c.h"

/** Airflow Init
 * @brief Initialize the Airflow sensor
 * 
 * @return pdTRUE if initialization was successful, pdFALSE otherwise
*/
BaseType_t Airflow_Init(void) {
  // TODO: Initialize I2C
  // TODO: Initialize Sensor
}

/** Airflow Read Data
 * @brief Update Airflow struct with new data
 * 
 * @param Data Pointer to the data structure to be filled
 * @return pdTRUE if data was successfully fetched from queue, pdFALSE if queue is empty
*/
BaseType_t Airflow_ReadData(Airflow_Data_t* Data) {
  // TODO: Read data from sensor
}
