#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "uart.h"

#define EVENT_LED 1
#define EVENT_BUZZER (1 << 1)
#define EVENT_UART (1 << 2)
#define EVENT_ALL ((1 << 3) - 1) 

EventGroupHandle_t event_handle;
void GPIO_Config(){
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &gpio);
}

void Task_Control(void *pvParameters){
	
	while(1){
		xEventGroupSetBits(event_handle, EVENT_BUZZER);
		vTaskDelay(pdMS_TO_TICKS(2000));
		xEventGroupSetBits(event_handle, EVENT_LED);
		vTaskDelay(pdMS_TO_TICKS(1000));
		xEventGroupSetBits(event_handle, EVENT_UART);
		vTaskDelay(pdMS_TO_TICKS(1000));
		xEventGroupSetBits(event_handle, EVENT_ALL);
		vTaskDelay(pdMS_TO_TICKS(2000));		
	}
}

void Task_LED(void *pvParameters){
	EventBits_t event;
	while(1){
		event = xEventGroupWaitBits(event_handle, EVENT_LED, pdTRUE, pdFALSE, portMAX_DELAY);
		if(event & EVENT_LED){
			GPIOA -> ODR ^= 1;
		}
	}
}

void Task_Buzzer(void *pvParameters){
	EventBits_t event;
	while(1){
		event = xEventGroupWaitBits(event_handle, EVENT_BUZZER, pdTRUE, pdFALSE, portMAX_DELAY);
		if(event & EVENT_BUZZER){
			GPIOA -> ODR ^= GPIO_Pin_1;
		}
	}
}

void Task_UART(void *pvParameters){
	EventBits_t event;
	while(1){
		event = xEventGroupWaitBits(event_handle, EVENT_UART, pdTRUE, pdFALSE, portMAX_DELAY);
		if(event & EVENT_UART){
			Uart_SendStr("LED va Buzzer da dao trang thai\n\r");
		}
	}
}

int main(){
	GPIO_Config();
	Uart_Config();
	event_handle = xEventGroupCreate();
	xTaskCreate(Task_Control, "Control", 128, NULL, 2, NULL);
	xTaskCreate(Task_LED, "BlinkLED", 128, NULL, 1, NULL);
	xTaskCreate(Task_Buzzer, "Buzzer", 128, NULL, 1, NULL);
	xTaskCreate(Task_UART, "Fan", 128, NULL, 1, NULL);
	
	vTaskStartScheduler();
	while(1);
}