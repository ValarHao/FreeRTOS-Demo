#ifndef __SYS_H
#define __SYS_H

/*------------------------------*
*  macros for configurations    *
*-------------------------------*/
#define   DEBUG
#define   FreeRTOS

/*------------------------------*
*  include head files           *
*-------------------------------*/
//#include "stm8s.h"
#include "stm32f10x.h"

/*------------------------------*
*  macros for others            *
*-------------------------------*/
#ifdef __STM8S_H
 
 #define   SYSCLK   16

 #define   BIT_ADDR(addr, bitnum)   (*((volatile BYTE_BITS *)addr)).bit##bitnum

 #define   GPIOA_ODR_ADDR   GPIOA_BaseAddress
 #define   GPIOB_ODR_ADDR   GPIOB_BaseAddress
 #define   GPIOC_ODR_ADDR   GPIOC_BaseAddress
 #define   GPIOD_ODR_ADDR   GPIOD_BaseAddress

 #define   GPIOA_IDR_ADDR   GPIOA_BaseAddress + 1
 #define   GPIOB_IDR_ADDR   GPIOB_BaseAddress + 1
 #define   GPIOC_IDR_ADDR   GPIOC_BaseAddress + 1
 #define   GPIOD_IDR_ADDR   GPIOD_BaseAddress + 1

 #define   PAout(n)   BIT_ADDR(GPIOA_ODR_ADDR, n)
 #define   PAin(n)    BIT_ADDR(GPIOA_IDR_ADDR, n)
 #define   PBout(n)   BIT_ADDR(GPIOB_ODR_ADDR, n)
 #define   PBin(n)    BIT_ADDR(GPIOB_IDR_ADDR, n)
 #define   PCout(n)   BIT_ADDR(GPIOC_ODR_ADDR, n)
 #define   PCin(n)    BIT_ADDR(GPIOC_IDR_ADDR, n)
 #define   PDout(n)   BIT_ADDR(GPIOD_ODR_ADDR, n)
 #define   PDin(n)    BIT_ADDR(GPIOD_IDR_ADDR, n)

#endif

#ifdef __STM32F10x_H
 
 #define   SYSCLK   72
 
 #define   BITBAND(addr, bitnum)    ((addr&0xF0000000)+0x2000000+((addr&0xFFFFF)<<5)+(bitnum<<2)) 
 #define   MEM_ADDR(addr)           *((volatile unsigned long *)(addr)) 
 #define   BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

 #define   GPIOA_ODR_Addr   (GPIOA_BASE + 12)  // 0x4001080C 
 #define   GPIOB_ODR_Addr   (GPIOB_BASE + 12)  // 0x40010C0C 
 #define   GPIOC_ODR_Addr   (GPIOC_BASE + 12)  // 0x4001100C 
 #define   GPIOD_ODR_Addr   (GPIOD_BASE + 12)  // 0x4001140C 
 #define   GPIOE_ODR_Addr   (GPIOE_BASE + 12)  // 0x4001180C 
 #define   GPIOF_ODR_Addr   (GPIOF_BASE + 12)  // 0x40011A0C    
 #define   GPIOG_ODR_Addr   (GPIOG_BASE + 12)  // 0x40011E0C    
 #define   GPIOA_IDR_Addr   (GPIOA_BASE + 8)   // 0x40010808 
 #define   GPIOB_IDR_Addr   (GPIOB_BASE + 8)   // 0x40010C08 
 #define   GPIOC_IDR_Addr   (GPIOC_BASE + 8)   // 0x40011008 
 #define   GPIOD_IDR_Addr   (GPIOD_BASE + 8)   // 0x40011408 
 #define   GPIOE_IDR_Addr   (GPIOE_BASE + 8)   // 0x40011808 
 #define   GPIOF_IDR_Addr   (GPIOF_BASE + 8)   // 0x40011A08 
 #define   GPIOG_IDR_Addr   (GPIOG_BASE + 8)   // 0x40011E08 

 #define   PAout(n)   BIT_ADDR(GPIOA_ODR_Addr, n)
 #define   PAin(n)    BIT_ADDR(GPIOA_IDR_Addr, n)
 #define   PBout(n)   BIT_ADDR(GPIOB_ODR_Addr, n)
 #define   PBin(n)    BIT_ADDR(GPIOB_IDR_Addr, n)
 #define   PCout(n)   BIT_ADDR(GPIOC_ODR_Addr, n)
 #define   PCin(n)    BIT_ADDR(GPIOC_IDR_Addr, n)
 #define   PDout(n)   BIT_ADDR(GPIOD_ODR_Addr, n)
 #define   PDin(n)    BIT_ADDR(GPIOD_IDR_Addr, n)
 #define   PEout(n)   BIT_ADDR(GPIOE_ODR_Addr, n)
 #define   PEin(n)    BIT_ADDR(GPIOE_IDR_Addr, n)
 #define   PFout(n)   BIT_ADDR(GPIOF_ODR_Addr, n)
 #define   PFin(n)    BIT_ADDR(GPIOF_IDR_Addr, n)
 #define   PGout(n)   BIT_ADDR(GPIOG_ODR_Addr, n)
 #define   PGin(n)    BIT_ADDR(GPIOG_IDR_Addr, n)
 
#endif

#ifdef __STM8S_H
 #define   Hx(val)     *((char *) &val)
 #define   xH(val)     *(((char *) &val) + 1)
 #define   Hxxx(val)   *((char *) &val)
 #define   xHxx(val)   *(((char *) &val) + 1)
 #define   xxHx(val)   *(((char *) &val) + 2)
 #define   xxxH(val)   *(((char *) &val) + 3)
#endif

#ifdef __STM32F10x_H
 #define   Hx(val)     *(((char *) &val) + 1)
 #define   xH(val)     *((char *) &val)
 #define   Hxxx(val)   *(((char *) &val) + 3)
 #define   xHxx(val)   *(((char *) &val) + 2)
 #define   xxHx(val)   *(((char *) &val) + 1)
 #define   xxxH(val)   *((char *) &val)
#endif

#ifdef __STM8S_H
 #define   LOAD_VAL   124   // 1MS
#endif

#ifdef __STM32F10x_H
 #define   TICK_1US   (SYSCLK / 8)

 #ifndef FreeRTOS
  #define   LOAD_VAL   TICK_1US * 1000
 #else
  #define   LOAD_VAL   TICK_1US * configTICK_RATE_HZ
 #endif
#endif

#ifdef __STM32F10x_H
typedef enum { FALSE = 0, TRUE = !FALSE } bool;
#endif

typedef enum { HIGH = 1, LOW = !HIGH } PinLevel;
typedef enum { WRITE = 0, READ = !WRITE } Operation;

#ifndef NULL
 #define   NULL     ((void *)0)
#endif

#define   BIT(i)   (1 << (i))

/*------------------------------*
*  macros for functions         *
*-------------------------------*/
#ifdef __STM8S_H
 #define   EnableInterrupt()    asm("rim")
 #define   DisableInterrupt()   asm("sim")
 #define   NOP()   asm("nop")
#endif

#ifdef __STM32F10x_H
 #define   EnableInterrupt()    __ASM volatile("cpsie i")
 #define   DisableInterrupt()   __ASM volatile("cpsid i")
 #define   NOP()   do { __nop(); __nop(); __nop(); } while (FALSE)
#endif

#ifndef FreeRTOS

#define   TASK_CHECK(taskName)   { \
	ptask = &taskName; \
	\
	if (ptask->enable == FALSE) \
		return; \
	\
	if (ptask->suspend == TRUE) \
	{ \
		if (sys.tick < ptask->tick) return; \
		ptask->suspend = FALSE; \
	} \
}

#define   TASK_WAIT(t)   { \
	ptask->tick = sys.tick + t; \
	ptask->suspend = TRUE; \
}

#define   TASK_ENABLE(taskName)    { \
	taskName.enable = TRUE; \
}

#define   TASK_DISABLE(taskName)   { \
	taskName.enable = FALSE; \
}

#endif

/*------------------------------*
*  type definitions             *
*-------------------------------*/
typedef void (*const Function)(void);

typedef struct
{
  #ifndef FreeRTOS
	u32 tick;
  #endif
	void (*const Init)(void);
	void (*const DelayUs)(u16);
  #ifndef FreeRTOS
	void (*const DelayMs)(u32);
  #endif
} Sys;

#ifndef FreeRTOS
typedef struct
{
	bool enable;
	bool suspend;
	u32 tick;	
	void (*const Process)(void);
} Task;
#endif

#ifdef __STM8S_H
typedef struct
{
	u8 bit0: 1;
	u8 bit1: 1;
	u8 bit2: 1;
	u8 bit3: 1;
	u8 bit4: 1;
	u8 bit5: 1;
	u8 bit6: 1;
	u8 bit7: 1;
} BYTE_BITS;
#endif

/*------------------------------*
*  public variables             *
*-------------------------------*/
extern Sys sys;

#ifndef FreeRTOS
 extern Task *ptask;
#endif

/*------------------------------*
*  public functions prototypes  *
*-------------------------------*/
#ifdef __STM8S_H
 extern void SetSoftwarePriority(u8 vector, u8 level);
#endif

/*------------------------------*
*  FreeRTOS head files          *
*-------------------------------*/
#ifdef FreeRTOS
 #include "FreeRTOS.h"
 #include "task.h"
 #include "queue.h"
 #include "croutine.h"
#endif

#endif
