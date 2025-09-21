#include "i2c.h"
#include "timer.h"

void Config_I2C(){
//	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;
	 
	// Bat clock
	RCC -> APB2ENR |= 0x0008; // Bat clock cho GPIOB (bit 3)
	RCC -> APB1ENR |= (1 << 21); //Bat clock cho I2C1 (bit 21)
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	// Cau hình PB6, PB7 là Alternate Function output Open-Drain
	GPIOB -> CRL |= 0xFF000000;
	
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB, &GPIO_InitStruct);

	SDA_1;
	SCL_1;
//	
//	//Config Clock
//	I2C1 -> CR2 = 0x0024; // f = 36MHz (data 6 bit dau de cau hinh FREQ) 
//	// Config Clock control register, Cau hinh toc do xung clock SCL
//	I2C1 -> CCR |= 0x00b4; // CCR = (f APB1)/ (f SCL * 2); Do do neu f SCL = 100kHz -> CRR = 180 = 00B4 
//	I2C1 -> TRISE = 0x25;  // Cau hinh tgian suon len toi da, jup tan so SCL on dinh 
//	//TRISE = 37 = FREQ(36) + 1
//	
//	// I2C mode
//	I2C1->CR1 &= ~I2C_CR1_SMBUS;   // I2C mode
//	I2C1->CCR &= ~I2C_CCR_DUTY;    // duty cycle = 2
//	
//	// Own address (master mode, không quan trong) 
//	I2C1->OAR1 = (0x00 << 1);      
//	I2C1->OAR1 &= ~I2C_OAR1_ADDMODE; // ADD_Mode = 0 -> 7-bit slave address 
//	
//	I2C1 -> CR1 |= I2C_CR1_ACK; // va bat ACK (bit 10)
//	I2C1 -> CR1 |= I2C_CR1_PE; // PE = 1: Enable I2C (bit 1)

	// Cau hình I2C1
	I2C_InitStruct.I2C_ClockSpeed = 100000;      // Toc do truyen 100kHz
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;			 // Che do I2C
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2; // Thigh = Tlow
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;       // STM32 làm master, day la dia chi chinh khi stm lam slave nen ko quan trong
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;		 // Bat ACK: tin hieu xac nhan sau moi byte truyen
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; // Che do dia chi 7 bit 
	I2C_Init(I2C1, &I2C_InitStruct);

	//Enable I2C1
	I2C_Cmd(I2C1, ENABLE);
}

void I2C_Start(){
	SDA_1;
	SCL_1;
	Delay_us(4);	
	SDA_0;
	Delay_us(4);

}

void I2C_Stop(){
	SDA_0;
	SCL_1;
	Delay_us(4);
	SDA_1;
	Delay_us(4);	
}

void I2C_WriteByte(uint8_t address, uint8_t data){
	// Send START
  I2C_Start();

  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); // ktra co SB = 1 xac nhan start thanh cong
  I2C_Send7bitAddress(I2C1, address, I2C_Direction_Transmitter); // gui 7 bit dia chi va 1 bit ghi (W = 0)

  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); // Cho gui xong

  I2C_SendData(I2C1,data); // Gui du lieu cho I2C1
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)); // Cho gui xong du lieu, du lieu da duoc nap vao DR
	
	I2C_Stop();
}

////Gui nhieu byte
//void I2C_WriteMultiByte(const uint8_t* buff,  uint32_t nbyte, uint8_t address){
//	if(nbyte){
//		I2C_Start();
//		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

//		I2C_Send7bitAddress(I2C1, address, I2C_Direction_Transmitter);
//		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

//		I2C_SendData(I2C1,address);
//		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

//		I2C_SendData(I2C1, *buff++);
//		while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//		
//		while(nbyte--){
//			I2C_SendData(I2C1, *buff++);
//			while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//		}
//		I2C_Stop();
//	}
//}

//uint8_t I2C_ReadByte(uint8_t address){
//	uint8_t msb=0;
//  uint8_t lsb=0;
//	I2C_AcknowledgeConfig(I2C1,ENABLE);
//  I2C_Start();
//  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
//  I2C_Send7bitAddress(I2C1, address, I2C_Direction_Transmitter);
//  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
//	
//  I2C_SendData(I2C1,address);
//  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

//  I2C_GenerateSTART(I2C1,ENABLE);
//  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

//  I2C_Send7bitAddress(I2C1, address, I2C_Direction_Receiver);
//  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

//  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));	
//  lsb = I2C_ReceiveData(I2C1);

//  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
//  msb = I2C_ReceiveData(I2C1);

//  I2C_Stop();
//  I2C_AcknowledgeConfig(I2C1,DISABLE);

//  return (msb << 8) | lsb;	

//}