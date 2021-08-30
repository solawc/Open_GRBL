#include "hal_w25qxx.h"


dev_spi_t dev_w25qxx_spi;
spi_setting_t dev_w25qxx_spi_set;

// __weak void hal_w25qxx_spi_init(void) {}

static void hal_w25qxx_spi_gpio_init(void) {

    GPIO_InitTypeDef GPIO_Init = {0};

    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_SPI5_CLK_ENABLE();

    GPIO_Init.Alternate = GPIO_AF5_SPI5;
    GPIO_Init.Mode =GPIO_MODE_AF_PP;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;

    GPIO_Init.Pin = W25QXX_SPI_SCK_PIN;
    HAL_GPIO_Init(W25QXX_SPI_SCK_GPIO, &GPIO_Init);

    GPIO_Init.Pin = W25QXX_SPI_MISO_PIN;
    HAL_GPIO_Init(W25QXX_SPI_MISO_GPIO, &GPIO_Init);

    GPIO_Init.Pin = W25QXX_SPI_MOSI_PIN;
    HAL_GPIO_Init(W25QXX_SPI_MOSI_GPIO, &GPIO_Init);

    GPIO_Init.Mode =GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pull = GPIO_PULLUP;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;
    GPIO_Init.Pin = W25QXX_SPI_CS_PIN;
    HAL_GPIO_Init(W25QXX_SPI_CS_GPIO, &GPIO_Init);
}

void hal_w25qxx_spi_init(void) {

    hal_w25qxx_spi_gpio_init();

    dev_w25qxx_spi_set.is_use_irq = false;
    dev_w25qxx_spi_set.spi_num = SPI_5;
    // dev_w25qxx_spi_set.spi_speed = SPI_DIV_8;
    dev_w25qxx_spi_set.spi_speed = 8;
    dev_w25qxx_spi_set.spi_mode_set = spi_mode_0;
    dev_w25qxx_spi_set.spi_date_size = size_8bit_date;
    dev_w25qxx_spi_set.spi_trans_mode = master_full_trans;
    dev_w25qxx_spi_set.spi_frist_bit = trans_msb_mode;
    hal_spi_begin(&dev_w25qxx_spi, &dev_w25qxx_spi_set);
}

bool is_write_had_finish(void) {

    if(__HAL_SPI_GET_FLAG(&dev_w25qxx_spi.hal_spi, SPI_FLAG_TXE) == RESET) {
        return true;
    }else {
        return false;
    }
}

bool is_read_had_finish(void) {
    if(__HAL_SPI_GET_FLAG(&dev_w25qxx_spi.hal_spi, SPI_FLAG_RXNE) == RESET) {
        return true;
    }else {
        return false;
    }
}

void w25qxx_enable(void) {
    HAL_GPIO_WritePin(W25QXX_SPI_CS_GPIO, W25QXX_SPI_CS_PIN, GPIO_PIN_RESET);
}

void w25qxx_disable(void) {
    HAL_GPIO_WritePin(W25QXX_SPI_CS_GPIO, W25QXX_SPI_CS_PIN, GPIO_PIN_SET);
}

uint8_t w25qxx_write_read(uint8_t byte) {
    return hal_spi_transfer_revice_byte(&dev_w25qxx_spi, byte);
}


/*--------------------------------------------------------------------------------------------*/

uint16_t w25qxx_read_write_cb(dev_spi_t *dev, uint16_t data) {
    uint16_t rdata = 0;
    rdata = dev->dev_spi_read_write_byte(data);
    return rdata;
}

uint16_t w25qxx_read_write_byte(uint16_t wdata) {
    return w25qxx_read_write_cb(&dev_w25qxx_spi, wdata);
}

void w25qxx_init(void) {
    dev_w25qxx_spi.__spi_intrans = false;
    dev_w25qxx_spi.is_use_dma = false;
    dev_w25qxx_spi.dev_spi_init_cb = hal_w25qxx_spi_init;
    dev_w25qxx_spi.dev_spi_read_write_byte = w25qxx_write_read;
    hal_spi_register(&dev_w25qxx_spi);
}

uint32_t w25qxx_read_id(void) {
    uint32_t id = 0;
    w25qxx_enable();
    w25qxx_read_write_byte(W25X_JedecDeviceID);
    id |= w25qxx_read_write_byte(0xff) << 16;
    id |= w25qxx_read_write_byte(0xff) << 8;
    id |= w25qxx_read_write_byte(0xff) << 0;
    w25qxx_disable();
    return id;
}
