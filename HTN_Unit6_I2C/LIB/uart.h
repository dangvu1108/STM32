#ifndef _uart_h_
#define _uart_h_

#include "stdio.h"
#include "stm32f10x_usart.h"
#include "string.h"

void uart_Init(void);
void uart_SendChar(char _chr);
void uart_SendStr(char *str);
#endif
