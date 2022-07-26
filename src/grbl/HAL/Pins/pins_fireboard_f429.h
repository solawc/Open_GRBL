#ifndef __pins_fireboard_f429_h
#define __pins_fireboard_f429_h

#include "pins_def.h"

#define USE_MCU_FPU

/* For Limit */
#define BOARD_LIMIT_X_PORT              GPIOD
#define BOARD_LIMIT_X_PIN               GPIO_PIN_4
#define BOARD_LIMIT_Y_PORT              GPIOD
#define BOARD_LIMIT_Y_PIN               GPIO_PIN_11
#define BOARD_LIMIT_Z_PORT              GPIOD
#define BOARD_LIMIT_Z_PIN               GPIO_PIN_12
#define BOARD_LIMIT_IRQ                 EXTI0_IRQn
#define BOARD_LIMIT_IRQnHANDLER         EXTI0_IRQHandler

/* For Motor axis */
#define BOARD_X_EN_PORT                 GPIOI
#define BOARD_X_EN_PIN                  GPIO_PIN_8
#define BOARD_Y_EN_PORT                 GPIOI           
#define BOARD_Y_EN_PIN                  GPIO_PIN_8
#define BOARD_Z_EN_PORT                 GPIOI          
#define BOARD_Z_EN_PIN                  GPIO_PIN_8
#define BOARD_X_STEP_PORT               GPIOA
#define BOARD_X_STEP_PIN                GPIO_PIN_4
#define BOARD_Y_STEP_PORT               GPIOA           
#define BOARD_Y_STEP_PIN                GPIO_PIN_6
#define BOARD_Z_STEP_PORT               GPIOA          
#define BOARD_Z_STEP_PIN                GPIO_PIN_8
#define BOARD_X_DIR_PORT                GPIOI
#define BOARD_X_DIR_PIN                 GPIO_PIN_5
#define BOARD_Y_DIR_PORT                GPIOI           
#define BOARD_Y_DIR_PIN                 GPIO_PIN_6
#define BOARD_Z_DIR_PORT                GPIOI          
#define BOARD_Z_DIR_PIN                 GPIO_PIN_7

/* Probe */
#define BOARD_PROBE_PORT                GPIOB
#define BOARD_PROBE_PIN                 GPIO_PIN_11

/* FLOOD */
#define BOARD_FLOOD_PORT                GPIOB
#define BOARD_FLOOD_PIN                 GPIO_PIN_3

/* MIST */
#define BOARD_MIST_PORT                 GPIOB
#define BOARD_MIST_PIN                  GPIO_PIN_3

/* FLAME */
// #define BOARD_FLAME_PORT                
// #define BOARD_FLAME_PIN

/* For W25qxx */
#define W25QXX_SPI_PORT                 SPI5
#define W25QXX_SPI_SCK_GPIO             GPIOF
#define W25QXX_SPI_SCK_PIN              GPIO_PIN_7
#define W25QXX_SPI_MISO_GPIO            GPIOF
#define W25QXX_SPI_MISO_PIN             GPIO_PIN_8
#define W25QXX_SPI_MOSI_GPIO            GPIOF
#define W25QXX_SPI_MOSI_PIN             GPIO_PIN_9
#define W25QXX_SPI_CS_GPIO              GPIOF
#define W25QXX_SPI_CS_PIN               GPIO_PIN_6
#define W25QXX_PIN_AF                   GPIO_AF5_SPI5
#define W25QXX_SPEED                    SPI_BAUDRATEPRESCALER_4

/* For SDCard */
#define SD_USE_SDIO

/* For Serial UART */
#define  __HAL_UART_CLK(uart)	        __HAL_RCC_##uart##_CLK_ENABLE()
#define  UART_IRQn(uart)                uart##_IRQn

#define BOARD_UART                      USART1
#define BOARD_UART_IRQ                  UART_IRQn(USART1)
#define BOARD_UART_CLK_ENABLE()         __HAL_UART_CLK(USART1)
#define BOARD_UART_IRQnHANDLER          USART1_IRQHandler
#define BOARD_UART_TX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE();
#define BOARD_UART_RX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE();
#define BOARD_UART_TX_PORT              GPIOA
#define BOARD_UART_TX_PIN               GPIO_PIN_9
#define BOARD_UART_RX_PORT              GPIOA
#define BOARD_UART_RX_PIN               GPIO_PIN_10
#define BOARD_UART_AF_MODE              GPIO_AF7_USART1
#define BOARD_UART_RX_FLAG              __HAL_UART_GET_FLAG(&laser_uart, UART_FLAG_RXNE) == SET

/* For timer use */
#define BOARD_SETP_SET_TIM              TIM3
#define BOARD_SETP_RESET_TIM            TIM4
#define BOARD_STEP_SET_TIMER            STEP_SET_TIM
#define BOARD_STEP_RESET_TIMER          STEP_RESET_TIM
#define BOARD_SET_TIM_IRQn              TIM3_IRQn
#define BOARD_RESET_TIM_IRQn            TIM4_IRQn
#define BOARD_SET_TIM_CLK_ENABLED()     __HAL_RCC_TIM3_CLK_ENABLE()
#define BOARD_RESET_TIM_CLK_ENABLED()   __HAL_RCC_TIM4_CLK_ENABLE()
#define BOARD_STEP_SET_HANDLER          TIM3_IRQHandler
#define BOARD_STEP_RESET_HANDLER        TIM4_IRQHandler
#define BOARD_LASER_TIM_PORT            TIM1
#define BOARD_LASER_TIM_CH              TIM_CHANNEL_2
#define BOARD_LASER_PIN_AF              GPIO_AF1_TIM1
#define BOARD_LASER_OUT_PORT            GPIOB
#define BOARD_LASER_OUT_PIN             GPIO_PIN_6
#define BOARD_LASER_OUT_CLK()           __HAL_RCC_TIM4_CLK_ENABLE()
#define BOARD_LASER_OUT_PIN_CLK()       __HAL_RCC_GPIOB_CLK_ENABLE()

















#endif
