#include "hal_tim.h"
#include "stepper.h"



/*  
 * Note: I use general timer by tim3 and tim4 on stm32h429,
 * also you can choose other timer as step count, the timer,
 * need handle with updata
*/
TIM_HandleTypeDef htim3;    // Configure Timer 1: Stepper Driver Interrupt
TIM_HandleTypeDef htim4;    // Configure Timer 0: Stepper Port Reset Interrupt

TIM_HandleTypeDef htim8;

void hal_set_timer_init(void) {

    __HAL_RCC_TIM3_CLK_ENABLE();

    htim3.Instance = TIM3; 
    htim3.Init.Period = 180; // 180 000 000/90 = 2000000Hz
    htim3.Init.Prescaler = 1;
    htim3.Init.ClockDivision = 0;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&htim3);

    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 2);
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
    HAL_TIM_Base_Start_IT(&htim3);
}

void hal_reset_timer_init(void) {

    __HAL_RCC_TIM4_CLK_ENABLE();
    htim4.Instance = TIM4;
    htim4.Init.Period = 100;// 90;  // 180 000 000/90 = 2000000Hz
    htim4.Init.Prescaler = 1;
    htim4.Init.ClockDivision = 0;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&htim4);

    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
    HAL_NVIC_DisableIRQ(TIM4_IRQn);
    HAL_TIM_Base_Start_IT(&htim4);
}

void hal_set_timer_irq_enable(void) {

    HAL_NVIC_EnableIRQ(TIM3_IRQn);
    
}

void hal_set_timer_irq_disable(void) {
    // HAL_NVIC_DisableIRQ(TIM3_IRQn);
    NVIC_DisableIRQ(TIM3_IRQn);
}

void hal_tim_set_reload(TIM_HandleTypeDef *htim, uint32_t reload) {
    WRITE_REG(htim->Instance->ARR, reload);
}
 

void hal_set_tim_cnt(TIM_HandleTypeDef *htim, uint32_t cnt) {
    WRITE_REG(htim->Instance->CNT, cnt);

}

void hal_tim_generateEvent_update(TIM_HandleTypeDef *htim) {
    SET_BIT(htim->Instance->EGR, TIM_EGR_UG);
}

void hal_tim_clear_flag_update(TIM_HandleTypeDef *htim) {
    WRITE_REG(htim->Instance->SR, ~(TIM_SR_UIF));
}

void hal_reset_timer_irq_enable(void) {
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
}

void hal_reset_timer_irq_disable(void) {
    HAL_NVIC_DisableIRQ(TIM4_IRQn);
}

void hal_set_tim_prescaler(uint32_t prescaler) {
    STEP_SET_TIMER.Init.Prescaler = prescaler;
}


void TIM4_IRQHandler(void) {
    HAL_TIM_IRQHandler(&STEP_RESET_TIMER);
}

void TIM3_IRQHandler(void) {
    HAL_TIM_IRQHandler(&STEP_SET_TIMER);
}


/*******************PWM SET***************************/

void hal_pwm_init() {

    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    htim8.Instance = TIM8;
    htim8.Init.Prescaler = 1000;
    htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim8.Init.Period = 90;
    htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim8.Init.RepetitionCounter = 0;
    htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_OC_Init(&htim8) != HAL_OK)
    {
    Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
    {
    Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 50;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_OC_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
    Error_Handler();
    }
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
    {
    Error_Handler();
    }
}


void hal_pwm_set(uint32_t duty) {


}


