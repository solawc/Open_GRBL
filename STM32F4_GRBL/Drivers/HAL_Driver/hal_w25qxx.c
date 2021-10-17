#include "hal_w25qxx.h"

dev_spi_t dev_w25qxx_spi;
spi_setting_t dev_w25qxx_spi_set;
spi_setting_t dev_sdcard_set;

// __weak void hal_w25qxx_spi_init(void) {}

NFLASH_t sFlash;

static void hal_w25qxx_spi_gpio_init(void)
{

    GPIO_InitTypeDef GPIO_Init = {0};

    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_SPI5_CLK_ENABLE();

    GPIO_Init.Alternate = GPIO_AF5_SPI5;
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

void hal_w25qxx_spi_init(void)
{   
    sFlash.flash_mode = sFLAHS_SPI_MODE;
    sFlash.flash_delay_time = 10;
    sFlash.flash_id = 0;
    sFlash.flash_size = 0;

    if(sFlash.flash_mode == sFLAHS_SPI_MODE) {
        hal_w25qxx_spi_gpio_init();
        dev_w25qxx_spi_set.is_use_irq = false;
        dev_w25qxx_spi_set.spi_num = SPI_5;
        dev_w25qxx_spi_set.spi_speed = 8;
        dev_w25qxx_spi_set.spi_mode_set = spi_mode_0;
        dev_w25qxx_spi_set.spi_date_size = size_8bit_date;
        dev_w25qxx_spi_set.spi_trans_mode = master_full_trans;
        dev_w25qxx_spi_set.spi_frist_bit = trans_msb_mode;
        hal_spi_begin(&dev_w25qxx_spi, &dev_w25qxx_spi_set);
    }else {

    }    
}

bool is_write_had_finish(void)
{

    if (__HAL_SPI_GET_FLAG(&dev_w25qxx_spi.hal_spi, SPI_FLAG_TXE) == RESET)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_read_had_finish(void)
{
    if (__HAL_SPI_GET_FLAG(&dev_w25qxx_spi.hal_spi, SPI_FLAG_RXNE) == RESET)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void w25qxx_enable(void)
{
    HAL_GPIO_WritePin(W25QXX_SPI_CS_GPIO, W25QXX_SPI_CS_PIN, GPIO_PIN_RESET);
}

void w25qxx_disable(void)
{
    HAL_GPIO_WritePin(W25QXX_SPI_CS_GPIO, W25QXX_SPI_CS_PIN, GPIO_PIN_SET);
}

uint8_t w25qxx_write_read_8(uint8_t byte)
{
    return hal_spi_transfer_revice_byte(&dev_w25qxx_spi, byte);
}

uint16_t w25qxx_write_read_16(uint16_t byte)
{
    return hal_spi_transfer_revice_byte(&dev_w25qxx_spi, byte);
}

/*--------------------------------------------------------------------------------------------*/

uint16_t w25qxx_read_write_cb(dev_spi_t *dev, uint16_t data)
{
    uint16_t rdata = 0;
    rdata = dev->dev_spi_read_write_byte(data);
    return rdata;
}

uint16_t w25qxx_read_write_byte(uint16_t wdata)
{
    return w25qxx_read_write_cb(&dev_w25qxx_spi, wdata);
}

void w25qxx_init(void)
{
    dev_w25qxx_spi.__spi_intrans = false;
    dev_w25qxx_spi.is_use_dma = false;
    dev_w25qxx_spi.dev_spi_init_cb = hal_w25qxx_spi_init;
    dev_w25qxx_spi.dev_spi_read_write_byte = w25qxx_write_read_16;
    hal_spi_register(&dev_w25qxx_spi);

    sFlash.flash_id =  w25qxx_read_id();

    switch(sFlash.flash_id) {
        case sFLASH_ID_X16: sFlash.flash_size = (16 / 8) *1024; break;
        case sFLASH_ID_16: sFlash.flash_size = (16 / 8) *1024; break;
        case sFLASH_ID_64: sFlash.flash_size = (64 / 8) *1024; break;
        case sFLASH_ID_128: sFlash.flash_size = (128 / 8) *1024; break;
        case sFLASH_ID_256: sFlash.flash_size = (258 / 8) *1024; break;
        default: sFlash.flash_size = 0; break;
    }
}

uint32_t w25qxx_read_id(void)
{
    uint32_t id = 0;
    w25qxx_enable();
    w25qxx_read_write_byte(W25X_JedecDeviceID);
    id |= w25qxx_read_write_byte(0xff) << 16;
    id |= w25qxx_read_write_byte(0xff) << 8;
    id |= w25qxx_read_write_byte(0xff) << 0;
    w25qxx_disable();
    return id;
}

uint8_t w25qxx_read_sr_reg(uint8_t reg)
{
    uint8_t byte = 0, command = 0;
    switch (reg)
    {
    case 1:
        command = W25X_ReadStatusReg;
        break;
    case 2:
        command = W25X_ReadStatusReg2;
        break;
    case 3:
        command = W25X_ReadStatusReg3;
        break;
    default:
        command = W25X_ReadStatusReg;
        break;
    }
    w25qxx_enable();
    w25qxx_read_write_byte(command);
    byte = w25qxx_read_write_byte(0Xff);
    w25qxx_disable();
    return byte;
}

void w25qxx_write_sr_reg(uint8_t reg, uint8_t sr)
{
    uint8_t command = 0;
    switch (reg)
    {
    case 1:
        command = W25X_ReadStatusReg;
        break;
    case 2:
        command = W25X_ReadStatusReg2;
        break;
    case 3:
        command = W25X_ReadStatusReg3;
        break;
    default:
        command = W25X_ReadStatusReg;
        break;
    }
    w25qxx_enable();
    w25qxx_read_write_byte(command);
    w25qxx_read_write_byte(sr);
    w25qxx_disable();
}

void w25qxx_write_enable(void)
{
    w25qxx_enable();
    w25qxx_read_write_byte(W25X_WriteEnable);
    w25qxx_disable();
}

void w25qxx_write_disable(void)
{
    w25qxx_enable();
    w25qxx_read_write_byte(W25X_WriteDisable);
    w25qxx_disable();
}

void w25qxx_wait_busy(void)
{
    while ((w25qxx_read_sr_reg(1) & 0x01) == 0x01); // 等待BUSY位清空
}

void w25qxx_read_buff(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
    uint16_t i;
    w25qxx_enable();                                     //使能器件
    w25qxx_read_write_byte(W25X_ReadData);               //发送读取命令
    w25qxx_read_write_byte((uint8_t)((ReadAddr) >> 16)); //发送24bit地址
    w25qxx_read_write_byte((uint8_t)((ReadAddr) >> 8));
    w25qxx_read_write_byte((uint8_t)ReadAddr);
    for (i = 0; i < NumByteToRead; i++)
    {
        pBuffer[i] = w25qxx_read_write_byte(0XFF); //循环读数
    }
    w25qxx_disable();
}

void w15qxx_write_page(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t i;
    w25qxx_write_enable();                    
    w25qxx_enable();                          
    w25qxx_read_write_byte(W25X_PageProgram); 

    w25qxx_read_write_byte((uint8_t)((WriteAddr) >> 16)); 
    w25qxx_read_write_byte((uint8_t)((WriteAddr) >> 8));
    w25qxx_read_write_byte((uint8_t)WriteAddr);
    for (i = 0; i < NumByteToWrite; i++)
    {
        w25qxx_read_write_byte(pBuffer[i]); 
    }
    w25qxx_disable();
    w25qxx_wait_busy(); 
}

void w25qxx_write_no_check(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t pageremain;
    pageremain = 256 - WriteAddr % 256; 
    if (NumByteToWrite <= pageremain)
        pageremain = NumByteToWrite;
    while (1)
    {
        w15qxx_write_page(pBuffer, WriteAddr, pageremain);
        if (NumByteToWrite == pageremain)
            break; 
        else       
        {
            pBuffer += pageremain;
            WriteAddr += pageremain;

            NumByteToWrite -= pageremain; 
            if (NumByteToWrite > 256)
                pageremain = 256; 
            else
                pageremain = NumByteToWrite; 
        }
    };
}

void w25qxx_erase_chip(void)   
{                                   
    w25qxx_write_enable();                
    w25qxx_wait_busy();   
  	w25qxx_enable();                      
    w25qxx_read_write_byte(W25X_ChipErase);   
	w25qxx_disable();                        
	w25qxx_wait_busy();   				  
} 

void w25qxx_erase_sector(uint32_t Dst_Addr)   
{  	  
 	Dst_Addr*=4096;
    w25qxx_write_enable();                
    w25qxx_wait_busy();   
  	w25qxx_enable();                         
    w25qxx_read_write_byte(W25X_SectorErase); 
    w25qxx_read_write_byte((uint8_t)((Dst_Addr)>>16));  
    w25qxx_read_write_byte((uint8_t)((Dst_Addr)>>8));   
    w25qxx_read_write_byte((uint8_t)Dst_Addr);  
	w25qxx_disable();                            
    w25qxx_wait_busy();   				    
} 
