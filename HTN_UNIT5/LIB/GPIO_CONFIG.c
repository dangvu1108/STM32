#include "config_gpio.h"

void Led_config(){
	GPIO_InitTypeDef led;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	led.GPIO_Mode = GPIO_Mode_Out_PP;
	led.GPIO_Pin = GPIO_Pin_13;
	led.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &led);
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}
