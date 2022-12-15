/*
 bsp_gpio.h

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __hal_gpio_h
#define __hal_gpio_h

#ifdef __cplusplus
extern "C" {
#endif

#include "../../../main.h"

/* Redefine GPIO Clk */ 
#define _HAL_RCC_GPIO_ENABLE(X)     __HAL_RCC_GPIO##X##_CLK_ENABLE()
#define HAL_RCC_GPIO_ENABLE(X)      _HAL_RCC_GPIO_ENABLE(X)

#define LIMIT_X_PORT                BOARD_LIMIT_X_PORT // GPIOB
#define LIMIT_X_PIN                 BOARD_LIMIT_X_PIN  // GPIO_PIN_0
#define LIMIT_Y_PORT                BOARD_LIMIT_Y_PORT // GPIOB
#define LIMIT_Y_PIN                 BOARD_LIMIT_Y_PIN  // GPIO_PIN_1
#ifdef BOARD_LIMIT_Z_PORT
#define LIMIT_Z_PORT                BOARD_LIMIT_Z_PORT
#endif // BOARD_LIMIT_Z_PORT
#ifdef BOARD_LIMIT_Z_PIN
#define LIMIT_Z_PIN                 BOARD_LIMIT_Z_PIN
#endif // BOARD_LIMIT_Z_PIN

#define LIMIT_IRQnHANDLE            BOARD_LIMIT_IRQnHANDLER
#define LIMIT_IRQn                  BOARD_LIMIT_IRQ

// #define STEP_EN_PORT                BOARD_X_EN_PORT
// #define STEP_EN_PIN                 BOARD_X_EN_PIN

#ifndef STEP_EN_PORT
#define STEP_X_EN_PORT              BOARD_X_EN_PORT      
#define STEP_X_EN_PIN               BOARD_X_EN_PIN   
#define STEP_Y_EN_PORT              BOARD_Y_EN_PORT      
#define STEP_Y_EN_PIN               BOARD_Y_EN_PIN   
#ifdef BOARD_Z_EN_PORT
#define STEP_Z_EN_PORT              BOARD_Z_EN_PORT    
#endif  // BOARD_Z_EN_PORT
#ifdef BOARD_Z_EN_PIN
#define STEP_Z_EN_PIN               BOARD_Z_EN_PIN  
#endif  // BOARD_Z_EN_PIN
#endif

#define MOTOR_X_DIR_PORT            BOARD_X_DIR_PORT
#define MOTOR_X_DIR_PIN             BOARD_X_DIR_PIN 
#define MOTOR_Y_DIR_PORT            BOARD_Y_DIR_PORT
#define MOTOR_Y_DIR_PIN             BOARD_Y_DIR_PIN 
#ifdef BOARD_Z_DIR_PORT
#define MOTOR_Z_DIR_PORT            BOARD_Z_DIR_PORT
#endif 
#ifdef BOARD_Z_DIR_PIN
#define MOTOR_Z_DIR_PIN             BOARD_Z_DIR_PIN
#endif

#define MOTOR_X_AXIS_PORT           BOARD_X_STEP_PORT 
#define MOTOR_X_AXIS_PIN            BOARD_X_STEP_PIN  
#define MOTOR_Y_AXIS_PORT           BOARD_Y_STEP_PORT 
#define MOTOR_Y_AXIS_PIN            BOARD_Y_STEP_PIN  
#ifdef BOARD_Z_STEP_PORT
#define MOTOR_Z_AXIS_PORT            BOARD_Z_STEP_PORT 
#endif 
#ifdef BOARD_Z_STEP_PIN
#define MOTOR_Z_AXIS_PIN             BOARD_Z_STEP_PIN  
#endif 

#define PROBE_PORT                  GPIOB
#define PROBE_PIN                   GPIO_PIN_11

/* 液体冷却 */
#define FLOOD_PORT                  GPIOB
#define FLOOD_PIN                   GPIO_PIN_3

/*空气冷却*/    
#define MIST_PORT                   GPIOB
#define MIST_PIN                    GPIO_PIN_3   

void BspLimitGpioInit(void);
void BspLimitGpioIrqEnable(void);
void BspLimitGpioIrqDisable(void);
uint8_t BspLimitGetState(uint8_t axis);
uint8_t BspLimitGetAllState(uint8_t bit_select);

void BspStepGpioInit(void);
void BspSetGpioDirState(uint8_t mask);
void BspSetGpioStepState(uint8_t mask);
void BspSetGpioStepEnable(bool status);
uint8_t BspGetStepDirMask(uint8_t axis);
uint8_t BspGetStepGpioMask(uint8_t axis);

void hal_probe_gpio_init(void);
uint8_t hal_probe_gpio_read(void);

void hal_coolant_pin_init(void);
void set_coolant_flood(bool status);
void set_coolant_mist(bool status);
uint8_t get_coolant_flood(void);
uint8_t get_coolant_mist(void);

void BspGpioSet(GPIO_TypeDef *GPIOx, uint16_t PIN, GPIO_InitTypeDef *settings);

#ifdef __cplusplus
}
#endif

#endif
