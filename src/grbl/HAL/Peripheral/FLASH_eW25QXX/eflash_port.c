/*
 eflash_port.c

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "eflash_port.h"

/**********************************************
 *                    Flash HAL SPI 
 * 
 * ********************************************/

/* GPIO 引脚初始化 */
void flashSpiGpioInit(void)
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
#ifdef HAS_W25Qxx
    sFlash.info.flash_mode                  = sFLAHS_SPI_MODE;
    sFlash.info.flash_delay_time            = 100;   
    sFlash.info.flash_id                    = 0;
    sFlash.info.flash_size                  = 0;
    sFlash.flashSpiInit                     = spi_for_w25qxx_init;
    sFlash.flashSpiGpioInit                 = flashSpiGpioInit;
    sFlash.flashSpiReadWriteByte            = w25qxx_spi_read_write;
    // sFlash.flashIsTransFinish            = flashIsTransFinish;
    sFlash.flashDisableTrans                = w25qxx_spi_cs_disable;
    sFlash.flashEnableTrans                 = w25qxx_spi_cs_enabel;
#endif
}



