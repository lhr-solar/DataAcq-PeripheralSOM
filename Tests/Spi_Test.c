#include "stm32l431xx.h"
#include "stm32lf4xx_hal_gpio.h"
#include "stm32l4xx_hal_spi.h"
#include "stdint.h"

int main(){
    SPI_HandleTypeDef spi;

    uint8_t data;
    uint16_t size = 1;
    uint32_t timeout = 100;
    
    HAL_SPI_Init(&spi);
    while(1){
        HAL_SPI_Receive(&spi, &data, size, timeout);
        if(data == 1) break;
    }

    GPIO_TypeDef gpio;
    GPIO_InitTypeDef init;
    
    //HAL_GPIO_Init();


    
}
