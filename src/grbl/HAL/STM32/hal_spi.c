#include "hal_spi.h"

/*******************************************************************************
 *                              W25QXX SPI Init
 * ****************************************************************************/
#ifdef HAS_W25Qxx
SPI_HandleTypeDef w25qxx_spi;
SPI_HandleTypeDef tft_spi;
NFLASH_t sFlash;

void w25qxx_spi_cs_enabel(void) {
    HAL_GPIO_WritePin(W25QXX_SPI_CS_GPIO, W25QXX_SPI_CS_PIN, GPIO_PIN_RESET);
}

void w25qxx_spi_cs_disable(void) {
    HAL_GPIO_WritePin(W25QXX_SPI_CS_GPIO, W25QXX_SPI_CS_PIN, GPIO_PIN_SET);
}

void w25qxx_spi_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_Init = {0};

    GPIO_Init.Alternate = W25QXX_PIN_AF;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;

    GPIO_Init.Pin = W25QXX_SPI_SCK_PIN;
    HAL_GPIO_Init(W25QXX_SPI_SCK_GPIO, &GPIO_Init);

    GPIO_Init.Pin = W25QXX_SPI_MISO_PIN;
    HAL_GPIO_Init(W25QXX_SPI_MISO_GPIO, &GPIO_Init);

    GPIO_Init.Pin = W25QXX_SPI_MOSI_PIN;
    HAL_GPIO_Init(W25QXX_SPI_MOSI_GPIO, &GPIO_Init);

    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pull = GPIO_PULLUP;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;
    GPIO_Init.Pin = W25QXX_SPI_CS_PIN;
    HAL_GPIO_Init(W25QXX_SPI_CS_GPIO, &GPIO_Init);
} 

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

bool w25qxx_is_trans_finish() {

    return true;
}

void w25qxx_spi_regiest() {
    sFlash.flash_mode = sFLAHS_SPI_MODE;
    sFlash.flash_delay_time = 10;   
    sFlash.flash_id = 0;
    sFlash.flash_size = 0;
    sFlash.w25qxx_spi_init = spi_for_w25qxx_init;
    sFlash.w25qxx_spi_gpio_init = w25qxx_spi_gpio_init;
    sFlash.w25qxx_spi_read_write_byte = w25qxx_spi_read_write;
    sFlash.w25qxx_is_trans_finish = w25qxx_is_trans_finish;
    sFlash.w25qxx_disable_trans = w25qxx_spi_cs_disable;
    sFlash.w25qxx_enable_trans = w25qxx_spi_cs_enabel;
}
#endif

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





