/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   This file contains all the function prototypes for
  *          the i2c.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Header content ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;
void MX_I2C1_Init(void);


#ifdef __cplusplus
}
#endif
#endif /*__ I2C_H__ */
