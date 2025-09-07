#include "stm32f10x.h"

int button_count = 0;
int last_state = 1; 


void Delay_ms(uint16_t _time){
	uint16_t i,j;
	for(i = 0; i < _time; i++){
		for(j = 0; j < 0x2aff; j++);
	}
}

void Config();

int main() {
	Config();
	while(1) {
		int button_state = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);
		if(button_state == 0 && last_state == 1) { 
			button_count++;
			if(button_count % 2 == 1) {
				GPIO_SetBits(GPIOA, GPIO_Pin_1);   
      } 
			else {
				GPIO_ResetBits(GPIOA, GPIO_Pin_1); 
      }
			Delay_ms(200); 
		}
    last_state = button_state;
	}
}


void Config(){
	GPIO_InitTypeDef gpio;
	GPIO_InitTypeDef btn;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  gpio.GPIO_Pin = GPIO_Pin_1;
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &gpio);
  btn.GPIO_Pin = GPIO_Pin_13;
  btn.GPIO_Mode = GPIO_Mode_IPU; 
  GPIO_Init(GPIOC, &btn);
}
    
	