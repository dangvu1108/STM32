#include "timer.h"

void TIM_Config(){
	TIM_TimeBaseInitTypeDef timer;
	NVIC_InitTypeDef interrupt;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);
	timer.TIM_CounterMode = TIM_CounterMode_Up;
	timer.TIM_Period = 65535;
	timer.TIM_Prescaler = 2 - 1;
	
	TIM_TimeBaseInit(TIM2, &timer);
}

void Delay_1ms(){
	TIM_Cmd(TIM2, ENABLE); //Cho phep timer2 hoat dong
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2) < 36000); //	Lap den khi gia tri bo dem <36000
	TIM_Cmd(TIM2, DISABLE);
}

void Delay_1us(){
	TIM_Cmd(TIM2, ENABLE); //Cho phep timer2 hoat dong
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2) < 36); //	Lap den khi gia tri bo dem <36
	TIM_Cmd(TIM2, DISABLE);
}

void Delay_ms(uint16_t time){
	while(time--) Delay_1ms();
}

void Delay_us(uint16_t time){
	while(time--) Delay_1us();
}