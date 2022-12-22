/*
 pins_mks_nano_v3.h - For MKS Robin Nano V3 Board(STM32F407VE)

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __pins_mks_nano_v3_h
#define __pins_mks_nano_v3_h

#include "pins_def.h"
#include "../grbl_mb.h"

#if MB_BOARD == BOARD_MKS_ROBIN_NANO_V3

/* Board Info */
#define MCU_INFI_NAME                   "STM32F407VE"
#define MCU_INFO_FLASH                  "512K"
#define MCU_INFO_RAM                    "196K"

/* For Limit */
#define BOARD_LIMIT_X_PORT              GPIOA
#define BOARD_LIMIT_X_PIN               GPIO_PIN_15
#define BOARD_LIMIT_Y_PORT              GPIOD
#define BOARD_LIMIT_Y_PIN               GPIO_PIN_2
#define BOARD_LIMIT_Z_PORT              GPIOC
#define BOARD_LIMIT_Z_PIN               GPIO_PIN_8
#define BOARD_LIMIT_IRQ                 EXTI9_5_IRQn  
#define BOARD_LIMIT_IRQnHANDLER         EXTI9_5_IRQHandler

/* For Motor axis */
#define BOARD_X_EN_PORT                 GPIOE
#define BOARD_X_EN_PIN                  GPIO_PIN_4
#define BOARD_Y_EN_PORT                 GPIOE           
#define BOARD_Y_EN_PIN                  GPIO_PIN_1
#define BOARD_Z_EN_PORT                 GPIOB          
#define BOARD_Z_EN_PIN                  GPIO_PIN_8

#define BOARD_X_STEP_PORT               GPIOE
#define BOARD_X_STEP_PIN                GPIO_PIN_3
#define BOARD_Y_STEP_PORT               GPIOE          
#define BOARD_Y_STEP_PIN                GPIO_PIN_0
#define BOARD_Z_STEP_PORT               GPIOB          
#define BOARD_Z_STEP_PIN                GPIO_PIN_5

#define BOARD_X_DIR_PORT                GPIOE
#define BOARD_X_DIR_PIN                 GPIO_PIN_2
#define BOARD_Y_DIR_PORT                GPIOB           
#define BOARD_Y_DIR_PIN                 GPIO_PIN_9
#define BOARD_Z_DIR_PORT                GPIOB          
#define BOARD_Z_DIR_PIN                 GPIO_PIN_4

/* Probe */
#define BOARD_PROBE_PORT                GPIOA
#define BOARD_PROBE_PIN                 GPIO_PIN_8

/* FLOOD */
#define BOARD_FLOOD_PORT                GPIOB
#define BOARD_FLOOD_PIN                 GPIO_PIN_1

/* MIST */
#define BOARD_MIST_PORT                 GPIOB
#define BOARD_MIST_PIN                  GPIO_PIN_1

/* For W25qxx */
#define W25QXX_SPI_PORT                 SPI2
#define W25QXX_SPI_SCK_GPIO             GPIOB
#define W25QXX_SPI_SCK_PIN              GPIO_PIN_13
#define W25QXX_SPI_MISO_GPIO            GPIOC
#define W25QXX_SPI_MISO_PIN             GPIO_PIN_2
#define W25QXX_SPI_MOSI_GPIO            GPIOC
#define W25QXX_SPI_MOSI_PIN             GPIO_PIN_3
#define W25QXX_SPI_CS_GPIO              GPIOB
#define W25QXX_SPI_CS_PIN               GPIO_PIN_12
#define W25QXX_PIN_AF                   GPIO_AF5_SPI2
#define W25QXX_SPEED                    SPI_BAUDRATEPRESCALER_2
#define W25QXX_SPI_CLK_ENABLE()         __HAL_RCC_SPI2_CLK_ENABLE()

/* For SDCard */
#define SD_USE_SPI
#define BOARD_SD_SPI                    SPI3
#define BOARD_SD_SCK_PORT               GPIOC
#define BOARD_SD_SCK_PIN                GPIO_PIN_10
#define BOARD_SD_MISO_PORT              GPIOC
#define BOARD_SD_MISO_PIN               GPIO_PIN_11
#define BOARD_SD_MOSI_PORT              GPIOC
#define BOARD_SD_MOSI_PIN               GPIO_PIN_12
#define BOARD_SD_CS_PORT                GPIOC
#define BOARD_SD_CS_PIN                 GPIO_PIN_9
#define BOARD_SD_DET_PORT               GPIOD
#define BOARD_SD_DET_PIN                GPIO_PIN_12
#define BOARD_SD_GPIO_AF                GPIO_AF6_SPI3

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
#define BOARD_LASER_TIM_PORT            3
#define BOARD_LASER_TIM_CH              TIM_CHANNEL_1
#define BOARD_LASER_PIN_AF              GPIO_AF2_TIM3
#define BOARD_LASER_OUT_PORT            GPIOB
#define BOARD_LASER_OUT_PIN             GPIO_PIN_0


#define I2C_EEPEOM                      
#ifdef I2C_EEPEOM
    #define EEPROM_I2C                  1                               // I2C1
    #define EEPROM_I2C_CLK              __HAL_RCC_I2C1_CLK_ENABLE()
    #define EEPROM_I2C_SCL_PORT         GPIOB
    #define EEPROM_I2C_SCL_PIN          GPIO_PIN_6
    #define EEPROM_I2C_SDA_PORT         GPIOB
    #define EEPROM_I2C_SDA_PIN          GPIO_PIN_7

    // #define EEPROM_ADDR                 
    // #define EEPROM_SIZE
#endif

#ifndef I2C_EEPEOM
#define EEPROM_START_ADDR               ADDR_FLASH_SECTOR_6     
#define EEPROM_END_ADDR                 ((uint32_t)0x0803ffff)
#define FLASH_WRITE_SECTORS_WORD
#endif


#endif

#endif