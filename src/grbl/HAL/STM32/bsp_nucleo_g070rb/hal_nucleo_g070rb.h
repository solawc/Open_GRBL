#ifndef __hal_nucleo_g070rb_h
#define __hal_nucleo_g070rb_h

#ifdef STM32G070xx
#include "stm32g0xx_hal.h"
#include "core_cm0plus.h"

#define TIM_SET_PSC     10
#define TIM_SET_ARR     10

#define TIM_RESET_PSC   10
#define TIM_RESET_ARR   10

void hal_nucleo_g070rb_system_init(void);
void Error_Handler(void);
void hal_nucleo_g070rb_clk_init(void);

#endif

#endif