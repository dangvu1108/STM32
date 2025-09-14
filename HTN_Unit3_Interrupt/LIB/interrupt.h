#ifndef _exti_h_
#define _exti_h_

#include "stm32f10x_exti.h"
#include "delay.h"

extern uint8_t status;
void Interrupt_Config();
void EXTI0_IRQHandler(void);
#endif
