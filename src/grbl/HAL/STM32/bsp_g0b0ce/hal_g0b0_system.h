#ifndef __hal_f429_system_h
#define __hal_f429_system_h

#include "stm32g0xx_hal.h"

#ifdef STM32G0B0xx

#define TIM_SET_PSC     10
#define TIM_SET_ARR     10

#define TIM_RESET_PSC   10
#define TIM_RESET_ARR   10

void hal_g0b0_system_init(void);
void Error_Handler(void);
void hal_g0b0_clk_init(void);
#endif

#endif
