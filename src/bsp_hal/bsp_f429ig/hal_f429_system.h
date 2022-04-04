#ifndef __hal_f429_system_h
#define __hal_f429_system_h

#ifdef STM32F429xx
#include "stm32f4xx_hal.h"
#include "core_cm4.h"

void hal_f429_system_init(void);
void Error_Handler(void);
void hal_f429_clk_init(void);
#endif

#endif
