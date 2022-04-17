#include "hal_w25qxx.h"

dev_spi_t dev_w25qxx_spi;
spi_setting_t dev_w25qxx_spi_set;
spi_setting_t dev_sdcard_set;


NFLASH_t sFlash;

static void hal_w25qxx_spi_gpio_init(void)
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

void hal_w25qxx_spi_init(void)
{   
    sFlash.flash_mode = sFLAHS_SPI_MODE;
    sFlash.flash_delay_time = 10;
    sFlash.flash_id = 0;
    sFlash.flash_size = 0;

    if(sFlash.flash_mode == sFLAHS_SPI_MODE) {
        hal_w25qxx_spi_gpio_init();

        dev_w25qxx_spi_set.is_use_irq = false;
        dev_w25qxx_spi_set.spi_num = W25QXX_SPI_NUM;
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
    return (uint8_t )rdata;
}

uint16_t w25qxx_read_write_byte(uint16_t wdata)
{
    return w25qxx_read_write_cb(&dev_w25qxx_spi, wdata);
}

void w25qxx_init(void)
{   
    uint32_t get_id_size = 0x00;
    dev_w25qxx_spi.__spi_intrans = false;
    dev_w25qxx_spi.is_use_dma = false;
    dev_w25qxx_spi.dev_spi_init_cb = hal_w25qxx_spi_init;
    dev_w25qxx_spi.dev_spi_read_write_byte = w25qxx_write_read_16;
    hal_spi_register(&dev_w25qxx_spi);

    w25qxx_enter_flash_mode();

    sFlash.flash_id =  w25qxx_read_id();

    get_id_size = sFlash.flash_id & 0x00ffff;

    switch(get_id_size) {
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
    case 4:
        command = W25X_PowerDown;
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
    while ((w25qxx_read_sr_reg(1) & 0x01) == 0x01); // 等待BUSY位清�?
}

void w25qxx_enter_power_down(void) {
    w25qxx_enable();
    w25qxx_read_write_byte(W25X_PowerDown);
    w25qxx_disable();
}

void w25qxx_wakeup(void) {
    w25qxx_enable();
    w25qxx_read_write_byte(W25X_ReleasePowerDown);
    w25qxx_disable();
}

// void SPI_FLASH_Mode_Init(void)
void w25qxx_enter_flash_mode(void)
{
	uint8_t Temp;
	w25qxx_enable();
	w25qxx_read_write_byte(W25X_ReadStatusRegister3); 
	Temp = w25qxx_read_write_byte(Dummy_Byte);
	w25qxx_disable();
	
	if((Temp & 0x01) == 0)
	{
		w25qxx_enable();
		w25qxx_read_write_byte(W25X_Enter4ByteMode);
		w25qxx_disable();
	}
}

void w25qxx_sector_erase(uint32_t SectorAddr)
{
  w25qxx_write_enable();

  w25qxx_wait_busy();
  
  w25qxx_enable();

  w25qxx_read_write_byte(W25X_SectorErase);

  w25qxx_read_write_byte((SectorAddr & 0xFF000000) >> 24);

  w25qxx_read_write_byte((SectorAddr & 0xFF0000) >> 16);

  w25qxx_read_write_byte((SectorAddr & 0xFF00) >> 8);

  w25qxx_read_write_byte(SectorAddr & 0xFF);

  w25qxx_disable();

  w25qxx_wait_busy();
}

void w25qxx_bulk_erase(void)
{
  w25qxx_write_enable();

  w25qxx_enable();

  w25qxx_read_write_byte(W25X_ChipErase);

  w25qxx_disable();

  w25qxx_wait_busy();
}

void w25qxx_page_write(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
  w25qxx_write_enable();

  w25qxx_enable();

  w25qxx_read_write_byte(W25X_PageProgram);

  w25qxx_read_write_byte((WriteAddr & 0xFF000000) >> 24);

  w25qxx_read_write_byte((WriteAddr & 0xFF0000) >> 16);

  w25qxx_read_write_byte((WriteAddr & 0xFF00) >> 8);

  w25qxx_read_write_byte(WriteAddr & 0xFF);
  
  if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
  {
     NumByteToWrite = SPI_FLASH_PerWritePageSize;
  }

  while (NumByteToWrite--)
  {
    w25qxx_read_write_byte(*pBuffer);

    pBuffer++;
  }

  w25qxx_disable();

  w25qxx_wait_busy();
}

void w25qxx_buffer_write(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
	
  Addr = WriteAddr % SPI_FLASH_PageSize;
	
  count = SPI_FLASH_PageSize - Addr;	

  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;

  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

  if (Addr == 0) {
    if (NumOfPage == 0) 
    {
      w25qxx_page_write(pBuffer, WriteAddr, NumByteToWrite);
    }
    else {

      while (NumOfPage--) {
        w25qxx_page_write(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
			
      w25qxx_page_write(pBuffer, WriteAddr, NumOfSingle);
    }
  }

  else {
    if (NumOfPage == 0) {

      if (NumOfSingle > count) 
      {
        temp = NumOfSingle - count;

        w25qxx_page_write(pBuffer, WriteAddr, count);

        WriteAddr +=  count;

        pBuffer += count;
				
        w25qxx_page_write(pBuffer, WriteAddr, temp);
      }
      else 
      {				
        w25qxx_page_write(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else {
			
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      w25qxx_page_write(pBuffer, WriteAddr, count);

      WriteAddr +=  count;

      pBuffer += count;

      while (NumOfPage--)
      {
        w25qxx_page_write(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
      if (NumOfSingle != 0)
      {
        w25qxx_page_write(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

void w25qxx_buffer_read(uint8_t* pBuffer, uint32_t ReadAddr, __IO uint32_t NumByteToRead)
{
  w25qxx_enable();

  w25qxx_read_write_byte(W25X_ReadData);

  w25qxx_read_write_byte((ReadAddr & 0xFF000000) >> 24);

  w25qxx_read_write_byte((ReadAddr & 0xFF0000) >> 16);

  w25qxx_read_write_byte((ReadAddr& 0xFF00) >> 8);

  w25qxx_read_write_byte(ReadAddr & 0xFF);

  while (NumByteToRead--)
  {
    *pBuffer = w25qxx_read_write_byte(Dummy_Byte);

    pBuffer++;
  }
  w25qxx_disable();
}



