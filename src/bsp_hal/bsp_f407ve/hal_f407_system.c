
#ifdef STM32F407xx
#include "hal_f407_system.h"
#include "../hal_tim.h"

/*
 * 1.set system clock 
 * 2.init system and clock
*/
void hal_f407_system_init(void) {





}


void hal_f407_clk_init(void) {



}

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

void systick_setting_init() {


}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#endif