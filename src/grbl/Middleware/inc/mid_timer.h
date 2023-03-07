/*
 mid_timer.h

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __mid_timer_h
#define __mid_timer_h

#include "../../main.h"

typedef struct {

    /**************Stepper timer***************/
    void (*stepper_timer_init)(void);
    void (*set_timer_irq_enable)(void);
    void (*reset_timer_irq_enable)(void);
    void (*set_timer_irq_disable)(void);
    void (*reset_timer_irq_disable)(void);
    void (*set_timer_begin)(void);
    void (*reset_timer_begin)(void);
    void (*set_timer_reload)(uint32_t);
    void (*reset_timer_reload)(uint32_t);

    /**************Spindle Pwm***************/
    void (*spindle_pwm_init)(void);
    void (*spindle_pwm_set)(uint32_t);
    uint32_t (*spindle_pwm_get)(void);
    
}mid_timer_t;
mid_timer_t dev_timer;

void DevTimerInit(void);

#endif
