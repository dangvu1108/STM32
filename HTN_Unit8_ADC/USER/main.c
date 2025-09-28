#include "adc.h"
#include "timer.h"
#include "uart.h"

int main(){
	Uart_Config();
	Tim_config();
	ADC_Config();
	while(1){
		uint16_t i = 0, Vin;
		ADC1 -> CR2 |= 1 ; // ADC on
		while((ADC1 -> SR & (1 << 1)) == 0); //Cho co EOC = 1 la conversion complete
		i = ADC1 -> DR;
		Vin = i * 3.3 / 4096 * 1000;
		printf("V in: %d (mV)\n\r", Vin);
		Delay_ms(1000);
	}
}