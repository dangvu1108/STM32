#include "sensor.h"
#include "i2c.h"
#include "timer.h"

void BH1750_Init(void) {
    Delay_ms(10);
    I2C_WriteByte(BH1750_ADDR, 0x01); // Power on
    Delay_ms(10);
    I2C_WriteByte(BH1750_ADDR, 0x10); // Cau hinh do lien tuc BH1750
    Delay_ms(200); 
}

uint16_t BH1750_ReadLight(void) {
    uint16_t value = 0;
		uint8_t lsb;
		uint8_t msb;
    I2C_Start();
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); // ktra co SB = 1 xac nhan start thanh cong

    I2C_Send7bitAddress(I2C1, BH1750_ADDR, I2C_Direction_Receiver); // gui 7 bit dia chi BH1750 va 1 bit 0x01 la Read
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)); // Cho gui xong, xac nhan vao che do Read

		//Doc du lieu 2 byte
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    msb = I2C_ReceiveData(I2C1); // bit cao

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    lsb = I2C_ReceiveData(I2C1);

    I2C_AcknowledgeConfig(I2C1, DISABLE);
    I2C_Stop();
    I2C_AcknowledgeConfig(I2C1, ENABLE);

    value = ((msb << 8) | lsb) / 1.2; // chuyen ve Lux
    return value;
}
