#ifndef __dma_h
#define __dma_h

#include "adc.h"

extern uint16_t dest[1];
extern uint8_t complete;
void DMA_Config();
void DMA1_Channel1_IRQHandler();

#endif
