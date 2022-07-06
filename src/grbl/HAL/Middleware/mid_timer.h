#ifndef __mid_timer_h
#define __mid_timer_h

#include "../../../main.h"

typedef struct {

    /**************Stepper timer***************/
    void (*stepper_timer_init)(void);
    void (*set_timer_irq_enable)(void);
    void (*reset_timer_irq_enable)(void);
    void (*set_timer_irq_disable)(void);
    void (*reset_timer_irq_disable)(void);
    void (*set_timer_begin)(void);
    void (*reset_timer_begin)(void);

    /**************Spindle Pwm***************/
    void (*spindle_pwm_init)(void);
    void (*spindle_pwm_set)(uint32_t);
    uint32_t (*spindle_pwm_get)(void);

}mid_timer_t;





#endif
