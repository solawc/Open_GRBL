#ifndef __hal_gpio_h
#define __hal_gpio_h

#include "main.h"

void hal_led_gpio_init(void);
void hal_led_on(void);
void hal_led_off(void);
void hal_led_toggle(void);

// limits
#define LIMIT_X_PORT        GPIOD
#define LIMIT_X_PIN         GPIO_PIN_4
#define LIMIT_Y_PORT        GPIOD
#define LIMIT_Y_PIN         GPIO_PIN_11
#define LIMIT_Z_PORT        GPIOD
#define LIMIT_Z_PIN         GPIO_PIN_12
#define LIMIT_IRQnHANDLE    EXTI0_IRQHandler

#define STEP_EN_PORT        GPIOI
#define STEP_EN_PIN         GPIO_PIN_8

#define MOTOR_X_DIR_PORT    GPIOI
#define MOTOR_X_DIR_PIN     GPIO_PIN_5
#define MOTOR_Y_DIR_PORT    GPIOI
#define MOTOR_Y_DIR_PIN     GPIO_PIN_6
#define MOTOR_Z_DIR_PORT    GPIOI
#define MOTOR_Z_DIR_PIN     GPIO_PIN_7

#define MOTOR_X_AXIS_PORT   GPIOA
#define MOTOR_X_AXIS_PIN    GPIO_PIN_4
#define MOTOR_Y_AXIS_PORT   GPIOA
#define MOTOR_Y_AXIS_PIN    GPIO_PIN_6
#define MOTOR_Z_AXIS_PORT   GPIOA
#define MOTOR_Z_AXIS_PIN    GPIO_PIN_8

void hal_limit_gpio_init(void);
void hal_limit_gpio_irq_enable(void);
void hal_limit_gpio_irq_disable(void);
uint8_t hal_limits_get_gpio_status(uint8_t axis);

void hal_set_dir_gpio_status(uint8_t mask);
void hal_set_step_gpio_status(uint8_t mask);
void hal_set_step_gpio_toggle(uint8_t mask);
void hal_motor_gpio_init(void);
void hal_step_en_gpio_set(bool status);
uint8_t hal_get_moter_dir_gpio_mask(uint8_t axis);
uint8_t hal_get_moter_axis_gpio_mask(uint8_t axis);

#endif
