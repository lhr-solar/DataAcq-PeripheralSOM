#ifndef TASKS_H
#define TASKS_H

#include "FreeRTOS.h"
#include "semphr.h"

void dataSendingTask(void* argument);

void dataReadingTask(void* argument);

#endif