#ifndef __sensor_h
#define __sensor_h

#include "stm32f10x.h"
#include "i2c.h"

#define BH1750_ADDR   0x46   // ADDR = GND ? 0x46, ADDR = VCC ? 0xB8
void BH1750_Init(void);
uint16_t BH1750_ReadLight(void); 
#endif
