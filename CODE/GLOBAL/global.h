#ifndef __GLOBAL_H
#define __GLOBAL_H	 

/*------------------------------*
*  include head files           *
*-------------------------------*/
#include "sys.h"

/*------------------------------*
*  macros for task priority     *
*-------------------------------*/
#define   LED_TASK_PRIO    2

/*------------------------------*
*  macros for task stack size   *
*-------------------------------*/
#define   LED_STK_SIZE   128

/*------------------------------*
*  variables for task handler   *
*-------------------------------*/
extern TaskHandle_t TaskLed_Handler;

/*------------------------------*
*  public variables             *
*-------------------------------*/

/*------------------------------*
*  public functions prototypes  *
*-------------------------------*/
extern void InitGlobal(void);

#endif
