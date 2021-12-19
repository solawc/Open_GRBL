#ifndef __hal_tim_h
#define __hal_tim_h

#include "../main.h"

typedef TIM_HandleTypeDef timer_def;

// extern TIM_HandleTypeDef htim3; 
// extern TIM_HandleTypeDef htim4; 
extern TIM_HandleTypeDef htim_set;    // Configure Timer 6: Stepper Driver Interrupt
extern TIM_HandleTypeDef htim_reset;    // Configure Timer 7: Stepper Port Reset Interrupt
extern TIM_HandleTypeDef htim_laser;    // Configure Timer 7: Stepper Port Reset Interrupt

#ifdef STM32F429xx
#define SETP_SET_TIM                TIM3
#define SETP_RESET_TIM              TIM4
#define STEP_SET_TIMER              htim_set
#define STEP_RESET_TIMER            htim_reset
#define SET_TIM_IRQn                TIM3_IRQn
#define RESET_TIM_IRQn              TIM4_IRQn
#define SET_TIM_CLK_ENABLED()       __HAL_RCC_TIM3_CLK_ENABLE();
#define RESET_TIM_CLK_ENABLED()     __HAL_RCC_TIM4_CLK_ENABLE();
#elif defined(STM32G0B0xx)
#define SETP_SET_TIM                TIM6
#define SETP_RESET_TIM              TIM7
#define SET_TIM_IRQn                TIM6_IRQn
#define RESET_TIM_IRQn              TIM7_IRQn
#define STEP_SET_TIMER              htim_set
#define STEP_RESET_TIMER            htim_reset
#define SET_TIM_CLK_ENABLED()       __HAL_RCC_TIM6_CLK_ENABLE();
#define RESET_TIM_CLK_ENABLED()     __HAL_RCC_TIM7_CLK_ENABLE();
#define STEP_SET_HANDLER            TIM6_IRQHandler
#define STEP_RESET_HANDLER          TIM7_IRQHandler
#define LASER_TIM                   TIM4
#endif

typedef struct  
{
    timer_def step_set;
    timer_def step_reset;

    uint8_t tim_addr;   // tim自动重装载
    uint8_t tim_p;      

    void (*tim_set_handler)(void *);
    void (*tim_reset_handler)(void *);
    void (*tim_config_init)(void *);
    void (*tim_set_period)(timer_def *, uint32_t *);
    void (*tim_set_prescaler)(timer_def *, uint32_t *);
    void (*tim_irq_set) (timer_def *, bool *);
    
}hal_tim_t;

void hal_set_timer_init(void);
void hal_reset_timer_init(void);
void hal_set_timer_irq_enable(void);
void hal_set_timer_irq_disable(void);
void hal_reset_timer_irq_enable(void);
void hal_reset_timer_irq_disable(void);
void hal_set_tim_prescaler(uint32_t prescaler);
void hal_tim_set_reload(TIM_HandleTypeDef *htim, uint32_t reload);
void hal_tim_generateEvent_update(TIM_HandleTypeDef *htim);
void hal_tim_clear_flag_update(TIM_HandleTypeDef *htim);
void hal_set_tim_cnt(TIM_HandleTypeDef *htim, uint32_t cnt);

#endif
