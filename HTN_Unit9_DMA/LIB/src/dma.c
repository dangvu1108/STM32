#include "dma.h"

uint16_t dest[1];
uint8_t complete = 0;
void DMA_Config(){
	RCC -> AHBENR |= 1;
	DMA1_Channel1 -> CCR |= ~1; // Tat DMA
	DMA1_Channel1 -> CPAR = (uint32_t) &(ADC1 -> DR); // Lay tu dia chi thanh ghi DR
	DMA1_Channel1 -> CMAR = (uint32_t) dest; // Kq truyen se duoc luu tai memory dest trong RAM
	DMA1_Channel1 -> CNDTR = 1; // Chuyen du lieu 1 lan
	DMA1_Channel1 -> CCR = (1 << 1) | (0x2 << 12) | (1 << 10) | (1 << 8) |(1 << 7) | (1 << 5); // Bat ngat khi truyen xog, Muc do uu tien cao, mem 16 bit, ngoai vi 16 bit, tang dia chi mem, lien tuc
	
	DMA1_Channel1 -> CCR |= 1; // Bat DMA Channel 1
	
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	
}

void DMA1_Channel1_IRQHandler(){
	if((DMA1 -> ISR & (1 << 1)) != 0){
		complete = 1;
		DMA1 -> IFCR = 1 << 1; // Clear flag TCIF
	}
}