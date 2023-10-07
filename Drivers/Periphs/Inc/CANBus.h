/**
 * @file CANBus.h
 * @brief CAN Drivers
 * 
 * Initialize and configure a singular CANBus
 * Currently set up for CAN1
 * 
 * Recieved CAN messages are placed in an external software FIFO.
 * "queue.h" has information on FIFO operations
 * @copyright Copyright (c) 2022 UT Longhorn Racing Solar
 * 
 */

#ifndef CAN_BUS_H
#define CAN_BUS_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "queue.h"
#include <stdbool.h>


/**
 * Filter and HAL RX_FIFO configurations
 * Set FILTER_MASK_ID_LOW/HIGH to 0 to recieve all can messages
 */
#define CAN_RX_FIFO_NUMBER      CAN_RX_FIFO0    /* CAN_RX_FIFO0 or CAN_RX_FIFO1 */
#define FILTER_BANK             0          /* 0 - 13 for CAN1, 14 - 27 for CAN2 */
#define FILTER_ID_LOW           0x0000
#define FILTER_ID_HIGH          0x0000
#define FILTER_MASK_ID_LOW      0x0000
#define FILTER_MASK_ID_HIGH     0x0000

/**
 * CAN Message Structure
 */

// Enum for ID's of all messages that can be sent across CAN bus
// IDs must be listed in strictly increasing order!

typedef enum {
    // ID's here
    LARGEST_CAN_ID                                          // For the lookup table size
} CANId_t;

// Union of data that can be sent across CAN bus. Only one field must be filled out
typedef union {
	uint8_t b;
	uint16_t h;
	uint32_t w;
	float f;
    uint8_t bytes[8];   // use when data matches no normal datatype
} CANData_t;

/**
 * @note    idx is only used when an array of data needs to be sent.
 * @note    data is a union so only one of the fields should be filled out or bad stuff will happen.
 */
typedef struct {
	uint8_t idx;
	CANData_t data;
} CANPayload_t;

// This data type is used to push messages onto the queue
typedef struct {
    CANId_t id;
    CANPayload_t payload;
} CANMSG_t;

// Used to format the fields in the CAN metadata lookup table

struct CanLUTEntry {uint8_t idx_used : 1; uint8_t len : 7;};

/** CAN Config
 * @brief Initialize CAN, configure CAN filters/interrupts, and start CAN
 * 
 * @param mode CAN_MODE_NORMAL or CAN_MODE_LOOPBACK for operation mode
 * @return HAL_StatusTypeDef - Status of CAN configuration
 */
HAL_StatusTypeDef CAN_Init(uint32_t mode);

/** CAN Fetch Message
 * @brief Fetch a CAN message from the queue
 * @note This is a wrapper for xQueueReceive and should not be called from an ISR
 * 
 * @param message Fetched message will be put here
 * @return BaseType_t pdTRUE if CAN message was successfully fetched from queue,
 *                    pdFALSE if queue is empty
 */
BaseType_t CAN_FetchMessage(CANMSG_t *message);

/** CAN Transmit
 * @brief Creates can message and adds it to transmit queue
 * @note Wrapper for CAN_FormPacket and CAN_PutInTransmitQueue
 * @param StdId CAN message ID
 * @param TxData Data to transmit
 * @return BaseType_t - pdTrue formed, errQUEUE_FULL if full, HAL_ERROR if invalid ID
 */
BaseType_t CAN_TransmitNew(uint32_t StdId, uint8_t *TxData);

/** CAN Transmit Message
 * @brief Transmit message over CAN
 * @note Does not remove message from queue if transmit Mailbox is full (HAL_CAN_AddTxMessage fails)
 * @return HAL_StatusTypeDef - Status of CAN configuration
 */
HAL_StatusTypeDef CAN_TransmitMessage();

/**
 * @brief Fetch metadata associated with an id
 * @return True if valid entry, False if invalid
 */
bool CAN_FetchMetadata(CANId_t id, struct CanLUTEntry *entry);

/**
 * @brief Fetch number of dropped CAN messages due to queue overfilling.
 *        Included for debug purposes
 * @return Number of dropped messages
 */
uint32_t CAN_FetchDroppedMsgCnt();

#endif /* CAN_BUS_H */
