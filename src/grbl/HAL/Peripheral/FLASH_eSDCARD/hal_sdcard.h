#ifndef __hal_sdcard_h
#define __hal_sdcard_h

#include "../../../../main.h"

extern SPI_HandleTypeDef sd_hspi;

#ifdef SD_USE_SPI

    #define SD_CARD_SPI             BOARD_SD_SPI

    #ifdef SD_CARD_SPI
    
    #ifndef BOARD_SD_MISO_PORT
        #define SD_SPI_MISO_PORT    GPIOB
        #define SD_SPI_MISO_PIN     GPIO_PIN_14
    #else 
        #define SD_SPI_MISO_PORT    BOARD_SD_MISO_PORT
        #define SD_SPI_MISO_PIN     BOARD_SD_MISO_PIN
    #endif

    #ifndef BOARD_SD_MOSI_PORT
        #define SD_SPI_MOSI_PORT    GPIOB
        #define SD_SPI_MOSI_PIN     GPIO_PIN_15
    #else 
        #define SD_SPI_MOSI_PORT    BOARD_SD_MOSI_PORT
        #define SD_SPI_MOSI_PIN     BOARD_SD_MOSI_PIN
    #endif

    #ifndef BOARD_SD_SCK_PORT
        #define SD_SPI_SCK_PORT     GPIOB
        #define SD_SPI_SCK_PIN      GPIO_PIN_13
    #else
        #define SD_SPI_SCK_PORT     BOARD_SD_SCK_PORT
        #define SD_SPI_SCK_PIN      BOARD_SD_SCK_PIN
    #endif

    #ifndef BOARD_SD_CS_PORT
        #define SD_SPI_CS_PORT      GPIOB
        #define SD_SPI_CS_PIN       GPIO_PIN_12
    #else
        #define SD_SPI_CS_PORT      BOARD_SD_CS_PORT
        #define SD_SPI_CS_PIN       BOARD_SD_CS_PIN
    #endif

    #ifndef BOARD_SD_DET_PORT
        #define SD_DET_PORT         GPIOC
        #define SD_DET_PIN          GPIO_PIN_3
    #else
        #define SD_DET_PORT         BOARD_SD_DET_PORT
        #define SD_DET_PIN          BOARD_SD_DET_PIN
    #endif

    #ifndef _SD_GPIO_CLK_ENABLE
            #define _SD_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE();\
                                            __HAL_RCC_GPIOA_CLK_ENABLE();\
                                            __HAL_RCC_GPIOC_CLK_ENABLE();\
                                            __HAL_RCC_SPI1_CLK_ENABLE()
    #endif

    #ifndef _SD_GPIO_CLK_DISABLE
            #define _SD_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOB_CLK_DISABLE();\
                                            __HAL_RCC_GPIOC_CLK_DISABLE();\
                                            __HAL_RCC_SPI1_CLK_DISABLE()
    #endif

    #endif

#elif defined(SD_USE_SDIO)



#endif


typedef struct{
    uint8_t (*dev_sdcard_init)(void);
    uint8_t (*dev_sdcard_read_disk)(uint8_t*, uint32_t, uint8_t);
    uint8_t (*dev_sdcard_write_disk)(uint8_t*, uint32_t, uint8_t);
    uint8_t (*dev_sd_get_sector_count)(void);
}dev_sdcard_t;


void hal_sd_register(void);
void hal_sd_init(void);
void hal_sd_enable(void);
void hal_sd_disable(void);


#endif
