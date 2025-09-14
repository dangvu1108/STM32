#include "interrupt.h"
#include "delay.h"

uint8_t status = 0;
void Interrupt_Config(){
	NVIC_InitTypeDef nvic;
	EXTI_InitTypeDef exti;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	nvic.NVIC_IRQChannel = EXTI0_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
	
	NVIC_Init(&nvic);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	exti.EXTI_Line = EXTI_Line0;
	exti.EXTI_LineCmd = ENABLE;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&exti);
}

void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0) != RESET){
		status = 1;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
	
