#ifndef _exti_h_
#define _exti_h_

#include "stm32f10x_exti.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "semphr.h"                     // ARM.FreeRTOS::RTOS:Core
extern SemaphoreHandle_t xSemaphore;
void Interrupt_Config();
void EXTI0_IRQHandler(void);
#endif
