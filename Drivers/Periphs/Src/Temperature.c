/**
  ******************************************************************************
  * @file    Temperature.c
  * @brief   Temperature Sensor Driver - LMT87
  *          This file interfaces with the LMT87.
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

#include "Temperature.h"
#include "VoltToTemp.h"

/** Temperature Init
 * @brief Initialize the Temperature sensor
 * 
 * @return pdTRUE if initialization was successful, pdFALSE otherwise
*/
BaseType_t Temperature_Init(void) {
  MX_ADC1_Init();
}

/** milliVolt to Celsius
 * Converts mv to temperature based on the temperature sensor equation
 * Equation : T(in C) = (((13.582 - sqrt((-13.582)*(-13.582) + 4 * 0.00433 * (2230.8 - milliVolt)))/ (2.0 * -0.00433)) + 30)
 * @param mV from ADC
 * @return temperature in Celsius (Fixed Point with .001 resolution) 
 */
int32_t milliVoltToCelsius(uint32_t milliVolt){
	if (milliVolt < sizeof(voltToTemp)/sizeof(voltToTemp[0])) {
		return voltToTemp[milliVolt];
	}
	else {
		return TEMP_ERR_OUT_BOUNDS;
	}
}

/** Temperature Read Data
 * @brief Update temperature array with new data
 * 
 * @param Data Pointer to the temperature array
 * @return pdTRUE if data was successfully fetched from queue, pdFALSE if queue is empty
*/
BaseType_t Temperature_ReadData(TempData_t* Data){
  HAL_ADC_START(&hadc1);
  for(int i = 0; i < 3; i++){
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    switch(i){
      case 1: Data->temp1 = milliVoltToCelsius(HAL_ADC_GetValue(&hadc1));
      case 2: Data->temp2 = milliVoltToCelsius(HAL_ADC_GetValue(&hadc1));
      case 3: Data->temp3 = milliVoltToCelsius(HAL_ADC_GetValue(&hadc1));
    }
  }
}
