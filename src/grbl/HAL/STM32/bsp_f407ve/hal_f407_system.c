
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