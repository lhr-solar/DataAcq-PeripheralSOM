/**
  ******************************************************************************
  * @file    Airflow.h
  * @brief   Air Velocity Sensor API - FS3000
  *          This file contains all the function prototypes for Airflow.c
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AIRFLOW_H__
#define __AIRFLOW_H__

#include "FreeRTOS.h"
#include <stdint.h>

// TODO: defines

typedef struct {
    uint16_t velocity;
    // other necessary fields
} Airflow_Data_t;

/** Airflow Init
 * @brief Initialize the Airflow sensor
 * 
 * @return pdTRUE if initialization was successful, pdFALSE otherwise
*/
BaseType_t Airflow_Init(void);

/** Airflow Read Data
 * @brief Update Airflow struct with new data
 * 
 * @param Data Pointer to the data structure to be filled
 * @return pdTRUE if data was successfully fetched from queue, pdFALSE if queue is empty
*/
BaseType_t Airflow_ReadData(Airflow_Data_t* Data);

#endif /* __AIRFLOW_H__ */