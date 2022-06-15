#ifndef __hal_f407_system_h
#define __hal_f407_system_h

#ifdef STM32F407xx

#include "stm32f4xx_hal.h"

void hal_f407_system_init(void);
void Error_Handler(void);
void hal_f407_clk_init(void);

#endif // STM32F407xx

#endif
