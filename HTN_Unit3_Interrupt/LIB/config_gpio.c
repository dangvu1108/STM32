#include "config_gpio.h"

void GPIO_Config(){
	GPIO_InitTypeDef led;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	led.GPIO_Mode = GPIO_Mode_Out_PP;
	led.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	led.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &led);
}

void Btn_Config(){
	GPIO_InitTypeDef btn;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	btn.GPIO_Mode = GPIO_Mode_IPU;
	btn.GPIO_Pin = GPIO_Pin_0;
	
	GPIO_Init(GPIOB, &btn);
}