#include "timer.h"
#include "config_gpio.h"
#include "uart.h"
#include <string.h>

int main(){
    Tim_config();
    Led_config();
    Uart_init();
		Delay_ms(100);
    printf("xin chao!\r\n");
		Delay_ms(100);
    while(1){
			if(vri_Stt){
				if(strcmp(vrc_Res,"ON") == 0){ // so sanh ki tu nhap vao neu la on thi bat led 
					GPIO_ResetBits(GPIOC, GPIO_Pin_13); 
				}		 
				else if (strcmp(vrc_Res,"OFF")== 0){ //   neu la off thi tat led
					
					 GPIO_SetBits(GPIOC, GPIO_Pin_13);
				}
				vri_Stt =0; // reset bien trang thai ve 0 
			}
    }
}
