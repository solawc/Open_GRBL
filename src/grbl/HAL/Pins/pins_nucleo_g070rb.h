/*
 pins_nucleo_g070rb.h - For STM32 NUCLEO Board(STM32G070RB)

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __pins_nucleo_g070rb_h
#define __pins_nucleo_g070rb_h

#include "pins_def.h"

/* For Limit */
#define BOARD_LIMIT_X_PORT              GPIOD
#define BOARD_LIMIT_X_PIN               GPIO_PIN_3
#define BOARD_LIMIT_Y_PORT              GPIOD
#define BOARD_LIMIT_Y_PIN               GPIO_PIN_2
#define BOARD_LIMIT_Z_PORT              GPIOD
#define BOARD_LIMIT_Z_PIN               GPIO_PIN_2
#define BOARD_LIMIT_IRQ                 EXTI2_3_IRQn
#define BOARD_LIMIT_IRQnHANDLER         EXTI2_3_IRQHandler

/* For Motor axis */
#define BOARD_X_EN_PORT                 GPIOC
#define BOARD_X_EN_PIN                  GPIO_PIN_15
#define BOARD_Y_EN_PORT                 GPIOB           
#define BOARD_Y_EN_PIN                  GPIO_PIN_9
#define BOARD_Z_EN_PORT                 GPIOC          
#define BOARD_Z_EN_PIN                  GPIO_PIN_15
#define BOARD_X_STEP_PORT               GPIOC
#define BOARD_X_STEP_PIN                GPIO_PIN_14
#define BOARD_Y_STEP_PORT               GPIOB           
#define BOARD_Y_STEP_PIN                GPIO_PIN_8
#define BOARD_Z_STEP_PORT               GPIOB          
#define BOARD_Z_STEP_PIN                GPIO_PIN_9
#define BOARD_X_DIR_PORT                GPIOC
#define BOARD_X_DIR_PIN                 GPIO_PIN_13
#define BOARD_Y_DIR_PORT                GPIOB           
#define BOARD_Y_DIR_PIN                 GPIO_PIN_7
#define BOARD_Z_DIR_PORT                GPIOB          
#define BOARD_Z_DIR_PIN                 GPIO_PIN_8

/* Laser */
#define BOARD_LASER_PORT                GPIOB
#define BOARD_LASER_PIN                 GPIO_PIN_7

/* Probe */
#define BOARD_PROBE_PORT                GPIOB
#define BOARD_PROBE_PIN                 GPIO_PIN_11

/* FLOOD */
#define BOARD_FLOOD_PORT                GPIOB
#define BOARD_FLOOD_PIN                 GPIO_PIN_3

/* MIST */
#define BOARD_MIST_PORT                 GPIOB
#define BOARD_MIST_PIN                  GPIO_PIN_3

/* For SDCard */
#define SD_USE_SPI
#define BOARD_SD_SPI                    SPI1
#define BOARD_SD_SCK_PORT               GPIOA
#define BOARD_SD_SCK_PIN                GPIO_PIN_5
#define BOARD_SD_MISO_PORT              GPIOA
#define BOARD_SD_MISO_PIN               GPIO_PIN_6
#define BOARD_SD_MOSI_PORT              GPIOA
#define BOARD_SD_MOSI_PIN               GPIO_PIN_7
#define BOARD_SD_CS_PORT                GPIOA
#define BOARD_SD_CS_PIN                 GPIO_PIN_4
#define BOARD_SD_DET_PORT               GPIOB
#define BOARD_SD_DET_PIN                GPIO_PIN_0
#define BOARD_SD_GPIO_AF                GPIO_AF0_SPI1

/* For Serial UART */
#define  __HAL_UART_CLK(uart)	        __HAL_RCC_##uart##_CLK_ENABLE()
#define  UART_IRQn(uart)                uart##_IRQn

#define BOARD_UART                      USART2
#define BOARD_UART_IRQ                  UART_IRQn(USART2)
#define BOARD_UART_CLK_ENABLE()         __HAL_UART_CLK(USART2)
#define BOARD_UART_IRQnHANDLER          USART2_IRQHandler
#define BOARD_UART_TX_PORT              GPIOA
#define BOARD_UART_TX_PIN               GPIO_PIN_2
#define BOARD_UART_RX_PORT              GPIOA
#define BOARD_UART_RX_PIN               GPIO_PIN_3
#define BOARD_UART_AF_MODE              GPIO_AF1_USART2
#define BOARD_UART_RX_FLAG              __HAL_UART_GET_FLAG(&laser_uart, UART_FLAG_RXNE) == SET

/* For timer use */
#define BOARD_SET_TIM                   6
#define BOARD_RESET_TIM                 7
#define BOARD_SET_TIM_FREQ              F_CPU / 1
#define BOARD_RESET_TIM_FREQ            F_CPU / 1
#define BOARD_LASER_TIM_PORT            1
#define BOARD_LASER_TIM_CH              TIM_CHANNEL_2
#define BOARD_LASER_PIN_AF              GPIO_AF1_TIM1
#define BOARD_LASER_OUT_PORT            GPIOB
#define BOARD_LASER_OUT_PIN             GPIO_PIN_6

#endif