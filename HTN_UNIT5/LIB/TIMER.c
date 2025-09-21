#include "timer.h"

void Tim_config(){
	TIM_TimeBaseInitTypeDef timer;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	timer.TIM_CounterMode = TIM_CounterMode_Up;
	timer.TIM_Period = 65535;
	timer.TIM_Prescaler = 2 - 1;
	
	TIM_TimeBaseInit(TIM2, &timer);
}

void Delay_1ms(){
	TIM_Cmd(TIM2, ENABLE);
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2) < 36000);
	TIM_Cmd(TIM2, DISABLE);
}

void Delay_ms(uint16_t time){
	while(time--) Delay_1ms();
}
