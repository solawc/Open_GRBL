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
    htim_set.Init.Prescaler = 1;
    htim_set.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim_set.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&htim_set);

    HAL_NVIC_SetPriority(SET_TIM_IRQn, 0, 1);       // 使定时器中断的优先级保持最高
    HAL_NVIC_DisableIRQ(SET_TIM_IRQn);
    HAL_TIM_Base_Start_IT(&htim_set);
}

void hal_reset_timer_init(void) {

    RESET_TIM_CLK_ENABLED()
    htim_reset.Instance = SETP_RESET_TIM;
    htim_reset.Init.Period = 32-1;     
    htim_reset.Init.Prescaler = 1; 
    htim_reset.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim_reset.Init.CounterMode = TIM_COUNTERMODE_UP;
    HAL_TIM_Base_Init(&htim_reset);

    HAL_NVIC_SetPriority(RESET_TIM_IRQn, 0, 1);
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
    __HAL_TIM_SET_AUTORELOAD(htim, reload);
}
 
void hal_set_tim_cnt(TIM_HandleTypeDef *htim, uint32_t cnt) {
    __HAL_TIM_SET_COUNTER(htim, cnt);
}

void hal_tim_generateEvent_update(TIM_HandleTypeDef *htim) {
    HAL_TIM_GenerateEvent(htim, TIM_EVENTSOURCE_UPDATE);
}

void hal_tim_clear_flag_update(TIM_HandleTypeDef *htim) {
    __HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);
}

void hal_reset_timer_irq_enable(void) {
    HAL_NVIC_EnableIRQ(RESET_TIM_IRQn);
}

void hal_reset_timer_irq_disable(void) {
    HAL_NVIC_DisableIRQ(RESET_TIM_IRQn);
}

void STEP_RESET_HANDLER(void) {
    HAL_TIM_IRQHandler(&STEP_RESET_TIMER);
}

void STEP_SET_HANDLER(void) {
    HAL_TIM_IRQHandler(&STEP_SET_TIMER);
}

/*******************PWM SET***************************/

static void laser_pin_config() {

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_TIM4_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = LASER_PIN_AF;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void hal_pwm_init() {

    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    laser_pin_config();

    htim_laser.Instance = LASER_TIM;
    htim_laser.Init.Prescaler = 64-1;       // psc
    htim_laser.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim_laser.Init.Period = 1000-1;            // arr
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
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_OC_ConfigChannel(&htim_laser, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
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
    HAL_TIM_PWM_Start(&htim_laser, TIM_CHANNEL_2);
}

void hal_pwm_set(uint32_t duty) {

    // htim_laser.Instance->CCR2 = duty;
    __HAL_TIM_SetCompare(&htim_laser, TIM_CHANNEL_2, duty);
}

uint32_t hal_pwm_ccr_get(void) {
    
    return __HAL_TIM_GetCompare(&htim_laser, TIM_CHANNEL_2);
}


