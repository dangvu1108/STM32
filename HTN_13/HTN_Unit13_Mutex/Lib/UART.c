#include "uart.h"

char vrc_Getc;
int vri_Stt;
char vrc_Res[MAX];
int vri_Count = 0;

void Uart_Init(){
	// enable clock
	RCC -> APB2ENR |= 0x4004; // Bat bit 2 (GPIOA) va bit 14 (UART1)

	GPIOA -> ODR |= (1 << 10); // Pull-up RX-PA10
	GPIOA -> CRH = 0x000008B0; // Cau hinh A9 (AF-PP) A10 (IPU)
	
	// usart configure
	USART1->BRR = 7500;	 // 72MHz/9600bps = 7500
	USART1->CR1 = 0x200C; // Enable UART, TE, RE (chuc nang truyen nhan)
	
	USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);

	USART_Cmd(USART1,ENABLE);
	
}

//Ham gui 1 ki tu
void uart_SendChar(char _chr){
	USART_SendData(USART1,_chr);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==0); // Doi co TC len 1 La truyen xong
}

//Gui 1 chuoi string
void Uart_SendStr(char *str){
	while(*str){
		uart_SendChar(*str++);		
	}
}

//Nhan du lieu tu UART
uint16_t UARTx_Getc(USART_TypeDef* USARTx){
    return USART_ReceiveData(USARTx);}
