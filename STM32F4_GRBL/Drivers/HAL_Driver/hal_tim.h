#ifndef __hal_tim_h
#define __hal_tim_h

#include "main.h"


typedef TIM_HandleTypeDef timer_def;

typedef struct {

    timer_def   step_set;
    timer_def   step_reset;

    void (*hal_step_timer_set_init)(void *);
    void (*hal_step_timer_reset_init)(void *);

    void (*hal_step_hal_time_set_iqr_en)(void *);
    void (*hal_step_hal_time_reset_iqr_en)(void *);

    void (*hal_step_tim_set_relaod)(timer_def *, uint32_t *);
    void (*hal_step_tim_generateEvent_update)(timer_def *);
    void (*hal_step_tim_clear_flag_update)(timer_def *);
}STEP_TIM_t;




extern TIM_HandleTypeDef htim3; 
extern TIM_HandleTypeDef htim4; 

#define STEP_RESET_TIMER    htim4
#define STEP_SET_TIMER      htim3

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

#endif
