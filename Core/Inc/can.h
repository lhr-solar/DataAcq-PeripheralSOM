/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
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
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Header content ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_hal.h"

extern CAN_HandleTypeDef hcan1;
void MX_CAN1_Init_Old(void);


#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

