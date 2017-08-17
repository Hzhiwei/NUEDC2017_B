#ifndef __BSP_DMA_H
#define __BSP_DMA_H


#include "stm32f4xx.h"


void BSP_DMA_InitConfig(void);
void UART1_DMASend(uint8_t *Data, uint16_t DataLength);


#endif
