#include "w25qxx_port.h"

/**********************************************
 *                    W25QXX HAL SPI 
 * 
 * ********************************************/

/* GPIO 引脚初始化 */
void w25qxxSpiGpioInit(void)
{
  BspSpiGpioInit();
} 

void w25qxx_spi_cs_enabel(void) {
    BspSpiTranBegin(W25QXX_SPI_CS_GPIO, W25QXX_SPI_CS_PIN);
}

void w25qxx_spi_cs_disable(void) {
    BspSpiTranEnd(W25QXX_SPI_CS_GPIO, W25QXX_SPI_CS_PIN);
}

void w25qxxSpiRegiest(void) {
    sFlash.flash_mode               = sFLAHS_SPI_MODE;
    sFlash.flash_delay_time         = 10;   
    sFlash.flash_id                 = 0;
    sFlash.flash_size               = 0;
    sFlash.w25qxxSpiInit            = spi_for_w25qxx_init;
    sFlash.w25qxxSpiGpioInit        = w25qxxSpiGpioInit;
    sFlash.w25qxxSpiReadWriteByte   = w25qxx_spi_read_write;
    // sFlash.w25qxxIsTransFinish      = w25qxxIsTransFinish;
    sFlash.w25qxxDisableTrans       = w25qxx_spi_cs_disable;
    sFlash.w25qxxEnableTrans        = w25qxx_spi_cs_enabel;
}



