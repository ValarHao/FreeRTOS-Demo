/****************************************************                                                                                         
* Microcontroller: STM8S103F3 & STM32F103RBT6                           
* Revision: 1.0  
* Description: System interface
* Author: ValarHao
*****************************************************
* Note:
* 2017.07.21 Build sys.h and sys.c
****************************************************/
#include "sys.h"

#ifndef FreeRTOS
 Task *ptask;
#endif

static void InitSysTick(void);
static void DelayUs(u16 nus);

#ifndef FreeRTOS
 static void DelayMs(u32 nms);
#endif

#ifndef FreeRTOS
 Sys sys = { 0, InitSysTick, DelayUs, DelayMs };
#else
 Sys sys = { InitSysTick, DelayUs };
#endif

#ifdef __STM8S_H
 volatile u8 facUs;
#endif

static void InitSysTick(void)
{
  #ifdef __STM8S_H
	SetSoftwarePriority(ITC_IRQ_TIM4_OVF, ITC_PRIORITYLEVEL_3);   // Software priority level 3
	TIM4_TimeBaseInit(TIM4_PRESCALER_128, LOAD_VAL);   // 128Prescaler, 124==>1ms tick
	TIM4_ClearFlag(TIM4_FLAG_UPDATE);   // Clear TIM4 update flag
	TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);   // Enable update interrupt  
	TIM4_Cmd(ENABLE);   // Enable TIM4

	// Initialize delay variable 
   #if SYSCLK > 16
	facUs = (16 - 4) / 4;
   #elif SYSCLK > 4
	facUs = (SYSCLK - 4) / 4;
   #else
	facUs = 1;
   #endif
  #endif

  #ifdef __STM32F10x_H
	SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;   // External divider 8
	SysTick->LOAD  = LOAD_VAL;
	SysTick->VAL   = 0x000000;   // Clear counter
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;   // Enable SYSTICK interrupt
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   // Enable SYSTICK

   #ifndef FreeRTOS
	sys.tick = 0;
   #endif
  #endif
}

static void DelayUs(u16 nus)
{
  #ifdef __STM8S_H
	DisableInterrupt();

	__asm(
	"PUSH A          \n"
	"DELAY_XUS:      \n"
	"LD A,facUs      \n"
	"DELAY_US_1:     \n"
	"NOP             \n"
	"DEC A           \n"
	"JRNE DELAY_US_1 \n"
	"NOP             \n"
	"DECW X          \n"
	"JRNE DELAY_XUS  \n"
	"POP A           \n"
	);

	EnableInterrupt();
  #endif

  #ifdef __STM32F10x_H
	u32 lastVal, nusVal, nowVal, usCnt = 0;

	nusVal = (u32) nus * TICK_1US;

   #ifndef FreeRTOS	
	DisableInterrupt();
   #else
    taskENTER_CRITICAL();
   #endif
	
	lastVal = SysTick->VAL;
	
	while (TRUE)
	{
		nowVal = SysTick->VAL;
		
		if (nowVal != lastVal)
		{
			if (nowVal < lastVal)
				usCnt += lastVal - nowVal;
			else
				usCnt += LOAD_VAL - nowVal + lastVal;
				
			lastVal = nowVal;
				
			if (usCnt >= nusVal)
				break;
		}
	}
	
   #ifndef FreeRTOS
	EnableInterrupt();
   #else
    taskEXIT_CRITICAL();
   #endif
  #endif
}

#ifndef FreeRTOS
static void DelayMs(u32 nms)
{
	u8 t;
	
  #ifdef __STM8S_H
	if (nms > 65)
	{
		t = nms / 65;
		while (t--) DelayUs(65000);
		nms %= 65;
	}
	
	DelayUs(nms * 1000);
  #endif

  #ifdef __STM32F10x_H
	for (t=0; t<nms; t++)
		DelayUs(1000);
  #endif
}
#endif

#ifdef __STM8S_H
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, ITC_IRQ_TIM4_OVF)
{
	TIM4->SR1 &= ~BIT(0);
	sys.tick++;
}
#endif

#if defined (__STM32F10x_H) && !defined (FreeRTOS)
void SysTick_Handler(void)
{
	sys.tick++;
}
#endif

#ifdef __STM8S_H
void SetSoftwarePriority(u8 vector, u8 level)
{
	u8 mask = 0;
	u8 newPriority = 0;
	
	mask = (u8)(~(u8)(0x03U << ((vector % 4U) * 2U)));
	
	newPriority = (u8)((level) << ((vector % 4U) * 2U));
	
	switch (vector)
	{
		case ITC_IRQ_TLI:
		case ITC_IRQ_AWU:
		case ITC_IRQ_CLK:
		case ITC_IRQ_PORTA:	
			ITC->ISPR1 &= mask;
			ITC->ISPR1 |= newPriority;
			break;
			
		case ITC_IRQ_PORTB:
		case ITC_IRQ_PORTC:
		case ITC_IRQ_PORTD:
		case ITC_IRQ_PORTE:
			ITC->ISPR2 &= mask;
			ITC->ISPR2 |= newPriority;
			break;
			
		case ITC_IRQ_SPI:
		case ITC_IRQ_TIM1_OVF:
			ITC->ISPR3 &= mask;
			ITC->ISPR3 |= newPriority;
			break;
			
		case ITC_IRQ_TIM1_CAPCOM:
		case ITC_IRQ_TIM2_OVF:
		case ITC_IRQ_TIM2_CAPCOM:
		case ITC_IRQ_TIM3_OVF:
			ITC->ISPR4 &= mask;
			ITC->ISPR4 |= newPriority;
			break;
			
		case ITC_IRQ_TIM3_CAPCOM:
		case ITC_IRQ_UART1_TX:
		case ITC_IRQ_UART1_RX:
		case ITC_IRQ_I2C:
			ITC->ISPR5 &= mask;
			ITC->ISPR5 |= newPriority;
			break;
			
		case ITC_IRQ_ADC1:
		case ITC_IRQ_TIM4_OVF:
			ITC->ISPR6 &= mask;
			ITC->ISPR6 |= newPriority;
			break;
			
		case ITC_IRQ_EEPROM_EEC:
			ITC->ISPR7 &= mask;
			ITC->ISPR7 |= newPriority;
			break;
			
		default:
			break;
	}
}
#endif
