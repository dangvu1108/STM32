#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC

void LED_Config(){
	GPIO_InitTypeDef led;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	led.GPIO_Mode = GPIO_Mode_Out_PP;
	led.GPIO_Pin = GPIO_Pin_13;
	led.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &led);
}

void Button_Config(){
	GPIO_InitTypeDef btn;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	btn.GPIO_Mode = GPIO_Mode_IPU;
	btn.GPIO_Pin = GPIO_Pin_0;
	btn.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &btn);
}

void Interrupt_Config(){
	NVIC_InitTypeDef nvic;
	EXTI_InitTypeDef exti;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	nvic.NVIC_IRQChannel = EXTI0_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE; // Cho phep hoac cam ngat ngoai vi dag cau hinh tai NVIC
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
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void Delay_ms(uint16_t time){
	uint16_t i, j;
	for(i = 0; i < time; i++){
		for(j = 0; j < 0x2aff; j++);
	}
}

int main(){
	LED_Config();
	Button_Config();
	Interrupt_Config();
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	while(1){
		GPIOC -> ODR ^= GPIO_Pin_13;
		Delay_ms(5000);
		
		__WFI();
	}
}