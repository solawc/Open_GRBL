#ifndef __hal_tim_h
#define __hal_tim_h

#include "../../../main.h"

typedef TIM_HandleTypeDef timer_def;

#define STEP_SET_TIM        hal_step_tim.step_set
#define STEP_RESET_TIM      hal_step_tim.step_reset
#define LASER_TIM           hal_step_tim.laser

#ifdef STM32F429xx
#define SETP_SET_TIM                TIM3
#define SETP_RESET_TIM              TIM4
#define STEP_SET_TIMER              STEP_SET_TIM
#define STEP_RESET_TIMER            STEP_RESET_TIM
#define SET_TIM_IRQn                TIM3_IRQn
#define RESET_TIM_IRQn              TIM4_IRQn
#define SET_TIM_CLK_ENABLED()       __HAL_RCC_TIM3_CLK_ENABLE()
#define RESET_TIM_CLK_ENABLED()     __HAL_RCC_TIM4_CLK_ENABLE()
#define STEP_SET_HANDLER            TIM3_IRQHandler
#define STEP_RESET_HANDLER          TIM4_IRQHandler
#define LASER_TIM_PORT              TIM1
#define LASER_TIM_CH                TIM_CHANNEL_2
#define LASER_PIN_AF                GPIO_AF1_TIM1
#define LASER_OUT_PORT              GPIOB
#define LASER_OUT_PIN               GPIO_PIN_6
#define LASER_OUT_CLK()             __HAL_RCC_TIM4_CLK_ENABLE()
#define LASER_OUT_PIN_CLK()         __HAL_RCC_GPIOB_CLK_ENABLE()
#elif defined(STM32G0B0xx)
#define SETP_SET_TIM                TIM6
#define SETP_RESET_TIM              TIM7
#define SET_TIM_IRQn                TIM6_IRQn
#define RESET_TIM_IRQn              TIM7_IRQn
#define STEP_SET_TIMER              STEP_SET_TIM
#define STEP_RESET_TIMER            STEP_RESET_TIM
#define SET_TIM_CLK_ENABLED()       __HAL_RCC_TIM6_CLK_ENABLE();
#define RESET_TIM_CLK_ENABLED()     __HAL_RCC_TIM7_CLK_ENABLE();
#define STEP_SET_HANDLER            TIM6_IRQHandler
#define STEP_RESET_HANDLER          TIM7_IRQHandler
#define LASER_TIM_PORT              TIM4
#define LASER_TIM_CH                TIM_CHANNEL_1
#define LASER_PIN_AF                GPIO_AF9_TIM4
#define LASER_OUT_PORT              GPIOB
#define LASER_OUT_PIN               GPIO_PIN_6
#define LASER_OUT_CLK()             __HAL_RCC_TIM4_CLK_ENABLE()
#define LASER_OUT_PIN_CLK()         __HAL_RCC_GPIOB_CLK_ENABLE()
#elif defined(STM32G070xx)
#define SETP_SET_TIM                TIM6
#define SETP_RESET_TIM              TIM7
#define SET_TIM_IRQn                TIM6_IRQn
#define RESET_TIM_IRQn              TIM7_IRQn
#define STEP_SET_TIMER              STEP_SET_TIM
#define STEP_RESET_TIMER            STEP_RESET_TIM
#define SET_TIM_CLK_ENABLED()       __HAL_RCC_TIM6_CLK_ENABLE();
#define RESET_TIM_CLK_ENABLED()     __HAL_RCC_TIM7_CLK_ENABLE();
#define STEP_SET_HANDLER            TIM6_IRQHandler
#define STEP_RESET_HANDLER          TIM7_IRQHandler
#define LASER_TIM_PORT              TIM1
#define LASER_TIM_CH                TIM_CHANNEL_2
#define LASER_PIN_AF                GPIO_AF1_TIM1
#define LASER_OUT_PORT              GPIOB
#define LASER_OUT_PIN               GPIO_PIN_6
#define LASER_OUT_CLK()             __HAL_RCC_TIM1_CLK_ENABLE()
#define LASER_OUT_PIN_CLK()         __HAL_RCC_GPIOB_CLK_ENABLE()
#elif defined(STM32F407xx)
#define SETP_SET_TIM                TIM3
#define SETP_RESET_TIM              TIM4
#define SET_TIM_IRQn                TIM3_IRQn
#define RESET_TIM_IRQn              TIM4_IRQn
#define STEP_SET_TIMER              STEP_SET_TIM
#define STEP_RESET_TIMER            STEP_RESET_TIM
#define SET_TIM_CLK_ENABLED()       __HAL_RCC_TIM3_CLK_ENABLE();
#define RESET_TIM_CLK_ENABLED()     __HAL_RCC_TIM4_CLK_ENABLE();
#define STEP_SET_HANDLER            TIM3_IRQHandler
#define STEP_RESET_HANDLER          TIM4_IRQHandler
#define LASER_TIM_PORT              TIM1
#define LASER_TIM_CH                TIM_CHANNEL_2
#define LASER_PIN_AF                GPIO_AF1_TIM1
#define LASER_OUT_PORT              GPIOB
#define LASER_OUT_PIN               GPIO_PIN_6
#define LASER_OUT_CLK()             __HAL_RCC_TIM4_CLK_ENABLE()
#define LASER_OUT_PIN_CLK()         __HAL_RCC_GPIOB_CLK_ENABLE()
#endif

typedef struct  
{
    timer_def step_set;
    timer_def step_reset;
    timer_def laser;

    uint16_t set_timer_psc;    
    uint16_t set_timer_arr;

    uint16_t reset_timer_psc;    
    uint16_t reset_timer_arr;

    void (*tim_set_handler)(void *);
    void (*tim_reset_handler)(void *);
    void (*tim_config_init)(void *);
    void (*tim_set_period)(timer_def *, uint32_t *);
    void (*tim_set_prescaler)(timer_def *, uint32_t *);
    void (*tim_irq_set) (timer_def *, bool *);
    
}hal_tim_t;
extern hal_tim_t hal_step_tim;


void hal_set_timer_init(void);
void hal_reset_timer_init(void);
void hal_base_timer_init(void);
void hal_reset_timer_begin(void);
void hal_set_timer_begin(void);
void hal_set_timer_irq_enable(void);
void hal_set_timer_irq_disable(void);
void hal_reset_timer_irq_enable(void);
void hal_reset_timer_irq_disable(void);
void hal_tim_set_reload(TIM_HandleTypeDef *htim, uint32_t reload);
void hal_tim_generateEvent_update(TIM_HandleTypeDef *htim);
void hal_tim_clear_flag_update(TIM_HandleTypeDef *htim);
void hal_set_tim_cnt(TIM_HandleTypeDef *htim, uint32_t cnt);

void hal_pwm_init();
void hal_pwm_set(uint32_t duty);
uint32_t hal_pwm_ccr_get(void);
#endif
