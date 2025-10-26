#include "FreeRTOS.h"
#include "task.h"
#include "stm32f10x.h"
#include "uart.h"
#include "stdlib.h"

// Task nháy LED
void Task_1(void *pvParameters){
    while(1){
      Uart_SendStr("AAAAAAA\n");

			vTaskDelay(pdMS_TO_TICKS(10));
			
    }
}

// Task nháy LED
void Task_2(void *pvParameters){
    while(1){
      Uart_SendStr("BBBBBBB\n	");

			vTaskDelay(pdMS_TO_TICKS(12));
    }
}

int main(void){
    SystemCoreClockUpdate();
		Uart_Init();

		xTaskCreate(Task_1, "A", 128, NULL, 1, NULL);
    xTaskCreate(Task_2, "B", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1);
}
