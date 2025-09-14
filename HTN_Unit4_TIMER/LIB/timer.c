#include "timer.h"

void TIM_Config(){
	TIM_TimeBaseInitTypeDef timer;
	NVIC_InitTypeDef interrupt;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);
	timer.TIM_CounterMode = TIM_CounterMode_Up;
	timer.TIM_Period = 65535;
	timer.TIM_Prescaler = 2 - 1;
	
	TIM_TimeBaseInit(TIM2, &timer);
	
	timer.TIM_Period = 35999;
	timer.TIM_Prescaler = 999;
	
	TIM_TimeBaseInit(TIM3, &timer);
	
	//Cau hinh ngat timer
	TIM_ClearFlag(TIM3, TIM_FLAG_Update); // Xoa co cap nhat
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	interrupt.NVIC_IRQChannel = TIM3_IRQn;
	interrupt.NVIC_IRQChannelPreemptionPriority = 0;
	interrupt.NVIC_IRQChannelSubPriority = 0;
	interrupt.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&interrupt);
	
	TIM_Cmd(TIM3, ENABLE);
}

void Delay_1ms(){
	TIM_Cmd(TIM2, ENABLE); //Cho phep timer2 hoat dong
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2) < 36000); //	Lap den khi gia tri bo dem <36000
	TIM_Cmd(TIM2, DISABLE);
}

void Delay_ms(uint16_t time){
	while(time--) Delay_1ms();
}

void TIM3_IRQHandler(){
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){
		GPIOA -> ODR ^= 1;
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}