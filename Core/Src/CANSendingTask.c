/**
 * @file CANSendingTask.c
 * 
 * Task in charge of transmitting CAN messages to the rest of the car.
 * @note Assumes that all lower level functions are initialized in main.c     
 * 
 * @copyright Copyright (c) 2023 UT Longhorn Racing Solar
 * 
 */

#include "Tasks.h"
#include "CANBus.h"
#include <stdio.h>

void CANSendingTask(void *argument){
    while (1){
        if (CAN_TransmitMessage() != HAL_OK) {
            taskYIELD();
        };
    }
}
