#include "hal_tim.h"

/*  
 * Note: I use general timer by tim3 and tim4 on stm32h429,
 * also you can choose other timer as step count, the timer,
 * need handle with updata
*/
TIM_HandleTypeDef htim3;    // Configure Timer 1: Stepper Driver Interrupt
TIM_HandleTypeDef htim4;    // Configure Timer 0: Stepper Port Reset Interrupt

void hal_tim_step_init(void) {

    __HAL_RCC_TIM3_CLK_ENABLE();

    htim3.Instance = TIM3; 
    htim3.Init.Period = 1000;
    htim3.Init.Prescaler = 1;
    htim3.Init.ClockDivision = 0;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&htim3);

    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
    HAL_TIM_Base_Start_IT(&htim3);
}


void hal_tim_move_step_init(void) {

    __HAL_RCC_TIM4_CLK_ENABLE();

    htim4.Instance = TIM4;
    htim4.Init.Period = 1000;
    htim4.Init.Prescaler = 1;
    htim4.Init.ClockDivision = 0;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;

    HAL_TIM_Base_Init(&htim4);

    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 2);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
    HAL_TIM_Base_Start_IT(&htim4);
}


void hal_tim_step_irq_enable(void) {
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void hal_tim_step_irq_disable(void) {
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
}


void hal_tim_move_step_irq_enable(void) {
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
}

void hal_tim_move_step_irq_disable(void) {
    HAL_NVIC_DisableIRQ(TIM4_IRQn);
}

void hal_set_tim_prescaler(uint32_t prescaler) {

    htim4.Init.Prescaler = prescaler;
}

void hal_tim_move_step_arr(uint32_t num) {

    htim3.Instance->ARR = num;
}

void TIM3_IRQHandler(void) {

    if((htim3.Instance->SR & 0x0001 ) != 0) {
        htim3.Instance->SR &= ~(1<<0);      // clear UIF flag
		htim3.Instance->CNT = 0;
        hal_tim_step_irq_disable();
    }
}

