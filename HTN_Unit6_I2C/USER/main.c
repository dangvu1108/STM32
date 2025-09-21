#include "stm32f10x.h"
#include "i2c.h"
#include "uart.h"
#include "timer.h"
#include "sensor.h"
#include <stdio.h>

int main(void) {
	Config_I2C();
	uart_Init();
	TIM_Config();

	BH1750_Init();  // Bat cam bien
	printf("Connect Done\n\r");
	Delay_ms(200);
	while(1) {
		uint16_t lux;
		printf("Ket qua doc du lieu cam bien:\r\n");
		lux = BH1750_ReadLight();
		printf("Lux = %u\r\n\n", lux);
		Delay_ms(2000);
	}
}
