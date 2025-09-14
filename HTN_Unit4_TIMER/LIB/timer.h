#ifndef _timer_h_
#define _timer_h_

#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"

void TIM_Config();
void Delay_1ms();
void Delay_ms(uint16_t time);

#endif
