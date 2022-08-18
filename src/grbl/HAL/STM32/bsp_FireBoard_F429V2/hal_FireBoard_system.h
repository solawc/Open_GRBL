#ifndef __hal_FireBoard_system_h
#define __hal_FireBoard_system_h

#ifdef STM32F429xx
#include "stm32f4xx_hal.h"
#include "core_cm4.h"

#define TIM_SET_PSC     10
#define TIM_SET_ARR     10

#define TIM_RESET_PSC   10
#define TIM_RESET_ARR   10


void hal_f429_system_init(void);
void Error_Handler(void);
void hal_f429_clk_init(void);
#endif // STM32F429xx

#endif
