#include "hal_sdcard.h"

#ifdef SD_CARD_SPI

SPI_HandleTypeDef sd_hspi;


static void sd_spi_pin_init(void) {

#ifdef HAS_SDCARD
    GPIO_InitTypeDef SPI_GPIO_Init;

    _SD_GPIO_CLK_ENABLE();                          // Enable SPI and GPIO Clock

    SPI_GPIO_Init.Alternate = BOARD_SD_GPIO_AF;     // GPIO_AF5_SPI2; 
    SPI_GPIO_Init.Mode = GPIO_MODE_AF_PP;
    SPI_GPIO_Init.Pin = SD_SPI_MISO_PIN|
                        SD_SPI_MOSI_PIN|
                        SD_SPI_SCK_PIN;
    SPI_GPIO_Init.Pull = GPIO_NOPULL;
    SPI_GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SD_SPI_SCK_PORT, &SPI_GPIO_Init);

    SPI_GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    SPI_GPIO_Init.Pin = SD_SPI_CS_PIN;
    SPI_GPIO_Init.Pull = GPIO_PULLUP;
    SPI_GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SD_SPI_CS_PORT, &SPI_GPIO_Init);

    SPI_GPIO_Init.Mode = GPIO_MODE_INPUT;
    SPI_GPIO_Init.Pin = SD_DET_PIN;
    SPI_GPIO_Init.Pull = GPIO_NOPULL;
    SPI_GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SD_DET_PORT, &SPI_GPIO_Init);
#endif
}

static void sd_spi_init(void) {

    sd_hspi.Instance = SD_CARD_SPI;
    sd_hspi.Init.BaudRatePrescaler = SD_SPI_LOW_SPEED;
    sd_hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
    sd_hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
    sd_hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    sd_hspi.Init.CRCPolynomial = 7;
    sd_hspi.Init.DataSize = SPI_DATASIZE_8BIT;
    sd_hspi.Init.Direction = SPI_DIRECTION_2LINES;
    sd_hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    sd_hspi.Init.Mode = SPI_MODE_MASTER;
    sd_hspi.Init.NSS = SPI_NSS_SOFT;
    sd_hspi.Init.TIMode = SPI_TIMODE_DISABLE;
    if (HAL_SPI_Init(&sd_hspi) != HAL_OK)
    {
        Error_Handler();
    }
    __HAL_SPI_ENABLE(&sd_hspi);
}

void hal_sd_enable(void) {
    HAL_GPIO_WritePin(SD_SPI_CS_PORT, SD_SPI_CS_PIN, GPIO_PIN_RESET);
}

void hal_sd_disable(void) {
    HAL_GPIO_WritePin(SD_SPI_CS_PORT, SD_SPI_CS_PIN, GPIO_PIN_SET);
}

uint8_t hal_sd_read_write_byte(uint8_t data) {
    uint8_t rxdata = 0;
    HAL_SPI_TransmitReceive(&sd_hspi, &data, &rxdata, 1, 1000);
    return rxdata;
}

void hal_sd_init(void) {
    sd_spi_pin_init();      // set gpio init
    sd_spi_init();          // set spi init
}

void hal_sd_set_speed(uint32_t SPI_BaudRatePrescaler) {
    sd_hspi.Init.BaudRatePrescaler = SPI_BaudRatePrescaler;
    HAL_SPI_Init(&sd_hspi);
    __HAL_SPI_ENABLE(&sd_hspi);
}

void hal_sd_deinit(void) {

    _SD_GPIO_CLK_DISABLE();
    HAL_SPI_DeInit(&sd_hspi);
}

uint8_t hal_sd_det_read(void) {

    if(GPIO_PIN_RESET == HAL_GPIO_ReadPin(SD_DET_PORT, SD_DET_PIN)) { return 0; }
    else return 1;
}

uint32_t hal_sd_spi_speed_get(SPI_HandleTypeDef *hspi) {

    uint16_t get_clk = (HAL_RCC_GetHCLKFreq() / 1000000) / 2; 

    uint8_t sd_spi_max_clk_div = get_clk / 12;

    if     ((sd_spi_max_clk_div<=2))     return SPI_BAUDRATEPRESCALER_2;       // && (sd_spi_min_clk_div<4) 
    else if((sd_spi_max_clk_div<=4) )    return SPI_BAUDRATEPRESCALER_4;       // && (sd_spi_min_clk_div<8) 
    else if((sd_spi_max_clk_div<=8) )    return SPI_BAUDRATEPRESCALER_8;       // && (sd_spi_min_clk_div<16)
    else if((sd_spi_max_clk_div<=16))    return SPI_BAUDRATEPRESCALER_16;      // && (sd_spi_min_clk_div<32)
    else if((sd_spi_max_clk_div<=32))    return SPI_BAUDRATEPRESCALER_32;      // && (sd_spi_min_clk_div<64)
    else    return SPI_BAUDRATEPRESCALER_256;
}

void hal_sd_register(void) {    

    hal_sd.sd_init = hal_sd_init;
    hal_sd.sd_trans_receive_data = hal_sd_read_write_byte;
    hal_sd.sd_trans_enable = hal_sd_enable;
    hal_sd.sd_trans_disable = hal_sd_disable;
    hal_sd.sd_set_speed = hal_sd_set_speed;
    hal_sd.sd_get_status = hal_sd_det_read;
    hal_sd.sd_trans_speed =  hal_sd_spi_speed_get(&sd_hspi);//  SPI_BAUDRATEPRESCALER_2;
    hal_sd.sd_slow_speed = SPI_BAUDRATEPRESCALER_256;

    hal_sd.sd_init();
}
#elif defined(SD_USE_SDIO)


#endif