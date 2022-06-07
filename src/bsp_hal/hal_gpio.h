#ifndef __hal_gpio_h
#define __hal_gpio_h

#include "main.h"

// limits
#ifdef STM32F429xx
#define LASER_PORT                  GPIOB
#define LASER_PIN                   GPIO_PIN_7
#define LASER_PIN_CLK_ENABLE()      __HAL_RCC_GPIOH_CLK_ENABLE()

#define LIMIT_X_PORT        GPIOD
#define LIMIT_X_PIN         GPIO_PIN_4
#define LIMIT_Y_PORT        GPIOD
#define LIMIT_Y_PIN         GPIO_PIN_11
// #define LIMIT_Z_PORT        GPIOD
// #define LIMIT_Z_PIN         GPIO_PIN_12
#define LIMIT_IRQnHANDLE    EXTI0_IRQHandler

#define LIMIT_IRQnHANDLE            EXTI0_IRQHandler
#define LIMIT_IRQn                  EXTI0_IRQn

#define STEP_EN_PORT        GPIOI
#define STEP_EN_PIN         GPIO_PIN_8

#define MOTOR_X_DIR_PORT    GPIOI
#define MOTOR_X_DIR_PIN     GPIO_PIN_5
#define MOTOR_Y_DIR_PORT    GPIOI
#define MOTOR_Y_DIR_PIN     GPIO_PIN_6
// #define MOTOR_Z_DIR_PORT    GPIOI
// #define MOTOR_Z_DIR_PIN     GPIO_PIN_7

#define MOTOR_X_AXIS_PORT   GPIOA
#define MOTOR_X_AXIS_PIN    GPIO_PIN_4
#define MOTOR_Y_AXIS_PORT   GPIOA
#define MOTOR_Y_AXIS_PIN    GPIO_PIN_6
// #define MOTOR_Z_AXIS_PORT   GPIOA
// #define MOTOR_Z_AXIS_PIN    GPIO_PIN_8

#define PROBE_PORT                  GPIOB
#define PROBE_PIN                   GPIO_PIN_11

#elif defined(STM32G0B0xx)

#define LASER_PORT                  GPIOB
#define LASER_PIN                   GPIO_PIN_7
#define LASER_PIN_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

#define LIMIT_X_PORT                GPIOB
#define LIMIT_X_PIN                 GPIO_PIN_0
#define LIMIT_Y_PORT                GPIOB
#define LIMIT_Y_PIN                 GPIO_PIN_1
// #define LIMIT_Z_PORT                GPIOB
// #define LIMIT_Z_PIN                 GPIO_PIN_1
#define LIMIT_IRQnHANDLE            EXTI0_1_IRQHandler
#define LIMIT_IRQn                  EXTI0_1_IRQn

#define STEP_EN_PORT                GPIOC
#define STEP_EN_PIN                 GPIO_PIN_15

// #define STEP_X_EN_PORT
// #define STEP_X_EN_PIN
// #define STEP_Y_EN_PORT
// #define STEP_Y_EN_PIN
// #define STEP_Z_EN_PORT
// #define STEP_Z_EN_PIN

#define MOTOR_X_DIR_PORT            GPIOC
#define MOTOR_X_DIR_PIN             GPIO_PIN_13
#define MOTOR_Y_DIR_PORT            GPIOB
#define MOTOR_Y_DIR_PIN             GPIO_PIN_8
// #define MOTOR_Z_DIR_PORT            GPIOB
// #define MOTOR_Z_DIR_PIN             GPIO_PIN_8

#define MOTOR_X_AXIS_PORT           GPIOC
#define MOTOR_X_AXIS_PIN            GPIO_PIN_14
#define MOTOR_Y_AXIS_PORT           GPIOB
#define MOTOR_Y_AXIS_PIN            GPIO_PIN_9
// #define MOTOR_Z_AXIS_PORT           GPIOB
// #define MOTOR_Z_AXIS_PIN            GPIO_PIN_9

#define PROBE_PORT                  GPIOB
#define PROBE_PIN                   GPIO_PIN_11

#elif defined(STM32F407xx)
#define LASER_PORT                  GPIOE
#define LASER_PIN                   GPIO_PIN_5
#define LASER_PIN_CLK_ENABLE()      __HAL_RCC_GPIOE_CLK_ENABLE()

#define LIMIT_X_PORT        GPIOA
#define LIMIT_X_PIN         GPIO_PIN_15
#define LIMIT_Y_PORT        GPIOD
#define LIMIT_Y_PIN         GPIO_PIN_2
#define LIMIT_Z_PORT        GPIOC
#define LIMIT_Z_PIN         GPIO_PIN_8

#define LIMIT_IRQnHANDLE            EXTI0_IRQHandler
#define LIMIT_IRQn                  EXTI0_IRQn

#define STEP_EN_PORT                GPIOE
#define STEP_EN_PIN                 GPIO_PIN_4

#define MOTOR_X_DIR_PORT            GPIOE
#define MOTOR_X_DIR_PIN             GPIO_PIN_2
#define MOTOR_Y_DIR_PORT            GPIOB
#define MOTOR_Y_DIR_PIN             GPIO_PIN_9
#define MOTOR_Z_DIR_PORT            GPIOB
#define MOTOR_Z_DIR_PIN             GPIO_PIN_4

#define MOTOR_X_AXIS_PORT           GPIOE
#define MOTOR_X_AXIS_PIN            GPIO_PIN_3
#define MOTOR_Y_AXIS_PORT           GPIOE
#define MOTOR_Y_AXIS_PIN            GPIO_PIN_0
#define MOTOR_Z_AXIS_PORT           GPIOB
#define MOTOR_Z_AXIS_PIN            GPIO_PIN_5

#define PROBE_PORT                  GPIOA
#define PROBE_PIN                   GPIO_PIN_8

#endif

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

#endif
