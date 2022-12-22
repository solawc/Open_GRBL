/*
 pins_direboard_f429.h - For Fire Board STM32F429IG V2

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __pins_fireboard_f429_h
#define __pins_fireboard_f429_h

#include "pins_def.h"
#include "../grbl_mb.h"

#if MB_BOARD == BOARD_FIRE_BOARD_F429

/* Enable FPU */
#define USE_MCU_FPU

/* Board Info */
#define MCU_INFI_NAME                   "STM32F429IG"
#define MCU_INFO_FLASH                  "1024K"
#define MCU_INFO_RAM                    "512K"

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
#define W25QXX_SPI_CLK_ENABLE()         __HAL_RCC_SPI5_CLK_ENABLE()

/* For SDCard */
#define SD_USE_SDIO

/* For Serial UART */
#define  __HAL_UART_CLK(uart)	        __HAL_RCC_##uart##_CLK_ENABLE()
#define  UART_IRQn(uart)                uart##_IRQn

#define BOARD_UART                      USART1
#define BOARD_UART_IRQ                  UART_IRQn(USART1)
#define BOARD_UART_CLK_ENABLE()         __HAL_UART_CLK(USART1)
#define BOARD_UART_IRQnHANDLER          USART1_IRQHandler
#define BOARD_UART_TX_PORT              GPIOA
#define BOARD_UART_TX_PIN               GPIO_PIN_9
#define BOARD_UART_RX_PORT              GPIOA
#define BOARD_UART_RX_PIN               GPIO_PIN_10
#define BOARD_UART_AF_MODE              GPIO_AF7_USART1
#define BOARD_UART_RX_FLAG              __HAL_UART_GET_FLAG(&laser_uart, UART_FLAG_RXNE) == SET

/* For timer use */
#define BOARD_SET_TIM                   3
#define BOARD_RESET_TIM                 4
#define BOARD_SET_TIM_FREQ              F_CPU / 2
#define BOARD_RESET_TIM_FREQ            F_CPU / 2
#define BOARD_LASER_TIM_PORT            1
#define BOARD_LASER_TIM_CH              TIM_CHANNEL_2
#define BOARD_LASER_PIN_AF              GPIO_AF1_TIM1
#define BOARD_LASER_OUT_PORT            GPIOB
#define BOARD_LASER_OUT_PIN             GPIO_PIN_6

/* For EEPROM */
#define EEPROM_START_ADDR               ADDR_FLASH_SECTOR_23  // 80D FC00  ADDR_FLASH_SECTOR_11
#define EEPROM_END_ADDR                 ((uint32_t)0x080fffff)
#define FLASH_WRITE_SECTORS_WORD

#endif /* MB_BOARD */

#endif
