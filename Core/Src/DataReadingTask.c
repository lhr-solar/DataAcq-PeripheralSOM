/**
 * @file DataReadingTask.c
 * 
 * Task in charge of collecting data from sensors (Airflow, IMU, Temperature).
 * Data is added to the CANTransmit queues.
 * @note Assumes that all lower level functions are initialized in main.c  
 * 
 * @copyright Copyright (c) 2023 UT Longhorn Racing Solar
 * 
 */

#include "Tasks.h"
#include "Airflow.h"
#include "CANBus.h"
#include <string.h>
#include <stdio.h>

void DataReadingTask(void* argument){
    
    CANMSG_t CANData;
    AirflowData_t AirflowData;

    while(1) {
        // Send Airflow data
        if (Airflow_GetMeasurements(&AirflowData) == HAL_OK){
            CAN_TransmitNew(0x1, AirflowData->flowData);    // TODO: get actual id
        }
        // Send IMU Data

        // Send Temperature Data
    }
}
