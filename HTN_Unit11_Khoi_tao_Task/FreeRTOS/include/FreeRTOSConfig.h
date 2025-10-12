#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "stm32f10x.h"

/*-----------------------------------------------------------
 * Basic Kernel Settings
 *-----------------------------------------------------------*/
#define configUSE_PREEMPTION                    1
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configCPU_CLOCK_HZ                      ( ( unsigned long ) 72000000 )
#define configTICK_RATE_HZ                      ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES                    5
#define configMINIMAL_STACK_SIZE                128
#define configTOTAL_HEAP_SIZE                   ( 5 * 1024 )
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 1

/*-----------------------------------------------------------
 * Memory Allocation
 *-----------------------------------------------------------*/
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configUSE_MALLOC_FAILED_HOOK            1

/*-----------------------------------------------------------
 * Software Timer (t?t vì chua dùng)
 *-----------------------------------------------------------*/
#define configUSE_TIMERS                        0

/*-----------------------------------------------------------
 * Mutex & Semaphore (t?t vì chua dùng)
 *-----------------------------------------------------------*/
#define configUSE_MUTEXES                       0
#define configUSE_COUNTING_SEMAPHORES           0
#define configUSE_RECURSIVE_MUTEXES             0

/*-----------------------------------------------------------
 * Hook function
 *-----------------------------------------------------------*/
#define configCHECK_FOR_STACK_OVERFLOW          0

/*-----------------------------------------------------------
 * Cortex-M3 Interrupt Priority
 *-----------------------------------------------------------*/
#define configPRIO_BITS                         4
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY        15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY   5
#define configKERNEL_INTERRUPT_PRIORITY  ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY  ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/*-----------------------------------------------------------
 * API functions to include
 *-----------------------------------------------------------*/
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_xTaskGetSchedulerState          1

/*-----------------------------------------------------------
 * Memory allocation failed hook
 *-----------------------------------------------------------*/
void vApplicationMallocFailedHook(void);

/*-----------------------------------------------------------
 * Interrupt handlers
 *----------------------------------------------------------*/
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
