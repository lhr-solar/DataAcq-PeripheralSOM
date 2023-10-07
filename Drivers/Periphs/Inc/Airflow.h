/**
 * @file Airflow.h
 * @brief Air Velocity Sensor API - FS3000
 * 
 * @copyright Copyright (c) 2023 UT Longhorn Racing Solar
 * 
 */

#ifndef Airflow_H
#define Airflow_H

#include "main.h"
#include <stdint.h>

// Error code for indication Airflow is not ready to read yet
#define Airflow_BUSY                0x04u

typedef struct {
    uint8_t     checksum;   // main checksum
    uint16_t    flowData;   // 12 bit unsigned sensor flow data
    uint8_t     generic1;   // generic checksum data
    uint8_t     generic2;   // generic checksum data

} AirflowData_t;

/**
 * @brief Update struct with new information
 * @param *Data : struct used to collect Airflow Data
 * @return HAL_OK on success, Airflow_BUSY if called too soon after last call, HAL_StatusTypeDef != HAL_OK on error
 */
HAL_StatusTypeDef Airflow_GetMeasurements(AirflowData_t *Data);

#endif
