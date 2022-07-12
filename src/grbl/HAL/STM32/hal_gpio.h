#ifndef __hal_gpio_h
#define __hal_gpio_h

#include "../../../main.h"

#define LASER_PORT                  BOARD_LASER_PORT
#define LASER_PIN                   BOARD_LASER_PIN
#define LASER_PIN_CLK_ENABLE()      BOARD_LASER_PIN_CLK_ENABLE

#define LIMIT_X_PORT                BOARD_LIMIT_X_PORT // GPIOB
#define LIMIT_X_PIN                 BOARD_LIMIT_X_PIN  // GPIO_PIN_0
#define LIMIT_Y_PORT                BOARD_LIMIT_Y_PORT // GPIOB
#define LIMIT_Y_PIN                 BOARD_LIMIT_Y_PIN  // GPIO_PIN_1
// #define LIMIT_Z_PORT                BOARD_LIMIT_Z_PORT
// #define LIMIT_Z_PIN                 BOARD_LIMIT_Z_PIN

#define LIMIT_IRQnHANDLE            BOARD_LIMIT_IRQnHANDLER
#define LIMIT_IRQn                  BOARD_LIMIT_IRQ

// #define STEP_EN_PORT                BOARD_X_EN_PORT
// #define STEP_EN_PIN                 BOARD_X_EN_PIN

#ifndef STEP_EN_PORT
#define STEP_X_EN_PORT              BOARD_X_EN_PORT      
#define STEP_X_EN_PIN               BOARD_X_EN_PIN   
#define STEP_Y_EN_PORT              BOARD_Y_EN_PORT      
#define STEP_Y_EN_PIN               BOARD_Y_EN_PIN   
// #define STEP_Z_EN_PORT              BOARD_Z_EN_PORT      
// #define STEP_Z_EN_PIN               BOARD_Z_EN_PIN   
#endif

#define MOTOR_X_DIR_PORT            BOARD_X_DIR_PORT
#define MOTOR_X_DIR_PIN             BOARD_X_DIR_PIN 
#define MOTOR_Y_DIR_PORT            BOARD_Y_DIR_PORT
#define MOTOR_Y_DIR_PIN             BOARD_Y_DIR_PIN 
// #define MOTOR_Z_DIR_PORT            BOARD_Z_DIR_PORT
// #define MOTOR_Z_DIR_PIN             BOARD_Z_DIR_PIN

#define MOTOR_X_AXIS_PORT           BOARD_X_STEP_PORT 
#define MOTOR_X_AXIS_PIN            BOARD_X_STEP_PIN  
#define MOTOR_Y_AXIS_PORT           BOARD_Y_STEP_PORT 
#define MOTOR_Y_AXIS_PIN            BOARD_Y_STEP_PIN  
// #define MOTOR_Z_AXIS_PORT            BOARD_Z_STEP_PORT 
// #define MOTOR_Z_AXIS_PIN             BOARD_Z_STEP_PIN  

#define PROBE_PORT                  GPIOB
#define PROBE_PIN                   GPIO_PIN_11

/* 液体冷却 */
#define FLOOD_PORT                  GPIOB
#define FLOOD_PIN                   GPIO_PIN_3

/*空气冷却*/    
#define MIST_PORT                   GPIOB
#define MIST_PIN                    GPIO_PIN_3   


void hal_limit_gpio_init(void);
void hal_limit_gpio_irq_enable(void);
void hal_limit_gpio_irq_disable(void);
uint8_t hal_limits_get_gpio_status(uint8_t axis);
uint8_t hal_get_all_limits_status(uint8_t bit_select);

void hal_motor_gpio_init(void);
void hal_set_dir_gpio_status(uint8_t mask);
void hal_set_step_gpio_status(uint8_t mask);
void hal_step_en_gpio_set(bool status);
uint8_t hal_get_moter_dir_gpio_mask(uint8_t axis);
uint8_t hal_get_moter_axis_gpio_mask(uint8_t axis);

void hal_probe_gpio_init(void);
uint8_t hal_probe_gpio_read(void);

void hal_coolant_pin_init(void);
void set_coolant_flood(bool status);
void set_coolant_mist(bool status);
uint8_t get_coolant_flood(void);
uint8_t get_coolant_mist(void);

#endif
