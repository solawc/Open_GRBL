#ifndef __hal_f429_system_h
#define __hal_f429_system_h

#include "stm32g0xx_hal.h"

#ifdef STM32G0B0xx
void hal_g0b0_system_init(void);
void Error_Handler(void);
void hal_g0b0_clk_init(void);
#endif

#endif
