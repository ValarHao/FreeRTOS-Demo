#ifndef __GLOBAL_H
#define __GLOBAL_H	 

/*------------------------------*
*  include head files           *
*-------------------------------*/
#include "sys.h"

/*------------------------------*
*  macros for task priority     *
*-------------------------------*/
#define   START_TASK_PRIO   1
#define   LED_TASK_PRIO     2

/*------------------------------*
*  macros for task stack size   *
*-------------------------------*/
#define   START_STK_SIZE   128
#define   LED_STK_SIZE      50

/*------------------------------*
*  variables for task handler   *
*-------------------------------*/
extern TaskHandle_t TaskStart_Handler;
extern TaskHandle_t TaskLed_Handler;

/*------------------------------*
*  public variables             *
*-------------------------------*/

/*------------------------------*
*  public functions prototypes  *
*-------------------------------*/
extern void InitGlobal(void);

#endif
