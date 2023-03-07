/*
 hal_spi.c

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "hal_spi.h"

/*******************************************************************************
 *                              W25QXX SPI Init
 * ****************************************************************************/
#ifdef HAS_W25Qxx
SPI_HandleTypeDef w25qxx_spi;
SPI_HandleTypeDef tft_spi;

void spi_for_w25qxx_init(void) {
    w25qxx_spi.Instance                 = W25QXX_SPI_PORT;
    w25qxx_spi.Init.BaudRatePrescaler   = W25QXX_SPEED;
    w25qxx_spi.Init.CLKPhase            = SPI_PHASE_2EDGE;
    w25qxx_spi.Init.CLKPolarity         = SPI_POLARITY_HIGH;
    w25qxx_spi.Init.CRCCalculation      = SPI_CRCCALCULATION_DISABLE;
    w25qxx_spi.Init.CRCPolynomial       = 7;
    w25qxx_spi.Init.DataSize            = SPI_DATASIZE_8BIT;
    w25qxx_spi.Init.Direction           = SPI_DIRECTION_2LINES;
    w25qxx_spi.Init.FirstBit            = SPI_FIRSTBIT_MSB;
    w25qxx_spi.Init.Mode                = SPI_MODE_MASTER;
    w25qxx_spi.Init.NSS                 = SPI_NSS_SOFT;
    w25qxx_spi.Init.TIMode              = SPI_TIMODE_DISABLE;
    
    BspSpiPortInit(&w25qxx_spi);
}

uint8_t w25qxx_spi_read_write(uint8_t data) {
    return BspSpiTransReceiveByte(&w25qxx_spi, data);
}

bool flashIsTransFinish() {

    return true;
}


#endif

/*******************************************************************************
 *                              TFT SPI Init
 * ****************************************************************************/
void spi_for_tft_init(void) {

    __HAL_RCC_SPI3_CLK_ENABLE();
}


/********************************************************************************/

void BspSpiPortInit(SPI_HandleTypeDef *spi) {

    BspSpiClkEnable(spi);

    if (HAL_SPI_Init(spi) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_SPI_ENABLE(spi);
}


#define _SPI_CLK(X)     __HAL_RCC_SPI##X##_CLK_ENABLE()
#define SPI_CLK(X)      _SPI_CLK(X) 

void BspSpiClkEnable(SPI_HandleTypeDef *spi) {

    if      (spi->Instance == SPI1)   SPI_CLK(1);
    else if (spi->Instance == SPI2)   SPI_CLK(2);
    else if (spi->Instance == SPI2)   SPI_CLK(3);
}

void BspSpiClkDisable(SPI_HandleTypeDef *spi) {

   
}

void BspSpiGpioInit(void) {

    GPIO_InitTypeDef settings = {
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_MEDIUM,
    };

    GPIO_InitTypeDef spi_settings = {
        .Alternate = W25QXX_PIN_AF,
        .Mode = GPIO_MODE_AF_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_MEDIUM,
    };

    BspGpioSet(W25QXX_SPI_SCK_GPIO, W25QXX_SPI_SCK_PIN, &spi_settings);
    BspGpioSet(W25QXX_SPI_MISO_GPIO, W25QXX_SPI_MISO_PIN, &spi_settings);
    BspGpioSet(W25QXX_SPI_MOSI_GPIO, W25QXX_SPI_MOSI_PIN, &spi_settings);
    BspGpioSet(W25QXX_SPI_CS_GPIO, W25QXX_SPI_CS_PIN, &settings);
}


/* 用于复用SPI时，两者配置不一样的切换  */
void BspSpiTranBeginSettings(SPI_HandleTypeDef *spi_settings) {
    HAL_SPI_Init(spi_settings);
}

/* 使能CS, 开始SPI传输                  */
void BspSpiTranBegin(GPIO_TypeDef *GPIOx, uint16_t PIN) {
    HAL_GPIO_WritePin(GPIOx, PIN, GPIO_PIN_RESET); 
}

/* 失能CS, 结束SPI传输                  */
void BspSpiTranEnd(GPIO_TypeDef *GPIOx, uint16_t PIN) {
    HAL_GPIO_WritePin(GPIOx, PIN, GPIO_PIN_SET); 
}

/* 单次接收或发送一个字节 */
uint8_t BspSpiTransReceiveByte(SPI_HandleTypeDef *spi, uint8_t wdata) {
    uint8_t rdata;
    HAL_SPI_TransmitReceive(spi, &wdata, &rdata, 1, 100);
    return rdata;
}

/* 单次接收或发送一个buff */
void BspSpiTransReceiveBuff(SPI_HandleTypeDef *spi, uint8_t *tdata, uint8_t *rdata, uint32_t num) {
    HAL_SPI_TransmitReceive(spi, tdata, rdata, num, 1000);
}










