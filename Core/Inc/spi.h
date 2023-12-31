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

#ifdef __cplusplus
extern "C" {
#endif

/* Header content ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_hal.h"

extern SPI_HandleTypeDef hspi1;
void MX_SPI1_Init(void)


#ifdef __cplusplus
}
#endif
#endif /*__ SPI_H__ */
