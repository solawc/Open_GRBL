/*
 bsp_it.c

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/


#include "bsp_it.h"

/****************************************************************************
 * This is the timer interrupt callback function
 ***************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
#if defined(USE_FREERTOS_RTOS)
  uint32_t ulReturn;
	ulReturn = taskENTER_CRITICAL_FROM_ISR();
#endif

  if(htim == &STEP_RESET_TIMER) { 
    reset_timer_irq_handler();
  }
  else if(htim == &STEP_SET_TIMER)  {
    set_timer_irq_handler();
  }

#if defined(USE_FREERTOS_RTOS)
  taskEXIT_CRITICAL_FROM_ISR( ulReturn );
#endif
}


void SysTick_Handler(void)
{
  HAL_IncTick();

  w25qxxTestHandler();

#if defined(USE_FREERTOS_RTOS)

#if (INCLUDE_xTaskGetSchedulerState == 1 )
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
#endif /* INCLUDE_xTaskGetSchedulerState */
    xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  }
#endif /* INCLUDE_xTaskGetSchedulerState */

#endif
}
