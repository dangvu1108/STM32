#ifndef _uart_h
#define _uart_h

#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stdio.h"
#include "string.h"
#define MAX 100

extern char vrc_Getc;
extern int vri_Stt;
extern char vrc_Res[MAX];	
extern int vri_Count;
void Uart_init();
void Uart_Sendchar(char _chr);
void Usart_Sendstr(char *str);
uint16_t UARTx_Getc(USART_TypeDef* USARTx);
#endif
