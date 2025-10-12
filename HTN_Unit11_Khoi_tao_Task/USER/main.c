#include "FreeRTOS.h"
#include "task.h"
#include "stm32f10x.h"
#include <stdint.h>

// Cau hinh phan cung cho 3 den LED tren cac chan PA0, PA1, PA2.
void GPIO_Config(void) {
    GPIO_InitTypeDef gpio;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // Cau hinh dong thoi 3 chan Pin 0, 1, 2 cua Port A
    gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP; // Che do Push-Pull
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);
}

//Task nhay LED 1 (PA0) voi tan so ~3Hz.
void LED1_Task(void *pvParameters) {
    for (;;) {
        // Dao trang thai cua chan PA0
        GPIOA->ODR ^= GPIO_Pin_0;
        // Tam dung task trong 333ms
        vTaskDelay(pdMS_TO_TICKS(333));
    }
}

//Task nhay LED 2 (PA1) voi tan so ~10Hz.
void LED2_Task(void *pvParameters) {
    for (;;) {
        // Dao trang thai cua chan PA1
        GPIOA->ODR ^= GPIO_Pin_1;
        // Tam dung task trong 100ms
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

//Task nhay LED 3 (PA2) voi tan so ~25Hz.
void LED3_Task(void *pvParameters) {
    for (;;) {
        // Dao trang thai cua chan PA2
        GPIOA->ODR ^= GPIO_Pin_2;
        // Tam dung task trong 40ms
        vTaskDelay(pdMS_TO_TICKS(40));
    }
}

int main(void) {
    // Cap nhat tan so clock he thong
    SystemCoreClockUpdate();
    // Goi ham cau hinh GPIO
    GPIO_Config();

    // Tao 3 task, moi task dieu khien mot den LED
    xTaskCreate(LED1_Task, "LED1", 128, NULL, 1, NULL); // Stack size co the giam xuong 128 cho task don gian nay
    xTaskCreate(LED2_Task, "LED2", 128, NULL, 1, NULL);
    xTaskCreate(LED3_Task, "LED3", 128, NULL, 1, NULL);

    // Bat dau bo lap lich cua FreeRTOS
    // Chuong trinh se khong bao gio chay qua dong nay
    vTaskStartScheduler();

    // Vong lap vo tan nay chi de de phong truong hop vTaskStartScheduler() tra ve (vi du: thieu bo nho)
    while (1){
        // Khong lam gi ca
    }
}

//Hook function nay se duoc goi neu co loi cap phat bo nho Heap.
void vApplicationMallocFailedHook(void)
{
    // Dung toan bo ngat va treo he thong de debug
    taskDISABLE_INTERRUPTS();
    while(1);
}