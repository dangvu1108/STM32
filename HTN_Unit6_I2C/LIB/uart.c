#include "uart.h"

//Ham duoi day de goi printf ra uart
struct __FILE {
    int dummy;
};
FILE __stdout;
 
int fputc(int ch, FILE *f) {
 
    uart_SendChar(ch);
  
    return ch;
}

void uart_Init(void){
	// enable clock
	RCC -> APB2ENR |= 0x4004; // Bat bit 2 (GPIOA) va bit 14 (UART1)
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	GPIOA -> ODR |= (1 << 10); // Pull-up RX-PA10
	GPIOA -> CRH = 0x000008B0; // Cau hinh A9 (AF-PP) A10 (IPU)
//	// congifgure pin Tx - A9 mode AF_PP
//	gpio_typedef.GPIO_Pin = GPIO_Pin_9;
//	gpio_typedef.GPIO_Mode = GPIO_Mode_AF_PP;
//	gpio_typedef.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&gpio_typedef);	
//	// configure pin Rx - A10 mode Input floating
//	gpio_typedef.GPIO_Pin = GPIO_Pin_10;
//	gpio_typedef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	gpio_typedef.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&gpio_typedef);
	
	// usart configure
	USART1->BRR = 7500;	 // 72MHz/9600bps = 7500
	USART1->CR1 = 0x200C; // Enable UART, TE, RE (chuc nang truyen nhan)
//	usart_typedef.USART_BaudRate = 9600;
//	usart_typedef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	usart_typedef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
//	usart_typedef.USART_Parity = USART_Parity_No;
//	usart_typedef.USART_StopBits = USART_StopBits_1;
//	usart_typedef.USART_WordLength = USART_WordLength_8b;
//	USART_Init(USART1, &usart_typedef);
//	
//	USART_Cmd(USART1, ENABLE);
}

//Ham gui 1 ki tu
void uart_SendChar(char _chr){
	//while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==0); // Chua san sang nhan du lieu moi, TXE len 1 khi DR trong
	USART_SendData(USART1,_chr);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==0); // Doi co TC len 1 la truyen xong
}

//Gui 1 chuoi string
void uart_SendStr(char *str){
	while(*str){
		uart_SendChar(*str++);		
	}
}
