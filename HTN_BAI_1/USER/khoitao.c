#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC

void Delay_ms(uint16_t time){
	uint16_t i, j;
	for(i = 0; i < time; i++){
		for(j = 0; j < 0x2aff; j++);
	}
}
	
int main(){
	//Ham config
	while(1){}	//Chuong trinh chinh
}
