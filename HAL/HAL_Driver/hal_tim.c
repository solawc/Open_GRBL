#include "hal_tim.h"
#include "stepper.h"


/*  
 * Note: I use general timer by tim3 and tim4 on stm32h429,
 * also you can choose other timer as step count, the timer,
 * need handle with updata
*/
TIM_HandleTypeDef htim_set;    // Configure Timer 6: Stepper Driver Interrupt
TIM_HandleTypeDef htim_reset;    // Configure Timer 7: Stepper Port Reset Interrupt
TIM_HandleTypeDef htim_laser;    // Configure Timer 7: Stepper Port Reset Interrupt

void hal_set_timer_init(void) {

    TIM_MasterConfigTypeDef sMasterConfig = {0};

     __HAL_RCC_TIM6_CLK_ENABLE();

    htim_set.Instance = TIM6;
    htim_set.Init.Prescaler = 32+1;
    htim_set.Init.Period = 1; // 64MHz /32 = 2M 
    htim_set.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim_set.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim_set) != HAL_OK)
    {

    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim_set, &sMasterConfig) != HAL_OK)
    {

    }
    HAL_NVIC_SetPriority(TIM6_IRQn, 0, 2);
    HAL_NVIC_DisableIRQ(TIM6_IRQn);
    HAL_TIM_Base_Start_IT(&htim_set);
}

void hal_reset_timer_init(void) {

    TIM_MasterConfigTypeDef sMasterConfig = {0};

    __HAL_RCC_TIM7_CLK_ENABLE();

    htim_reset.Instance = TIM7;
    htim_reset.Init.Prescaler = 32+1;
    htim_reset.Init.Period = 1;    // 64MHz /32 = 2M
    htim_reset.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim_reset.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if(HAL_TIM_Base_Init(&htim_reset) != HAL_OK) {
        while(1);
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim_reset, &sMasterConfig) != HAL_OK)
    {
        while(1);
    }

    HAL_NVIC_SetPriority(TIM7_IRQn, 0, 1);
    HAL_NVIC_DisableIRQ(TIM7_IRQn);
    HAL_TIM_Base_Start_IT(&htim_reset);
}


void hal_laser_port_init(void) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_TIM4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void hal_laser_timer_init(void) {

    __HAL_RCC_TIM4_CLK_ENABLE();

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim_laser.Instance = TIM4;
    htim_laser.Init.Prescaler = 64;                             // config 1KHz
    htim_laser.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim_laser.Init.Period = 1000;
    htim_laser.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    if (HAL_TIM_Base_Init(&htim_laser) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim_laser, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim_laser) != HAL_OK)
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
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim_laser, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_TIM_PWM_Start(&htim_laser, TIM_CHANNEL_2);

    hal_laser_port_init();
}

/*
    0-255 -----> 0-1000
*/
void hal_pwm_set(uint32_t duty) {

    if(duty > 1000) duty = 1000;
    
    htim_laser.Instance->CCR2 = duty;
}

uint32_t hal_pwm_value(void) {

    return htim_laser.Instance->CCR2;
}


void hal_set_timer_irq_enable(void) {
    HAL_NVIC_EnableIRQ(TIM6_IRQn);
}

void hal_set_timer_irq_disable(void) {
    HAL_NVIC_DisableIRQ(TIM6_IRQn);
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
    HAL_NVIC_EnableIRQ(TIM7_IRQn);
}

void hal_reset_timer_irq_disable(void) {
    HAL_NVIC_DisableIRQ(TIM7_IRQn);
}

void hal_set_tim_prescaler(uint32_t prescaler) {
    htim_reset.Init.Prescaler = prescaler;
}

void TIM7_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&STEP_RESET_TIMER);
}

void TIM6_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&STEP_SET_TIMER);
}





