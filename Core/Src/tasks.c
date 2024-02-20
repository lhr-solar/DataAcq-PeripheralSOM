/**
 * @file Tasks.c
 * All tasks run by the RTOS.
 *
 * @note  Assumes that all lower level functions are initialized in main.c
 * 
 * @copyright Copyright (c) 2023 UT Longhorn Racing Solar
 * 
 */

#include "tasks.h"
#include "Airflow.h"
#include "IMU.h"
#include "Temperature.h"
#include <string.h>
#include <stdio.h>

 /** dataRendingTask
 * @brief Task in charge of collecting data from sensors (Airflow, IMU, Temperature).
 *
 * @note  Data is added to the CAN TX queues.
 */

void dataReadingTask(void* argument){

    while(1) {
        // Add Airflow Data to TX Queue
        

        // Add IMU Data to TX Queue

        // Add Temperature Data to TX Queue
    }

}

 /** dataSendingTask
 * @brief Task in charge of transmitting CAN messages to the rest of the car.
 *
 * @note  Assumes that all lower level functions are initialized in main.c
 */

void dataSendingTask(void *argument){
    while (1){
        if (1/* Transmit attempt fails */) {
            taskYIELD();
        };
    }
}
