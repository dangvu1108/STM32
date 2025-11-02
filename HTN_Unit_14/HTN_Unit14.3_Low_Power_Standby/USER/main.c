#include "stm32f10x.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>

void RTC_Config(void);
void Set_Alarm(uint32_t seconds);
void delay_ms(uint16_t time);

int main(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
		Uart_Config();
    if (PWR_GetFlagStatus(PWR_FLAG_SB) == SET)
    {
        // D?y t? Standby
        PWR_ClearFlag(PWR_FLAG_SB);
        RCC_ClearFlag();
        Uart_SendStr("Da thuc day tu Standby!\r\n");
			
				// Sau khi th?c d?y, thi?t l?p l?i Alarm và ng? ti?p
        RTC_Config();          // d?m b?o RTC còn ho?t d?ng
        Set_Alarm(5);
        Uart_SendStr("Ngu lai sau 5 giay...\r\n\r\n");
        delay_ms(4000);
        PWR_ClearFlag(PWR_FLAG_WU);
        PWR_EnterSTANDBYMode();   // quay l?i Standby
    }
    else
    {
        Uart_SendStr("Khoi dong lan dau\r\n");
        RTC_Config();
    }

    Uart_SendStr("Thiet lap bao thuc 5 giay...\r\n");
    Set_Alarm(5);

    Uart_SendStr("Chuan bi vao Standby...\r\n\r\n");
    delay_ms(100);

    // Xóa c? Wakeup
    PWR_ClearFlag(PWR_FLAG_WU);

    // Vào ch? d? Standby
    PWR_EnterSTANDBYMode();

    while (1) {}
}

void RTC_Config(void)
{
EXTI_InitTypeDef EXTI_InitStructure;
    PWR_BackupAccessCmd(ENABLE);
    RCC_LSICmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForSynchro();

    RTC_SetPrescaler(39999);
    RTC_WaitForLastTask();
    RTC_SetCounter(0);
    RTC_WaitForLastTask();

    // Enable ng?t báo th?c RTC
    RTC_ITConfig(RTC_IT_ALR, ENABLE);
    RTC_WaitForLastTask();

    // --- QUAN TR?NG: C?u hình EXTI line 17 ---
    EXTI_ClearITPendingBit(EXTI_Line17);
    
    EXTI_InitStructure.EXTI_Line = EXTI_Line17;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

void Set_Alarm(uint32_t seconds)
{
    uint32_t currentTime = RTC_GetCounter();
    RTC_SetAlarm(currentTime + seconds);
    RTC_WaitForLastTask();
}

void delay_ms(uint16_t time)
{
    uint16_t i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 0x2aff; j++);
}
