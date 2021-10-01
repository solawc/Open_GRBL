#ifndef __hal_tim_h
#define __hal_tim_h

#include "main.h"

extern TIM_HandleTypeDef htim3; 
extern TIM_HandleTypeDef htim4; 

#define STEP_RESET_TIMER    htim4
#define STEP_SET_TIMER      htim3

void hal_set_timer_init(void);
void hal_reset_timer_init(void);
// void hal_tim_move_step_arr(uint32_t num);
void hal_set_timer_irq_enable(void);
void hal_set_timer_irq_disable(void);
void hal_reset_timer_irq_enable(void);
void hal_reset_timer_irq_disable(void);

void hal_set_tim_prescaler(uint32_t prescaler);


void hal_tim_set_reload(TIM_HandleTypeDef *htim, uint32_t reload);
void hal_tim_generateEvent_update(TIM_HandleTypeDef *htim);
void hal_tim_clear_flag_update(TIM_HandleTypeDef *htim);

#endif
