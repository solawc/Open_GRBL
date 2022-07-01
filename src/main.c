#include "main.h"

int main() {

  grbl_hw_init();

  client_init();

#ifdef STM32G0B0xx
  // here must wait for some time, beacuse STM32G0B0CE have no XTAL
  HAL_Delay(100);  
#endif

  // report MCU info and you can check
  grbl_report_mcu_info();

#ifdef DEBUG_TEST
  while(1) {}
#endif

#if defined(USE_FREERTOS_RTOS)
  xTaskCreate(enter_grbl_task, "grbl task", 1024, NULL, 1, &grbl_task_handler);
#else 
  enter_grbl_task();
#endif

#if defined(USE_FREERTOS_RTOS)
  osKernelStart();
#endif
}

void _delay_ms(uint32_t tick) {
  
#if defined(USE_FREERTOS_RTOS)
  vTaskDelay(tick);
#else 
  uint32_t mililoop = SystemCoreClock / 1000;
	for (uint32_t i=0; i< mililoop; i++)
		__asm__ __volatile__("nop\n\t":::"memory");
  // HAL_Delay(tick);
#endif
}

void _delay_us(uint32_t tick) {
	__NOP();
}
