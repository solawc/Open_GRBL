#include "hal_spi.h"

/*******************************************************************************
 *                              W25QXX SPI Init
 * ****************************************************************************/
SPI_HandleTypeDef w25qxx_spi;
SPI_HandleTypeDef tft_spi;

void spi_for_w25qxx_init(void) {

    __HAL_RCC_SPI2_CLK_ENABLE();

    w25qxx_spi.Instance = W25QXX_SPI_PORT;
    w25qxx_spi.Init.BaudRatePrescaler = W25QXX_SPEED;
    w25qxx_spi.Init.CLKPhase = SPI_PHASE_1EDGE;
    w25qxx_spi.Init.CLKPolarity = SPI_POLARITY_LOW;
    w25qxx_spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    w25qxx_spi.Init.CRCPolynomial = 7;
    w25qxx_spi.Init.DataSize = SPI_DATASIZE_8BIT;
    w25qxx_spi.Init.Direction = SPI_DIRECTION_2LINES;
    w25qxx_spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    w25qxx_spi.Init.Mode = SPI_MODE_MASTER;
    w25qxx_spi.Init.NSS = SPI_NSS_SOFT;
    w25qxx_spi.Init.TIMode = SPI_TIMODE_DISABLE;
    if (HAL_SPI_Init(&w25qxx_spi) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_SPI_ENABLE(&w25qxx_spi);
}

uint8_t w25qxx_spi_read_write(uint8_t data) {
    uint8_t rdata = 0;    
    HAL_SPI_TransmitReceive(&w25qxx_spi, &data, &rdata, 1, 10);
    return rdata;
}

/*******************************************************************************
 *                              TFT SPI Init
 * ****************************************************************************/
void spi_for_tft_init(void) {

    __HAL_RCC_SPI3_CLK_ENABLE();
}

/*******************************************************************************
 *                              SDCard SPI Init
 * ****************************************************************************/





/*******************************************************************************
 *                              SPI Common
 * ****************************************************************************/





