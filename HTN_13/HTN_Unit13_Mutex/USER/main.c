#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "stm32f10x.h"
#include "uart.h"
#include "stdlib.h"
#include "semphr.h"                    

xSemaphoreHandle xMutex;

// Task nháy LED
void Task_1(void *pvParameters){
    while(1){
			xSemaphoreTake(xMutex, portMAX_DELAY);
      Uart_SendStr("AAAAAAA\n");
			xSemaphoreGive(xMutex);
			vTaskDelay(pdMS_TO_TICKS(10));
			
    }
}

// Task nháy LED
void Task_2(void *pvParameters){
    while(1){
			xSemaphoreTake(xMutex, portMAX_DELAY);
      Uart_SendStr("BBBBBBB\n	");
			
			xSemaphoreGive(xMutex);
			vTaskDelay(pdMS_TO_TICKS(12));
    }
}

int main(void){
    SystemCoreClockUpdate();
		Uart_Init();
		xMutex = xSemaphoreCreateMutex();
		xTaskCreate(Task_1, "A", 128, NULL, 1, NULL);
    xTaskCreate(Task_2, "B", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1);
}
