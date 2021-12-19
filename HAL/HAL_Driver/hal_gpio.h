#ifndef __hal_gpio_h
#define __hal_gpio_h

#include "main.h"

void hal_led_gpio_init(void);
void hal_led_on(void);
void hal_led_off(void);
void hal_led_toggle(void);


// Laser led 
#define LASER_PORT          GPIOB
#define LASER_PIN           GPIO_PIN_7

// limits
#define LIMIT_X_PORT        GPIOB
#define LIMIT_X_PIN         GPIO_PIN_0
#define LIMIT_Y_PORT        GPIOB
#define LIMIT_Y_PIN         GPIO_PIN_1
// #define LIMIT_Z_PORT        GPIOC
// #define LIMIT_Z_PIN         GPIO_PIN_15
#define LIMIT_IRQnHANDLE    EXTI0_IRQHandler

#define STEP_EN_PORT        GPIOC
#define STEP_EN_PIN         GPIO_PIN_15

#define MOTOR_X_DIR_PORT    GPIOC
#define MOTOR_X_DIR_PIN     GPIO_PIN_13
#define MOTOR_Y_DIR_PORT    GPIOB
#define MOTOR_Y_DIR_PIN     GPIO_PIN_8
// #define MOTOR_Z_DIR_PORT    GPIOI
// #define MOTOR_Z_DIR_PIN     GPIO_PIN_7

#define MOTOR_X_AXIS_PORT   GPIOC
#define MOTOR_X_AXIS_PIN    GPIO_PIN_14
#define MOTOR_Y_AXIS_PORT   GPIOB
#define MOTOR_Y_AXIS_PIN    GPIO_PIN_9
// #define MOTOR_Z_AXIS_PORT   GPIOA
// #define MOTOR_Z_AXIS_PIN    GPIO_PIN_8

void hal_limit_gpio_init(void);
void hal_limit_gpio_irq_enable(void);
void hal_limit_gpio_irq_disable(void);
uint8_t hal_limits_get_gpio_status(uint8_t axis);

void hal_set_dir_gpio_status(uint8_t mask);
void hal_set_step_gpio_status(uint8_t mask);
void hal_motor_gpio_init(void);
void hal_step_en_gpio_set(bool status);
uint8_t hal_get_moter_dir_gpio_mask(uint8_t axis);
uint8_t hal_get_moter_axis_gpio_mask(uint8_t axis);

#endif
