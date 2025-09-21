#include "uart.h"

char vrc_Getc;
int vri_Stt;
char vrc_Res[MAX];
int vri_Count = 0;

void Uart_init(){
	GPIO_InitTypeDef gpio_tydef;
	USART_InitTypeDef usart_tydef;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	gpio_tydef.GPIO_Pin = GPIO_Pin_9;
	gpio_tydef.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_tydef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_tydef);
	
	gpio_tydef.GPIO_Pin = GPIO_Pin_10;
	gpio_tydef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_tydef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_tydef);
	
	usart_tydef.USART_BaudRate = 9600;
	usart_tydef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_tydef.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart_tydef.USART_Parity = USART_Parity_No;
	usart_tydef.USART_StopBits = USART_StopBits_1;
	usart_tydef.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &usart_tydef);
	
	USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
	//cau hinh ngat nhan (RXNE)
	NVIC_EnableIRQ(USART1_IRQn); //cau hinh tong quat
	USART_Cmd(USART1,ENABLE);
	
}

void Uart_Sendchar(char _chr){
	USART_SendData(USART1, _chr);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Usart_Sendstr(char *str){
	while(*str != '\0'){
		Uart_Sendchar(*str++);
	}
}

uint16_t UARTx_Getc(USART_TypeDef* USARTx){
    return USART_ReceiveData(USARTx);}

void USART1_IRQHandler(void){
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET){
	  vrc_Getc =UARTx_Getc(USART1);
		if (vrc_Getc == '\r' || vrc_Getc == '\n') {
			if (vri_Count > 0) {       
        vrc_Res[vri_Count] = '\0';
        vri_Stt = 1;
        printf("%s\n", vrc_Res);  // debug
        vri_Count = 0;
			}
		}

		else {
			vrc_Res[vri_Count] = vrc_Getc;
      vri_Count++;			
		
		}
		
		}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}

struct __FILE { int handle; };
FILE __stdout;

int fputc(int ch, FILE *f) {
    Uart_Sendchar((char)ch);   
    return ch;
}
