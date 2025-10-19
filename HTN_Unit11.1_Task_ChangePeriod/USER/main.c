#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x.h"                  // Device header
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "queue.h"                      // ARM.FreeRTOS::RTOS:Core

void Led_Config(){
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOA, &gpio);
}

QueueHandle_t periodQueue;  // Queue luu tan so (ms)

void Task_Blink(void *pvParameters){
	uint32_t Delay_ms = 800;
	while(1){
		xQueueReceive(periodQueue, &Delay_ms, 0);
		GPIOA -> ODR ^= GPIO_Pin_0;
		vTaskDelay(pdMS_TO_TICKS(Delay_ms/2));
	}
}

void Task_Change_Period(void *pvParameters){
    uint32_t PeriodList[] = {800, 400, 200, 100};  // ms
    uint8_t stt = 0;

    while (1) {
        xQueueSend(periodQueue, &PeriodList[stt], 0);
        stt = (stt + 1) % 4;
        vTaskDelay(pdMS_TO_TICKS(3000)); // doi freq moi 3 giây
    }	
}

int main(){

	SystemCoreClockUpdate();
	Led_Config();
	
	periodQueue = xQueueCreate(5, sizeof(uint32_t));
	xTaskCreate(Task_Blink, "BlinkLED", 128, NULL, 1, NULL);
	xTaskCreate(Task_Change_Period, "ChangePeriod", 128, NULL, 2, NULL);
	
	vTaskStartScheduler();
	
	while(1); //Ko bao h run toi day
}