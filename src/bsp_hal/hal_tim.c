#include "hal_tim.h"
// #include "stepper.h"

/*  
 * Note: I use general timer by tim3 and tim4 on stm32h429,
 * also you can choose other timer as step count, the timer,
 * need handle with updata
*/

TIM_HandleTypeDef htim_set;    // Configure Timer 6: Stepper Driver Interrupt
TIM_HandleTypeDef htim_reset;    // Configure Timer 7: Stepper Port Reset Interrupt
TIM_HandleTypeDef htim_laser;    // Configure Timer 7: Stepper Port Reset Interrupt

void hal_set_timer_init(void) {

    SET_TIM_CLK_ENABLED();   

    htim_set.Instance = SETP_SET_TIM; 
    htim_set.Init.Period = 32-1;     
    htim_set.Init.Prescaler = 1-1;
    htim_set.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim_set.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&htim_set);

    HAL_NVIC_SetPriority(SET_TIM_IRQn, 0, 1);
    HAL_NVIC_DisableIRQ(SET_TIM_IRQn);
    HAL_TIM_Base_Start_IT(&htim_set);
}

void hal_reset_timer_init(void) {

    RESET_TIM_CLK_ENABLED()
    htim_reset.Instance = SETP_RESET_TIM;
    htim_reset.Init.Period = 32-1;     
<<<<<<< HEAD
    htim_reset.Init.Prescaler = 1-1;     
=======
    htim_reset.Init.Prescaler = 1-1; 
>>>>>>> fcbe05e009d74228b129c23a042bed9d9cb3b5e4
    htim_reset.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim_reset.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&htim_reset);

    HAL_NVIC_SetPriority(RESET_TIM_IRQn, 0, 2);
    HAL_NVIC_DisableIRQ(RESET_TIM_IRQn);
    HAL_TIM_Base_Start_IT(&htim_reset);
}

void hal_set_timer_irq_enable(void) {
    HAL_NVIC_EnableIRQ(SET_TIM_IRQn);
}

void hal_set_timer_irq_disable(void) {
    NVIC_DisableIRQ(SET_TIM_IRQn);
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
    HAL_NVIC_EnableIRQ(RESET_TIM_IRQn);
}

void hal_reset_timer_irq_disable(void) {
    HAL_NVIC_DisableIRQ(RESET_TIM_IRQn);
}

void hal_set_tim_prescaler(uint32_t prescaler) {
    STEP_SET_TIMER.Init.Prescaler = prescaler;
}


void STEP_RESET_HANDLER(void) {
    HAL_TIM_IRQHandler(&STEP_RESET_TIMER);
}

void STEP_SET_HANDLER(void) {
    HAL_TIM_IRQHandler(&STEP_SET_TIMER);
}


/*******************PWM SET***************************/
void hal_pwm_init() {

    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    htim_laser.Instance = LASER_TIM;
    htim_laser.Init.Prescaler = 1000;
    htim_laser.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim_laser.Init.Period = 32;
    htim_laser.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim_laser.Init.RepetitionCounter = 0;
    htim_laser.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_OC_Init(&htim_laser) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim_laser, &sMasterConfig) != HAL_OK)
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
    if (HAL_TIM_OC_ConfigChannel(&htim_laser, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
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
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim_laser, &sBreakDeadTimeConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void hal_pwm_set(uint32_t duty) {


}


