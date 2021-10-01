#ifndef __hal_gpio_h
#define __hal_gpio_h

#include "main.h"

void hal_led_gpio_init(void);
void hal_led_on(void);
void hal_led_off(void);
void hal_led_toggle(void);

// limits
#define LIMIT_X_PORT        GPIOA
#define LIMIT_X_PIN         GPIO_PIN_0
#define LIMIT_X_NUM         0
#define LIMIT_Y_PORT        GPIOC
#define LIMIT_Y_PIN         GPIO_PIN_13
#define LIMIT_Y_NUM         13
#define LIMIT_Z_PORT        GPIOC
#define LIMIT_Z_PIN         GPIO_PIN_14
#define LIMIT_Z_NUM         14
#define LIMIT_IRQnHANDLE    EXTI0_IRQHandler

#define STEP_EN_PORT        GPIOA
#define STEP_EN_PIN        GPIO_PIN_1

#define MOTOR_X_DIR_PORT    GPIOA
#define MOTOR_X_DIR_PIN     GPIO_PIN_4
#define MOTOR_X_DIR_NUM     4
#define MOTOR_Y_DIR_PORT    GPIOA
#define MOTOR_Y_DIR_PIN     GPIO_PIN_5
#define MOTOR_Y_DIR_NUM     5
#define MOTOR_Z_DIR_PORT    GPIOA
#define MOTOR_Z_DIR_PIN     GPIO_PIN_6
#define MOTOR_Z_DIR_NUM     6

#define MOTOR_X_AXIS_PORT   GPIOB
#define MOTOR_X_AXIS_PIN    GPIO_PIN_1
#define MOTOR_X_AXIS_NUM    1
#define MOTOR_Y_AXIS_PORT   GPIOB
#define MOTOR_Y_AXIS_PIN    GPIO_PIN_2
#define MOTOR_Y_AXIS_NUM    2
#define MOTOR_Z_AXIS_PORT   GPIOB
#define MOTOR_Z_AXIS_PIN    GPIO_PIN_3
#define MOTOR_Z_AXIS_NUM    3

void hal_limit_gpio_init(void);
void hal_limit_gpio_irq_enable(void);
void hal_limit_gpio_irq_disable(void);
uint8_t hal_limits_get_gpio_status(uint8_t axis);

void hal_motor_gpio_init(void);
void hal_step_en_gpio_set(bool status);
uint8_t hal_get_moter_dir_gpio_mask(uint8_t axis);
uint8_t hal_get_moter_axis_gpio_mask(uint8_t axis);

#endif
