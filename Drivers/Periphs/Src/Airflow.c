/**
 * @file Airflow.c
 * @brief Air Velocity Sensor API - FS3000
 * 
 * @copyright Copyright (c) 2023 UT Longhorn Racing Solar
 * 
 */

#include "Airflow.h"
#include "config.h"
#include <stdbool.h>
#include <stdio.h>
#include "cmsis_os.h"
#include <stdlib.h>

#define DEV_ADDR 0x28
#define ADDR (DEV_ADDR << 1)

/**
 * @brief Update struct with new information
 * @param *Data : struct used to collect Airflow Data
 * @return HAL_OK on success, Airflow_BUSY if called too soon after last call, HAL_StatusTypeDef != HAL_OK on error
 */
HAL_StatusTypeDef Airflow_GetMeasurements(AirflowData_t *Data){

    HAL_StatusTypeDef error = HAL_OK;
    static TickType_t ticks = 0;

    // return if less than 10ms has elapsed since last call
    if ((xTaskGetTickCount() - (ticks / portTICK_PERIOD_MS)) < 10) {  
        return Airflow_BUSY;
    }

    ticks = xTaskGetTickCount();

    // Read 5 bytes and stores data within struct fields
    error |= HAL_I2C_Master_Receive(&hi2c1, ADDR, (uint8_t*)Data, 5, HAL_MAX_DELAY);
    debugprintf("ERROR: %d\n\r", error);
    Data->flowData &= 0xFFF;

    // validate checksum
    if((Data->checksum + ((Data->flowData >> 8) & 0xFF) + (Data->flowData & 0xFF) + Data->generic1 + Data->generic2) != 0){
        error = HAL_ERROR;
        debugprintf("ERROR: Airflow: Invalid payload checksum\n\r");
    }

    return error;
}