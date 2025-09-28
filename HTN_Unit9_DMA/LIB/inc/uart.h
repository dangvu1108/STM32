#ifndef _uart_h
#define _uart_h

#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stdio.h"
#include "string.h"

void Uart_Config();
void Uart_SendChar(char _chr);
void Uart_SendStr(char *str);
#endif
