#ifndef TASKS_H
#define TASKS_H

#include "FreeRTOS.h"
#include "semphr.h"

void CANSendingTask(void* argument);

void DataReadingTask(void* argument);

#endif
