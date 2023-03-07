/*
 hal_tim.h

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __hal_tim_h
#define __hal_tim_h

#include "../../../main.h"

typedef TIM_HandleTypeDef timer_def;

/* Define Timer Port */
#define _TIM(X)                     TIM##X
#define TIM(X)                      _TIM(X)

/* Define Timer IRQn */
#define _TIM_IRQn(X)                TIM##X##_IRQn
#define TIM_IRQn(X)                 _TIM_IRQn(X)
#define _TIM_IRQHander(X)           TIM##X##_IRQHandler
#define TIM_IRQHander(X)            _TIM_IRQHander(X)

/* Define Timer Rcc */
#define _TIM_RCC(X)                 __HAL_RCC_TIM##X##_CLK_ENABLE()
#define TIM_RCC(X)                   _TIM_RCC(X)

/* Define TIMER Handler */
#define STEP_SET_TIM                hal_step_tim.step_set
#define STEP_RESET_TIM              hal_step_tim.step_reset
#define LASER_TIM                   hal_step_tim.laser

/* Define TIMER Freq */
#define STEP_SET_TIM_FREQ           BOARD_SET_TIM_FREQ
#define STEP_RESET_TIM_FREQ         BOARD_RESET_TIM_FREQ


#define SETP_SET_TIM                TIM(BOARD_SET_TIM)                     
#define SETP_RESET_TIM              TIM(BOARD_RESET_TIM)                  
#define SET_TIM_IRQn                TIM_IRQn(BOARD_SET_TIM)            
#define RESET_TIM_IRQn              TIM_IRQn(BOARD_RESET_TIM)          
#define SET_TIM_CLK_ENABLED()       TIM_RCC(BOARD_SET_TIM)            
#define RESET_TIM_CLK_ENABLED()     TIM_RCC(BOARD_RESET_TIM)          
#define STEP_SET_HANDLER            TIM_IRQHander(BOARD_SET_TIM)        
#define STEP_RESET_HANDLER          TIM_IRQHander(BOARD_RESET_TIM)     
#define STEP_SET_TIMER              STEP_SET_TIM          
#define STEP_RESET_TIMER            STEP_RESET_TIM    

#define LASER_TIM_PORT              TIM(BOARD_LASER_TIM_PORT)            
#define LASER_TIM_CH                BOARD_LASER_TIM_CH            
#define LASER_PIN_AF                BOARD_LASER_PIN_AF            
#define LASER_OUT_PORT              BOARD_LASER_OUT_PORT          
#define LASER_OUT_PIN               BOARD_LASER_OUT_PIN           
#define LASER_OUT_CLK()             TIM_RCC(BOARD_LASER_TIM_PORT)     

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
