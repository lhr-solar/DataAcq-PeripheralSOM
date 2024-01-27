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

typedef enum lsm6_spi_rw{
  LSM6_SPI_READ = 0x80,
  LSM6_SPI_WRITE = 0x00
} lsm6_spi_rw_t;

/*LSM6 Registers*/
typedef enum lsm6_register_address{
  LSM6_CFG_ACCESS = 0x01,
  FIFO_CTRL_1 = 0x07,
  FIFO_CTRL_2 = 0x08,
  FIFO_CTRL_3 = 0x09, 
  FIFO_CTRL_4 = 0x0A,
  LSM6_CTRL_1 = 0x10, // 10000
  LSM6_CTRL_2 = 0x11,
  LSM6_CTRL_3 = 0x12,
  LSM6_CTRL_6 = 0x15,
  LSM6_CTRL_7 = 0x16,
  LSM6_CTRL_8 = 0x17,
  LSM6_CTRL_9 = 0x18,
  LSM6_CTRL_10 = 0x19,
  LSM6_FIFO_STATUS_1 = 0x1B,
  OUT_TEMP_L = 0x20,
  OUTX_L_G = 0x22,
  OUTX_H_G = 0x23,
  OUTY_L_G = 0x24,
  OUTY_H_G = 0x25,
  OUTZ_L_G = 0x26,
  OUTZ_H_G = 0x27,
  OUTX_L_A = 0x28,
  OUTX_H_A = 0x29,
  OUTY_L_A = 0x2A,
  OUTY_H_A = 0x2B,
  OUTZ_L_A = 0x2C,
  OUTZ_H_A = 0x2D,
  X_OFS_USR = 0x73,
  Y_OFS_USR = 0x74,
  Z_OFS_USR = 0x75,
  FIFO_DATA_OUT_TAG  = 0x78,
  FIFO_DATA_OUT_X_L  = 0x79,
  FIFO_DATA_OUT_X_H = 0x7A,
  FIFO_DATA_OUT_Y_L = 0x7B,
  FIFO_DATA_OUT_Y_H = 0x7C,
  FIFO_DATA_OUT_Z_L = 0x7D,
  FIFO_DATA_OUT_Z_H = 0x7E
}lsm6_register_address_t;

typedef enum lsm6_fifo_tag {
  LSM6_Gyroscope_NC = 0x01,
  LSM6_Accelerometer_NC = 0x02,
  LSM6_Temperature = 0x03,
  LSM6_Timestamp = 0x04,
  LSM6_CFG_Change = 0x05,
  LSM6_Accelerometer_NC_T_2 = 0x06,
  LSM6_Accelerometer_NC_T_1 = 0x07,
  LSM6_Accelerometer_2xC = 0x08,
  LSM6_Accelerometer_3xC = 0x09,
  LSM6_Gyroscope_NC_T_2 = 0x0A,
  LSM6_Gyroscope_NC_T_1 = 0x0B,
  LSM6_Gyroscope_2xC = 0x0C,
  LSM6_Gyroscope_3xC = 0x0D,
  LSM6_Sensor_Hub_Slave_0 = 0x0E,
  LSM6_Sensor_Hub_Slave_1 = 0x0F,
  LSM6_Sensor_Hub_Slave_2 = 0x10,
  LSM6_Sensor_Hub_Slave_3 = 0x11,
  LSM6_Step_Counter = 0x12
} lsm6_fifo_tag_t;

/*SPI Messages*/
typedef enum lsm6_spi_message{
/* IMU feature configuration */
LSM6_cfg = 0b00000000, // LSM6_CFG_ACCESS 

/* low power mode 1 (2 mean) at 240 hz */
LSM6_accel_start = 0b01000111, // LSM6_CTRL_1 

/* lower power mode at 240 hz */
LSM6_gyro_start = 0b01010111, // LSM6_CTRL_2

/* reboot memory content and reset all control registers */
LSM6_reboot = 0b10000101, // LSM6_CTRL_3 

/* gyroscope low-pass-filter 1 (unconfigured) */
LSM6_gyro_lpf1_cfg = 0b00000000, // LSM6_CTRL_6 

/* gyroscope LPF1 disabled */
LSM6_gyro_lpf1_enable = 0b00000000, // LSM6_CTRL_7 

/* XL LPF2 and HP filter cutoff (unconfigured), dual channel mode (disabled), full scale selection (unconfigured) */
LSM6_accel_dual_channel_cfg = 0b00000000, // LSM6_CTRL_8

/* XL HPF reference mode (unconfigured), LPF2 and HPF fast setting mode (unconfigured), slope selection (unconfigured)
   XL high-resolution (unconfigured), XL offset bits (unconfigured), XL offset correction (unconfigured) */
LSM6_accel_block_cfg = 0b00000000, // LSM6_CTRL_9

/* Embeded function debug disabled, Gyroscope self-test selection (default), XL self-test selection (default) */
LSM6_debug_cfg = 0b00000000, //  LSM6_CTRL_10

/* FIFO watermark threshold: 1 LSB = TAG(1 byte) + 1 sensor (6 bytes), 0x28 = (40 bytes) */
LSM6_FIFO_watermark = 0b00101000, // FIFO_CTRL_1

/* FIFO depth limited to watermark, compression algo disabled, ODR change not batched,
   don't force uncompressed data, FSM dual channel not forced  */
LSM6_FIFO_data_cfg = 0b10000000, // FIFO_CTRL_2

/* FIFO batch data rate (BDR) for gyro and XL (240hz) */
LSM6_FIFO_BDR = 0b01110111, // FIFO_CTRL_3

/* timestamp not batched in FIFO, temperature not batched in FIFO, EIS gyro not batched */
/* FIFO mode: continuous */
LSM6_FIFO_start_cfg = 0b00000110, // FIFO_CTRL_4

// all these registers are only read from
LSM6_FIFO_read_tag = FIFO_DATA_OUT_TAG | LSM6_SPI_READ,

LSM6_FIFO_read_x_l = FIFO_DATA_OUT_X_L | LSM6_SPI_READ,
LSM6_FIFO_read_x_h = FIFO_DATA_OUT_X_H | LSM6_SPI_READ,

LSM6_FIFO_read_y_l = FIFO_DATA_OUT_Y_L | LSM6_SPI_READ,
LSM6_FIFO_read_y_h = FIFO_DATA_OUT_Y_H | LSM6_SPI_READ,

LSM6_FIFO_read_z_l = FIFO_DATA_OUT_Y_L | LSM6_SPI_READ,
LSM6_FIFO_read_z_h = FIFO_DATA_OUT_Y_H | LSM6_SPI_READ,

LSM6_FIFO_stored = LSM6_FIFO_STATUS_1 | LSM6_SPI_READ,

LSM6_read_x_l_g = OUTX_L_G | LSM6_SPI_READ,
LSM6_read_x_h_g = OUTX_H_G | LSM6_SPI_READ,
LSM6_read_y_l_g = OUTY_L_G | LSM6_SPI_READ,
LSM6_read_y_h_g = OUTY_H_G | LSM6_SPI_READ,
LSM6_read_z_l_g = OUTZ_L_G | LSM6_SPI_READ,
LSM6_read_z_h_g = OUTZ_H_G | LSM6_SPI_READ,

LSM6_read_x_l_a = OUTX_L_A | LSM6_SPI_READ,
LSM6_read_x_h_a = OUTX_H_A | LSM6_SPI_READ,
LSM6_read_y_l_a = OUTY_L_A | LSM6_SPI_READ,
LSM6_read_y_h_a = OUTY_H_A | LSM6_SPI_READ,
LSM6_read_z_l_a = OUTZ_L_A | LSM6_SPI_READ,
LSM6_read_z_h_a = OUTZ_H_A | LSM6_SPI_READ
} lsm6_spi_message_t;

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

/** IMU Read Data from Hardware FIFO 
 * 
 * WARNING: DO NOT USE
 * @brief Update IMU struct with new data
 * @param Data : Pointer to struct used to collect IMU Data
 * @return pdTRUE if data was successfully fetched from queue, pdFALSE if queue is empty
 */
// BaseType_t IMU_ReadDataHWQueue(IMUData_t *Data);



#endif /* __IMU_H__ */
