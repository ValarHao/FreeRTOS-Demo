/****************************************************                                                                                         
* Microcontroller: STM32F103RBT6
* File: led.c                              
* Revision: 1.0  
* Description: LED API
* Author: ValarHao
* Date: 2017.8.26
****************************************************/
#include "led.h"

#define   LED_ON    LOW
#define   LED_OFF   HIGH

#define   LED_R   PAout(4)

static void InitLed(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	
	// LED_R
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	LED_R = LED_OFF;
}

void TaskLed(void *p_arg)
{
	InitLed();
	
	while (TRUE)
	{
		LED_R ^= 1;
		vTaskDelay(500);
	}
}
