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

static void AppTaskCreate(void);

int main(void)
{
	__set_PRIMASK(1);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	sys.Init();

	AppTaskCreate();
	
	vTaskStartScheduler();

	while (TRUE);
}

static void AppTaskCreate(void)
{
    xTaskCreate((TaskFunction_t) TaskLed,
                (const char *)  "TaskLed",
                (u16)            LED_STK_SIZE,
                (void *)         NULL,
                (UBaseType_t)    LED_TASK_PRIO,
                (TaskHandle_t *) &TaskLed_Handler );
}
