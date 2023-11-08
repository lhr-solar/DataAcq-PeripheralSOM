#include "adc.h"

ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

static void ADC_InitDMA(void) {
	// Create the DMA structure
	DMA_InitTypeDef DMA_InitStruct;

	DMA_InitStruct.Direction = DMA_PERIPH_TO_MEMORY;
	DMA_InitStruct.PeriphInc = DMA_PINC_DISABLE;
	DMA_InitStruct.MemInc = DMA_MINC_ENABLE;
	DMA_InitStruct.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    DMA_InitStruct.Request = DMA_REQUEST_0;
	DMA_InitStruct.Mode = DMA_CIRCULAR;
	DMA_InitStruct.Priority = DMA_PRIORITY_HIGH;
    DMA_InitStruct.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;

    //Might need more handle settings but idk
    hdma_adc.Init = DMA_InitStruct;

	HAL_DMA_Init(&hdma_adc);
}

/**
 * @brief   Initializes the ADC module.
 * @param   None
 * @return  None
 */
void ADC_Init(void) {
	ADC_InitDMA();

	// Set up to use DMA so that multiple channels can be used
	ADC_InitTypeDef ADC_InitStruct;	// Initialization structure
	ADC_InitStruct.Resolution = ADC_RESOLUTION_12B;	// High resolution
	ADC_InitStruct.ScanConvMode = ENABLE;						// So we can go through all the channels
	ADC_InitStruct.ContinuousConvMode = ENABLE; 		// Cycle the channels
	ADC_InitStruct.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	ADC_InitStruct.ExternalTrigConv = DISABLE;
	ADC_InitStruct.DataAlign = ADC_DATAALIGN_RIGHT;
	ADC_InitStruct.NbrOfConversion = 1;	

    hadc.Instance = ADC1;

	HAL_ADC_Init(&hadc);
}