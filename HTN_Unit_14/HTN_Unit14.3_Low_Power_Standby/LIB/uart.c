#include "uart.h"

char vrc_Getc;
int vri_Stt;
char vrc_Res[MAX];
int vri_Count = 0;

void Uart_Config(){
	GPIO_InitTypeDef gpio_typefef;
	USART_InitTypeDef usart_typedef;
	//Bat clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//Config pin TX-A9
	gpio_typefef.GPIO_Pin = GPIO_Pin_9;
	gpio_typefef.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_typefef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_typefef);
	//Config pin RX-A10;
	gpio_typefef.GPIO_Pin = GPIO_Pin_10;
	gpio_typefef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_typefef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_typefef);
	// usart config
	usart_typedef.USART_BaudRate = 9600;
	usart_typedef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_typedef.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart_typedef.USART_Parity = USART_Parity_No;
	usart_typedef.USART_StopBits = USART_StopBits_1;
	usart_typedef.USART_WordLength =USART_WordLength_8b;
	USART_Init(USART1, &usart_typedef);
	USART_Cmd(USART1, ENABLE);
	
}

//Ham gui 1 ki tu
void Uart_SendChar(char _chr){
	USART_SendData(USART1,_chr);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==0); // Doi co TC len 1 La truyen xong
}

//Gui 1 chuoi string
void Uart_SendStr(char *str){
	while(*str){
		Uart_SendChar(*str++);		
	}
}