#ifndef __hal_tim_h
#define __hal_tim_h

#include "main.h"

typedef TIM_HandleTypeDef timer_def;

extern TIM_HandleTypeDef htim3; 
extern TIM_HandleTypeDef htim4; 

#define STEP_RESET_TIMER    htim4
#define STEP_SET_TIMER      htim3

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
