/*
 hal_spi.h

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef hal_spi_h
#define hal_spi_h

#include "../../../main.h"

extern SPI_HandleTypeDef w25qxx_spi;

typedef enum {

    SPI_MODE_0 = 0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3

}spi_mode_t;

typedef enum {
    SPI_LINE_TX = 0,
    SPI_LINE_RX,
    SPI_LINE_TX_RX,
}spi_line_mode_t;


typedef struct {

    SPI_HandleTypeDef   obj;
    SPI_TypeDef         *spi_port;

    GPIO_TypeDef        *sck_port;
    GPIO_TypeDef        *miso_port;
    GPIO_TypeDef        *mosi_port;
    GPIO_TypeDef        *cs_port;

    uint16_t            sck_pin;
    uint16_t            miso_pin;
    uint16_t            mosi_pin;
    uint16_t            cs_pin;
    uint32_t            _af;

    uint32_t            _spi_baud;
    uint32_t            _clk_phase;
    uint32_t            _clk_polarity;
    uint32_t            _data_size;
    
}hal_spi_t;




uint8_t w25qxx_spi_read_write(uint8_t data);
void spi_for_w25qxx_init(void);
void spi_for_tft_init(void);


void BspSpiGpioInit(void);
void BspSpiPortInit(SPI_HandleTypeDef *spi);
void BspSpiClkEnable(SPI_HandleTypeDef *spi);
void BspSpiClkDisable(SPI_HandleTypeDef *spi);


void BspSpiTranBeginSettings(SPI_HandleTypeDef *spi_settings);
void BspSpiTranBegin(GPIO_TypeDef *GPIOx, uint16_t PIN);
void BspSpiTranEnd(GPIO_TypeDef *GPIOx, uint16_t PIN);
uint8_t BspSpiTransReceiveByte(SPI_HandleTypeDef *spi, uint8_t wdata);
void BspSpiTransReceiveBuff(SPI_HandleTypeDef *spi, uint8_t *tdata, uint8_t *rdata, uint32_t num);


#endif

