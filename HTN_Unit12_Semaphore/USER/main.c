#include "stm32f10x.h"                  // Device header
#include "interrupt.h"                   // ARM.FreeRTOS::RTOS:Core
#include "uart.h"
#include "semphr.h"                     // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

extern SemaphoreHandle_t xSemaphore;

void LED_Config(){
	GPIO_InitTypeDef led;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	led.GPIO_Mode =GPIO_Mode_Out_PP;
	led.GPIO_Pin = GPIO_Pin_13;
	led.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &led);
}

void Coi_Config(){
	GPIO_InitTypeDef coi;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	coi.GPIO_Mode =GPIO_Mode_Out_PP;
	coi.GPIO_Pin = GPIO_Pin_0;
	coi.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &coi);
}

void Button_Config(){
	GPIO_InitTypeDef btn;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	btn.GPIO_Mode =GPIO_Mode_IPU;
	btn.GPIO_Pin = GPIO_Pin_0;
	
	GPIO_Init(GPIOB, &btn);
}
void Task_Coi(void *pvParameters){
	while(1){
			if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == 1){	
				vTaskDelay(pdMS_TO_TICKS(50));
				if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0){
					GPIO_ResetBits(GPIOA, GPIO_Pin_0);
					vTaskDelay(pdMS_TO_TICKS(200));
					GPIO_SetBits(GPIOA, GPIO_Pin_0);				
				}
			}
	}
}
void Task_Blink(void *pvParameters){
	while(1){
		GPIOC->ODR ^= (1<<13); // Toggle LED
		vTaskDelay(pdMS_TO_TICKS(100));
	}
}
int main(){
	Uart_init();
	LED_Config();
	Button_Config();
	Coi_Config();
	xSemaphore = xSemaphoreCreateBinary();
	Interrupt_Config();
	
	xTaskCreate(Task_Blink, "BlinkLed", 128, NULL, 1, NULL);
	xTaskCreate(Task_Coi, "Warning", 128, NULL, 1, NULL);

	GPIO_SetBits(GPIOA, GPIO_Pin_0);
	
	vTaskStartScheduler();
	
	while(1){}
}