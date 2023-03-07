/*
 pins_mks_dlc_lg0.h - For MKS LG0 V3

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __pins_mks_dlc_lg0_h
#define __pins_mks_dlc_lg0_h

#include "pins_def.h"
#include "../grbl_mb.h"

/* Board Info */
#define MCU_INFI_NAME                   "STM32F401RC"
#define MCU_INFO_FLASH                  "256K"
#define MCU_INFO_RAM                    "64K"

/* For Limit */
#define BOARD_LIMIT_X_PORT              GPIOC
#define BOARD_LIMIT_X_PIN               GPIO_PIN_9
#define BOARD_LIMIT_Y_PORT              GPIOC
#define BOARD_LIMIT_Y_PIN               GPIO_PIN_8
// #define BOARD_LIMIT_Z_PORT              GPIOD
// #define BOARD_LIMIT_Z_PIN               GPIO_PIN_12
#define BOARD_LIMIT_IRQ                 EXTI9_5_IRQn
#define BOARD_LIMIT_IRQnHANDLER         EXTI9_5_IRQHandler


/* For Motor axis */
#define BOARD_X_EN_PORT                 GPIOB
#define BOARD_X_EN_PIN                  GPIO_PIN_9
#define BOARD_Y_EN_PORT                 GPIOB           
#define BOARD_Y_EN_PIN                  GPIO_PIN_9
// #define BOARD_Z_EN_PORT                 GPIOB          
// #define BOARD_Z_EN_PIN                  GPIO_PIN_9

#define BOARD_X_STEP_PORT               GPIOB
#define BOARD_X_STEP_PIN                GPIO_PIN_8
#define BOARD_Y_STEP_PORT               GPIOB           
#define BOARD_Y_STEP_PIN                GPIO_PIN_6
// #define BOARD_Z_STEP_PORT               GPIOA          
// #define BOARD_Z_STEP_PIN                GPIO_PIN_8

#define BOARD_X_DIR_PORT                GPIOB
#define BOARD_X_DIR_PIN                 GPIO_PIN_7
#define BOARD_Y_DIR_PORT                GPIOB           
#define BOARD_Y_DIR_PIN                 GPIO_PIN_5
// #define BOARD_Z_DIR_PORT                GPIOI          
// #define BOARD_Z_DIR_PIN                 GPIO_PIN_7

/* Probe */
#define BOARD_PROBE_PORT                GPIOC
#define BOARD_PROBE_PIN                 GPIO_PIN_6

/* FLOOD */
#define BOARD_FLOOD_PORT                GPIOC
#define BOARD_FLOOD_PIN                 GPIO_PIN_10

/* MIST */
#define BOARD_MIST_PORT                 GPIOC
#define BOARD_MIST_PIN                  GPIO_PIN_10

/* For W25qxx */
#define W25QXX_SPI_PORT                 SPI1
#define W25QXX_SPI_SCK_GPIO             GPIOA
#define W25QXX_SPI_SCK_PIN              GPIO_PIN_5
#define W25QXX_SPI_MISO_GPIO            GPIOA
#define W25QXX_SPI_MISO_PIN             GPIO_PIN_6
#define W25QXX_SPI_MOSI_GPIO            GPIOA
#define W25QXX_SPI_MOSI_PIN             GPIO_PIN_7
#define W25QXX_SPI_CS_GPIO              GPIOA
#define W25QXX_SPI_CS_PIN               GPIO_PIN_4
#define W25QXX_PIN_AF                   GPIO_AF5_SPI1
#define W25QXX_SPEED                    SPI_BAUDRATEPRESCALER_4
#define W25QXX_SPI_CLK_ENABLE()         __HAL_RCC_SPI1_CLK_ENABLE()

/* For SDCard */
#define SD_USE_SPI
#define BOARD_SD_SPI                    SPI2
#define BOARD_SD_SCK_PORT               GPIOB
#define BOARD_SD_SCK_PIN                GPIO_PIN_13
#define BOARD_SD_MISO_PORT              GPIOB
#define BOARD_SD_MISO_PIN               GPIO_PIN_14
#define BOARD_SD_MOSI_PORT              GPIOB
#define BOARD_SD_MOSI_PIN               GPIO_PIN_15
#define BOARD_SD_CS_PORT                GPIOB
#define BOARD_SD_CS_PIN                 GPIO_PIN_12
#define BOARD_SD_DET_PORT               GPIOA
#define BOARD_SD_DET_PIN                GPIO_PIN_3
#define BOARD_SD_GPIO_AF                GPIO_AF5_SPI2

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
#define BOARD_SET_TIM                   4
#define BOARD_RESET_TIM                 5
#define BOARD_SET_TIM_FREQ              F_CPU / 1
#define BOARD_RESET_TIM_FREQ            F_CPU / 1
#define BOARD_LASER_TIM_PORT            3
#define BOARD_LASER_TIM_CH              TIM_CHANNEL_1
#define BOARD_LASER_PIN_AF              GPIO_AF2_TIM3
#define BOARD_LASER_OUT_PORT            GPIOB
#define BOARD_LASER_OUT_PIN             GPIO_PIN_4

#define EEPROM_START_ADDR               ADDR_FLASH_SECTOR_5  // 80D FC00  ADDR_FLASH_SECTOR_11
#define EEPROM_END_ADDR                 ((uint32_t)0x0803ffff)
#define FLASH_WRITE_SECTORS_WORD

#endif
