#ifndef __grbl_main_h
#define __grbl_main_h

#include "../main.h"

#if defined(USE_FREERTOS_RTOS)
  extern TaskHandle_t grbl_task_handler;
#endif


#if defined(USE_FREERTOS_RTOS)
void enter_grbl_task(void *parg);
void grblTaskInit(void);
#else
void enter_grbl_task(void);
#endif


#endif
