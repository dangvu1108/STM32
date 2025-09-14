#include "config_gpio.h"                  // Device header
#include "interrupt.h"
#include "delay.h"

int main(){
	GPIO_Config();
	Btn_Config();
	Interrupt_Config();
	while(1){
		if(status){
			Delay_ms(5);
			GPIOA -> ODR ^= 1;
			status = 0;
		}
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
		Delay_ms(500);
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		Delay_ms(500);
	}
}

