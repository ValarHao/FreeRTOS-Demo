/****************************************************                                                                                         
* Microcontroller: STM32F103RBT6
* File: main.c                              
* Revision: 1.0  
* Description: FreeRTOS-Demo
* Author: ValarHao
* Date: 2017.8.26
****************************************************/
#include "sys.h"
#include "global.h"
#include "led.h"

static void TaskStart(void *pvParameters);

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	sys.Init();
	
	xTaskCreate((TaskFunction_t) TaskStart,
	            (const char *)  "TaskStart",
	            (u16)            START_STK_SIZE,
	            (void *)         NULL,
	            (UBaseType_t)    START_TASK_PRIO,
	            (TaskHandle_t *) &TaskStart_Handler );
	
	vTaskStartScheduler();
}

static void TaskStart(void *pvParameters)
{
	taskENTER_CRITICAL();
	
	xTaskCreate((TaskFunction_t) TaskLed,
	            (const char *)  "TaskLed",
	            (u16)            LED_STK_SIZE,
	            (void *)         NULL,
	            (UBaseType_t)    LED_TASK_PRIO,
				(TaskHandle_t *) &TaskLed_Handler );
	
	vTaskDelete(TaskStart_Handler);
	
	taskEXIT_CRITICAL();
}
