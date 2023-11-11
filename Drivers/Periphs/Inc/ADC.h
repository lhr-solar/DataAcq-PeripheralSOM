
#include "stm32l4xx_hal.h"

extern ADC_HandleTypeDef hadc;
extern DMA_HandleTypeDef hdma_adc;

/**
 * @brief   Initializes the ADC module. 
 * @param   None
 * @return  None
 */
void ADC_Init(void);