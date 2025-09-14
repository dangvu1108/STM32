#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x.h"                  // Device header

void Config(){
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); //Bat clock cho GPIOA va GPIOB
	
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &gpio);
	GPIO_Init(GPIOB, &gpio);
	
}

void Delay_ms(uint16_t time){
	uint16_t i, j;
	for(i = 0; i < time; i++){
		for(j = 0; j < 0x2aff; j++);
	}
}
int main(){
	Config();
	while(1){
		// Dua dau ra cac chan set ve muc 0
		GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
		GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
		Delay_ms(500);
		// Dua dau ra cac chan set len muc 1
		GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
		GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
		Delay_ms(500);
	}
}

