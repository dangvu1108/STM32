#include "delay.h"
void Delay_ms(uint16_t time){
	uint16_t i, j;
	for(i = 0; i < time; i++){
		for(j = 0; j < 0x2aff; j++);
	}
}