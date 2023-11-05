/**
  ******************************************************************************
  * @file    IMU.h
  * @brief   Inertial Measurement Unit API - LSM6DSV
  *          This file contains all the function prototypes for IMU.c
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
#ifndef __IMU_H__
#define __IMU_H__

#include "FreeRTOS.h"
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "spi.h"

#define COMMAND_ARR_SIZE 10

#define LSM6_SPI_READ 0b1
#define LSM6_SPI_WRITE 0b0

/*LSM6 Registers*/
#define LSM6_CFG_ACCESS 0x01
#define FIFO_CTRL_1 0x07 
#define FIFO_CTRL_2 0x08 
#define FIFO_CTRL_3 0x08 
#define FIFO_CTRL_4 0x09 
#define LSM6_CTRL_1 0x10
#define LSM6_CTRL_2 0x11
#define LSM6_CTRL_3 0x12
#define LSM6_CTRL_6 0x15
#define LSM6_CTRL_7 0x16
#define LSM6_CTRL_8 0x17
#define LSM6_CTRL_9 0x18
#define LSM6_CTRL_10 0x19
#define LSM6_FIFO_STATUS_1 0x1B
#define X_OFS_USR 0x73
#define Y_OFS_USR 0x74
#define Z_OFS_USR 0x75
#define FIFO_DATA_OUT_TAG 0x78
#define FIFO_DATA_OUT_X_L 0x79
#define FIFO_DATA_OUT_X_H 0x7A
#define FIFO_DATA_OUT_Y_L 0x7B
#define FIFO_DATA_OUT_Y_H 0x7C
#define FIFO_DATA_OUT_Z_L 0x7D
#define FIFO_DATA_OUT_Z_H 0x7E

/*LSM6 FIFO tag*/
#define LSM6_Gyroscope_NC  0x01
#define LSM6_Accelerometer_NC  0x02
#define LSM6_Temperature  0x03
#define LSM6_Timestamp  0x04
#define LSM6_CFG_Change  0x05
#define LSM6_Accelerometer_NC_T_2  0x06
#define LSM6_Accelerometer_NC_T_1  0x07
#define LSM6_Accelerometer_2xC  0x08
#define LSM6_Accelerometer_3xC  0x09
#define LSM6_Gyroscope_NC_T_2  0x0A
#define LSM6_Gyroscope_NC_T_1  0x0B
#define LSM6_Gyroscope_2xC  0x0C
#define LSM6_Gyroscope_3xC  0x0D
#define LSM6_Sensor_Hub_Slave_0  0x0E
#define LSM6_Sensor_Hub_Slave_1  0x0F
#define LSM6_Sensor_Hub_Slave_2  0x10
#define LSM6_Sensor_Hub_Slave_3  0x11
#define LSM6_Step_Counter  0x12

/*SPI Messages*/
/*IMU feature configuration*/
#define LSM6_cfg (0b00000000 << 8) || (LSM6_CFG_ACCESS << 1) || LSM6_SPI_WRITE

/* low power mode 1 (2 mean) at 240 hz*/
#define LSM6_accel_start (0b01000111 << 8) || (LSM6_CTRL_1 << 1) ||  LSM6_SPI_WRITE 

/* lower power mode at 240 hz*/
#define LSM6_gyro_start (0b01010111 << 8) || (LSM6_CTRL_2 << 1) || LSM6_SPI_WRITE 

/* reboot memory content and reset all control registers*/
#define LSM6_reboot (0b10000001 << 8) || (LSM6_CTRL_3 << 1) || LSM6_SPI_WRITE

/* gyroscope low-pass-filter 1 (unconfigured) */
#define LSM6_gyro_lpf1_cfg (0b00000000 << 8) || (LSM6_CTRL_6 << 1) || LSM6_SPI_WRITE

/* gyroscope LPF1 disabled*/
#define LSM6_gyro_lpf1_enable (1b00000000 << 8) || (LSM6_CTRL_7 << 1) || LSM6_SPI_WRITE

/* XL LPF2 and HP filter cutoff (unconfigured), dual channel mode (disabled), full scale selection (unconfigured)*/
#define LSM6_accel_dual_channel_cfg (0b00000000 << 8) || (LSM6_CTRL_8 << 1) || LSM6_SPI_WRITE

/* XL HPF reference mode (unconfigured), LPF2 and HPF fast setting mode (unconfigured), slope selection (unconfigured)
   XL high-resolution (unconfigured), XL offset bits (unconfigured), XL offset correction (unconfigured)*/
#define LSM6_accel_block_cfg (0b00000000 << 8) || (LSM6_CTRL_9 << 1) || LSM6_SPI_WRITE

/* Embeded function debug disabled, Gyroscope self-test selection (default), XL self-test selection (default) */
#define LSM6_debug_cfg (0b00000000 << 8) || (LSM6_CTRL_10 << 1) || LSM6_SPI_WRITE

/* FIFO watermark threshold: 1 LSB = TAG(1 byte) + 1 sensor (6 bytes), 0x28 = (40 bytes)*/
#define LSM6_FIFO_watermark (0b00101000 << 8) || (FIFO_CTRL_1 << 1) || LSM6_SPI_WRITE

/* FIFO depth limited to watermark, compression algo disabled, ODR change not batched,
   don't force uncompressed data, FSM dual channel not forced  */
#define LSM6_FIFO_data_cfg (0b10000000 << 8) || (FIFO_CTRL_2 << 1) || LSM6_SPI_WRITE

/* FIFO batch data rate (BDR) for gyro and XL (240hz)*/
#define LSM6_FIFO_BDR (0b01110111 << 8) || (FIFO_CTRL_3 << 1) || LSM6_SPI_WRITE

/* timestamp not batched in FIFO, temperature not batched in FIFO, EIS gyro not batched */
/* FIFO mode: continous*/
#define LSM6_FIFO_start_cfg (0b00000110 << 8) || (FIFO_CTRL_4 << 1) || LSM6_SPI_WRITE

#define LSM6_FIFO_read_tag (0b00000000 << 8) || (FIFO_DATA_OUT_TAG << 1) || LSM6_SPI_READ

#define LSM6_FIFO_read_x_l (0b00000000 << 8) || (FIFO_DATA_OUT_X_L << 1) || LSM6_SPI_READ
#define LSM6_FIFO_read_x_h (0b00000000 << 8) || (FIFO_DATA_OUT_X_H << 1) || LSM6_SPI_READ

#define LSM6_FIFO_read_y_l (0b00000000 << 8) || (FIFO_DATA_OUT_Y_L << 1) || LSM6_SPI_READ
#define LSM6_FIFO_read_y_h (0b00000000 << 8) || (FIFO_DATA_OUT_Y_H << 1) || LSM6_SPI_READ

#define LSM6_FIFO_read_z_l (0b00000000 << 8) || (FIFO_DATA_OUT_Y_L << 1) || LSM6_SPI_READ
#define LSM6_FIFO_read_z_h (0b00000000 << 8) || (FIFO_DATA_OUT_Y_H << 1) || LSM6_SPI_READ

#define LSM6_FIFO_stored (0b00000000 << 8) || (LSM6_FIFO_STATUS_1 << 1) || LSM6_SPI_READ

typedef struct {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyr_x;
    int16_t gyr_y;
    int16_t gyr_z;
} IMUData_t;

/** IMU Init
 * @brief Initialize IMU to collect data
 * 
 * @param None
 * @return pdTRUE if initialization was successful, pdFALSE otherwise
 */
BaseType_t IMU_Init(void);

/** IMU Read Data
 * 
 * @brief Update IMU struct with new data
 * @param Data : Pointer to struct used to collect IMU Data
 * @return pdTRUE if data was successfully fetched from queue, pdFALSE if queue is empty
 */
BaseType_t IMU_ReadData(IMUData_t *Data);

#endif /* __IMU_H__ */
