#include "uart.h"

char vrc_Getc; // bien luu ki tu vua nhan
int vri_Stt; // bien trang thai
char vrc_Res[MAX]; // mang luu du lieu truyen qua uart
int vri_Count = 0; // bien dem so ki tu da nhan

void Uart_init(){
	GPIO_InitTypeDef gpio_tydef; // cau hinh gpio
	USART_InitTypeDef usart_tydef; // cau hinh uart
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // bat clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	// cau hinh tx = 9 
	gpio_tydef.GPIO_Pin = GPIO_Pin_9;
	gpio_tydef.GPIO_Mode = GPIO_Mode_AF_PP; // vi tx la ngo ra(output) nen phai cau hinh af_pp de phat tin hieu cho uart ra ngoai
	gpio_tydef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_tydef);
	// cau hinh  rx = 10
	gpio_tydef.GPIO_Pin = GPIO_Pin_10;
	gpio_tydef.GPIO_Mode = GPIO_Mode_IN_FLOATING; // vi du lieu uart tu ben ngoai da co muc logic chuan
																								// nen chi can de o dang in_floating de nhan dung tin hieu
	gpio_tydef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_tydef);
	
	usart_tydef.USART_BaudRate = 9600; //  chon baudrate
	usart_tydef.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // khong dung rtx/ctx
	usart_tydef.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // cho phep tx va rx
	usart_tydef.USART_Parity = USART_Parity_No; // k su dung bit kiem tra
	usart_tydef.USART_StopBits = USART_StopBits_1; // 1 stop bit
	usart_tydef.USART_WordLength = USART_WordLength_8b; // 8 bit data
	USART_Init(USART1, &usart_tydef);
	
	USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
	//cau hinh ngat nhan (RXNE)
	NVIC_EnableIRQ(USART1_IRQn); //cau hinh tong quat
	USART_Cmd(USART1,ENABLE); // kich hoat uart1
	
}
// ham gui du lieu
void Uart_Sendchar(char _chr){
	USART_SendData(USART1, _chr); // gui ki tu
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // cho gui xong
}
// ham gui chuoi du lieu
void Usart_Sendstr(char *str){
	while(*str != '\0'){ // gui tung ki tu den khi gap ki tu NULL
		Uart_Sendchar(*str++);
	}
}
// ham nhan du lieu
uint16_t UARTx_Getc(USART_TypeDef* USARTx){
    return USART_ReceiveData(USARTx);}
// ham ngat 
void USART1_IRQHandler(void){
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET){
	  vrc_Getc =UARTx_Getc(USART1); // lay ki tu nhan duoc
		if (vrc_Getc == '\r' || vrc_Getc == '\n') { // neu gap ki tu ket thuc chuoi
			if (vri_Count > 0) {       
        vrc_Res[vri_Count] = '\0'; // them NULL vaf terminal
        vri_Stt = 1; // danh dau da nhan xong 1 chuoi
        printf("%s\n", vrc_Res);  // in ra de debug
        vri_Count = 0; // reset bien dem
			}
		}

		else { // neu la ki tu binh thuong thi luu vao mang
			vrc_Res[vri_Count] = vrc_Getc;
      vri_Count++;			
		
		}
		
		}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE); // xoa co ngat
}
// hamf cho phep printf() de gui ra uart1
struct __FILE { int handle; };
FILE __stdout;

int fputc(int ch, FILE *f) {
    Uart_Sendchar((char)ch);   
    return ch;
}
