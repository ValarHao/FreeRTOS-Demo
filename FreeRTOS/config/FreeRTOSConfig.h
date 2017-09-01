/*
    FreeRTOS V8.2.3 - Copyright (C) 2015 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 *                FreeRTOS基础配置配置选项
 *----------------------------------------------------------*/
#define configUSE_PREEMPTION       1                                /* 启用抢占式内核 */
#define configUSE_IDLE_HOOK        0                                /* 启用空闲钩子 */
#define configUSE_TICK_HOOK        0                                /* 启用时间片钩子 */
#define configCPU_CLOCK_HZ         ( ( unsigned long ) 72000000 )   /* CPU 时钟频率 */
#define configTICK_RATE_HZ         ( ( TickType_t ) 1000 )          /* 时基 */
#define configMAX_PRIORITIES       ( 5 )                            /* 可使用的最大优先级 */
#define configMINIMAL_STACK_SIZE   ( ( unsigned short ) 128 )       /* 空闲任务堆栈大小 */
#define configTOTAL_HEAP_SIZE      ( ( size_t ) ( 17 * 1024 ) )     /* 系统总的堆大小 */
#define configMAX_TASK_NAME_LEN    ( 16 )                           /* 任务名字字符串长度 */
#define configUSE_TRACE_FACILITY   0                                /* 启用可视化跟踪调试 */
#define configUSE_16_BIT_TICKS     0                                /* 系统节拍计数器变量数据类型 */
#define configIDLE_SHOULD_YIELD    0                                /* 空闲任务放弃CPU使用权给其他同优先级的用户任务 */

/*-----------------------------------------------------------
 *                FreeRTOS与协程有关的配置选项
 *----------------------------------------------------------*/
#define configUSE_CO_ROUTINES             0                         /* 启用协程 */
#define configMAX_CO_ROUTINE_PRIORITIES   ( 2 )                     /* 协程的有效优先级数目 */

/*-----------------------------------------------------------
 *                FreeRTOS可选函数配置选项
 *----------------------------------------------------------*/
#define INCLUDE_vTaskPrioritySet        1
#define INCLUDE_uxTaskPriorityGet       1
#define INCLUDE_vTaskDelete             1
#define INCLUDE_vTaskCleanUpResources   0
#define INCLUDE_vTaskSuspend            1
#define INCLUDE_vTaskDelayUntil         1
#define INCLUDE_vTaskDelay              1

/*-----------------------------------------------------------
 *                FreeRTOS与中断有关的配置选项
 *----------------------------------------------------------*/
#ifdef __NVIC_PRIO_BITS
	#define configPRIO_BITS   __NVIC_PRIO_BITS
#else
	#define configPRIO_BITS   4
#endif

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY        15           /* 中断最低优先级 */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY   1            /* 系统可管理的最高中断优先级 */
#define configKERNEL_INTERRUPT_PRIORITY        ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY   ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/*-----------------------------------------------------------
 *                FreeRTOS与中断服务函数有关的配置选项
 *----------------------------------------------------------*/
#define vPortSVCHandler       SVC_Handler
#define xPortPendSVHandler    PendSV_Handler
#define xPortSysTickHandler   SysTick_Handler

/*-----------------------------------------------------------
 *                FreeRTOS与断言有关的配置选项
 *----------------------------------------------------------*/
#define configASSERT( x )   if ( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); for( ;; ); }	

#endif /* FREERTOS_CONFIG_H */
