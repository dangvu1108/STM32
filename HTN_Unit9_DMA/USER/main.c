#include "timer.h"
#include "uart.h"
#include "adc.h"
#include "dma.h"

extern uint8_t complete;
int main(){	
	Uart_Config();
	printf("UART Config Done\r\n");
	
	Tim_config();
	printf("TIMER Config Done\r\n");
	ADC_Config();
	printf("ADC Config Done\r\n");
	DMA_Config();
	printf("DMA Config Done\r\n");

	while(1){
		uint16_t Vin;
		while(complete == 0);
		if(complete == 1){
			Vin = dest[0] * 3.3 / 4096 * 1000;
			printf("Ket qua ADC thu duoc: %d\r\n", dest[0]);
			printf("V_in: %d (mV)\r\n\r\n", Vin);
			Delay_ms(1000);
			complete = 0;
		}
	}
}