/*
 mid_timer.c

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "mid_timer.h"

mid_timer_t dev_timer;

void DevTimerInit(void) {
    
    dev_timer.stepper_timer_init        = hal_base_timer_init;
    dev_timer.reset_timer_begin         = hal_reset_timer_begin;
    dev_timer.set_timer_begin           = hal_set_timer_begin;
    dev_timer.set_timer_irq_enable      = hal_set_timer_irq_enable;
    dev_timer.set_timer_irq_disable     = hal_set_timer_irq_disable;
    dev_timer.reset_timer_irq_enable    = hal_reset_timer_irq_enable;
    dev_timer.reset_timer_irq_disable   = hal_reset_timer_irq_disable;

    dev_timer.spindle_pwm_init          = hal_pwm_init;
    dev_timer.spindle_pwm_set           = hal_pwm_set;
    dev_timer.spindle_pwm_get           = hal_pwm_ccr_get;
}