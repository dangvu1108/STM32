#include "stm32f10x.h"
#include <stdio.h>

/* Delay don gi?n */
void delay_ms(uint16_t t) {
    uint16_t i, j;
    for (i = 0; i < t; i++)
        for (j = 0; j < 0x2AFF; j++);
}

/* UART1 Init (PA9 TX, PA10 RX) */
void uart_init(uint32_t baud) {
    GPIO_InitTypeDef gpio;
    USART_InitTypeDef us;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    /* PA9 = TX */
    gpio.GPIO_Pin = GPIO_Pin_9;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);

    /* PA10 = RX */
    gpio.GPIO_Pin = GPIO_Pin_10;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio);

    us.USART_BaudRate = baud;
    us.USART_WordLength = USART_WordLength_8b;
    us.USART_StopBits = USART_StopBits_1;
    us.USART_Parity = USART_Parity_No;
    us.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    us.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &us);
    USART_Cmd(USART1, ENABLE);
}

void uart_send_char(char c) {
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, c);
}

void uart_send_str(char *s) {
    while (*s) uart_send_char(*s++);
}

/* SPI2 Init (PB13 SCK, PB14 MISO, PB15 MOSI, PB12 CS) */
#define CS_LOW()   GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define CS_HIGH()  GPIO_SetBits(GPIOB, GPIO_Pin_12)

void spi2_init(void) {
    GPIO_InitTypeDef gpio;
    SPI_InitTypeDef spi;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    /* SCK, MOSI */
    gpio.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &gpio);

    /* MISO */
    gpio.GPIO_Pin = GPIO_Pin_14;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &gpio);

    /* CS */
    gpio.GPIO_Pin = GPIO_Pin_12;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio);
    CS_HIGH();

    spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spi.SPI_Mode = SPI_Mode_Master;
    spi.SPI_DataSize = SPI_DataSize_8b;
    spi.SPI_CPOL = SPI_CPOL_Low;
    spi.SPI_CPHA = SPI_CPHA_1Edge;
    spi.SPI_NSS = SPI_NSS_Soft;
    spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;  
    spi.SPI_FirstBit = SPI_FirstBit_MSB;
    spi.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &spi);
    SPI_Cmd(SPI2, ENABLE);
}

uint8_t spi2_transfer(uint8_t data) {
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI2, data);
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI2);
}

int main() {
    uint8_t tx = 0x55;   
    uint8_t rx;          
    char buf[32];

    SystemInit();
    uart_init(9600);
    spi2_init();

    uart_send_str("SPI Test Start\r\n");

    CS_LOW();               
    rx = spi2_transfer(tx); 
    CS_HIGH();

    sprintf(buf, "Sent: 0x%02X, Received: 0x%02X\r\n", tx, rx);
    uart_send_str(buf);

    while (1);  
}





