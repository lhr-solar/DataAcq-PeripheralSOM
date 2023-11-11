/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
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
#ifndef __SPI_H__
#define __SPI_H__

/* Header content ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_spi.h"

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
void MX_SPI_Init(SPI_TypeDef* port);

#endif
