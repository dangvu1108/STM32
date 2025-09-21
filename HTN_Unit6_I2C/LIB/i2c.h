#ifndef _i2c_h_
#define _i2c_h_

#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_gpio.h"

#define SDA_0 GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define SDA_1 GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define SCL_0 GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define SCL_1 GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define SDA_VAL GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)

void Config_I2C();
void I2C_Start();
void I2C_Stop();
void I2C_WriteByte(uint8_t address, uint8_t data);
void I2C_WriteMultiByte(const uint8_t* buff,  uint32_t nbyte, uint8_t address);
uint8_t I2C_ReadByte(uint8_t address);

#endif
