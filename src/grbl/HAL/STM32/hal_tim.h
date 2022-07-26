#ifndef __hal_tim_h
#define __hal_tim_h

#include "../../../main.h"

typedef TIM_HandleTypeDef timer_def;

#define STEP_SET_TIM        hal_step_tim.step_set
#define STEP_RESET_TIM      hal_step_tim.step_reset
#define LASER_TIM           hal_step_tim.laser

#define SETP_SET_TIM                BOARD_SETP_SET_TIM            
#define SETP_RESET_TIM              BOARD_SETP_RESET_TIM          
#define STEP_SET_TIMER              BOARD_STEP_SET_TIMER          
#define STEP_RESET_TIMER            BOARD_STEP_RESET_TIMER        
#define SET_TIM_IRQn                BOARD_SET_TIM_IRQn            
#define RESET_TIM_IRQn              BOARD_RESET_TIM_IRQn          
#define SET_TIM_CLK_ENABLED()       BOARD_SET_TIM_CLK_ENABLED()   
#define RESET_TIM_CLK_ENABLED()     BOARD_RESET_TIM_CLK_ENABLED() 
#define STEP_SET_HANDLER            BOARD_STEP_SET_HANDLER        
#define STEP_RESET_HANDLER          BOARD_STEP_RESET_HANDLER      
#define LASER_TIM_PORT              BOARD_LASER_TIM_PORT          
#define LASER_TIM_CH                BOARD_LASER_TIM_CH            
#define LASER_PIN_AF                BOARD_LASER_PIN_AF            
#define LASER_OUT_PORT              BOARD_LASER_OUT_PORT          
#define LASER_OUT_PIN               BOARD_LASER_OUT_PIN           
#define LASER_OUT_CLK()             BOARD_LASER_OUT_CLK()         
#define LASER_OUT_PIN_CLK()         BOARD_LASER_OUT_PIN_CLK()     

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
