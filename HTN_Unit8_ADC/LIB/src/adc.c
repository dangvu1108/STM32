#include "adc.h"

void ADC_Config(){
	RCC -> APB2ENR |= (1 << 9) | (1 << 2); // Bat clock cho GPIOA (2) va ADC1 (9)
	GPIOA -> CRL = 0x44444404; // Cau hinh PA1 o che do Analog input
	
	ADC1 -> CR2 |= 1; // ADC on
	Delay_1ms();
	ADC1 -> CR2 |= (1 << 1); // Bat Continuous
	ADC1 -> SMPR2 |= (0x4 << 3); // 41.5 cycles cho kênh 1
	// Hieu chinh ADC
	ADC1 -> CR2 |= (1 << 2); // Bat bit CAL (bit 2) len 1 de hieu chinh ADC 
	while(ADC1 -> CR2 & (1 << 2)); // Cho hieu chuan ADC
	
	ADC1 -> SQR3 = 1; // Chon kenh 1 la dau ra thong thuong (thu tu uu tien)
}