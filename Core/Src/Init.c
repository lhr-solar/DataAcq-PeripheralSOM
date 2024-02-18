/**
  ******************************************************************************
  * File Name          : Init.c
  * Description        : Initialization Code
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

/* Includes ------------------------------------------------------------------*/
#include "Init.h"
#include "CANbus.h"
#include "IMU.h"
#include "Airflow.h"
#include "Temperature.h"

void InitializePeripherals(void) {
  
    HAL_GPIO_Init();
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; 
    HAL_GPIO_Init(GPIO_PIN_15, &GPIO_InitStruct);
    //GPIO_InitTypeDef

    // TODO: Initialize CAN
    // TODO: Initialize IMU
    // TODO: Initialize Airflow
    // TODO: Initialize Temperature
}