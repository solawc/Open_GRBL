#include "hal_w25qxx.h"

#ifdef HAS_W25Qxx

static void w25qxx_enable(NFLASH_t *nFlash)
{
  nFlash->w25qxx_enable_trans();
}

static void w25qxx_disable(NFLASH_t *nFlash)
{
  nFlash->w25qxx_disable_trans();
}

__WEAK void hal_w25qxx_spi_reg(NFLASH_t *nFlash) {

  //..TODO
}

void hal_w25qxx_spi_init(NFLASH_t *nFlash)
{   
    hal_w25qxx_spi_reg(nFlash);

    if(sFlash.flash_mode == sFLAHS_SPI_MODE) {
        nFlash->w25qxx_spi_gpio_init();
        nFlash->w25qxx_spi_init();
    }else {

    }    
}

uint16_t w25qxx_read_write_byte(NFLASH_t *nFlash, uint16_t wdata)
{ 
  return nFlash->w25qxx_spi_read_write_byte(wdata);
}


/*--------------------------------------------------------------------------------------------*/

void w25qxx_init(NFLASH_t *nFlash)
{   
  uint32_t get_id_size = 0x00;
  
  hal_w25qxx_spi_init(nFlash);

  w25qxx_enter_flash_mode(nFlash);

  sFlash.flash_id =  w25qxx_read_id(nFlash);

  get_id_size = sFlash.flash_id & 0x00ffff;

  sFlash.addr_size = 16;

  switch(get_id_size) {
    case sFLASH_ID_X16: sFlash.flash_size   = (16  / 8) *1024; break;
    case sFLASH_ID_16:  sFlash.flash_size    = (16  / 8) *1024; break;
    case sFLASH_ID_64:  sFlash.flash_size    = (64  / 8) *1024; break;
    case sFLASH_ID_128: sFlash.flash_size   = (128 / 8) *1024; 
                        sFlash.addr_size = 24;
                        break;
    case sFLASH_ID_256: sFlash.flash_size   = (258 / 8) *1024; 
                        sFlash.addr_size = 24;
                        break;
    default: sFlash.flash_size = 0; break;
  }

  if(sFlash.flash_size != 0) { sFlash.flash_state = 1; }
  else { sFlash.flash_state = 0; }
}

uint32_t w25qxx_read_id(NFLASH_t *nFlash)
{
    uint32_t id = 0;
    w25qxx_enable(nFlash);
    w25qxx_read_write_byte(nFlash, W25X_JedecDeviceID);
    id |= w25qxx_read_write_byte(nFlash, 0xff) << 16;
    id |= w25qxx_read_write_byte(nFlash, 0xff) << 8;
    id |= w25qxx_read_write_byte(nFlash, 0xff) << 0;
    w25qxx_disable(nFlash);
    return id;
}

uint8_t w25qxx_read_sr_reg(NFLASH_t *nFlash, uint8_t reg)
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
    w25qxx_enable(nFlash);
    w25qxx_read_write_byte(nFlash, command);
    byte = w25qxx_read_write_byte(nFlash, 0Xff);
    w25qxx_disable(nFlash);
    return byte;
}

void w25qxx_write_enable(NFLASH_t *nFlash)
{
    w25qxx_enable(nFlash);
    w25qxx_read_write_byte(nFlash, W25X_WriteEnable);
    w25qxx_disable(nFlash);
}

void w25qxx_write_disable(NFLASH_t *nFlash)
{
    w25qxx_enable(nFlash);
    w25qxx_read_write_byte(nFlash, W25X_WriteDisable);
    w25qxx_disable(nFlash);
}


void w25qxx_wait_busy(NFLASH_t *nFlash)
{
    uint8_t FLASH_Status = 0;
    uint32_t SPITimeout = 0xfffff;
    w25qxx_enable(nFlash);
    w25qxx_read_write_byte(nFlash, W25X_ReadStatusReg);
    do
    {
      FLASH_Status = w25qxx_read_write_byte(nFlash, Dummy_Byte);	 
      if((SPITimeout--) == 0) 
      {
        return;
      }
    }
    while ((FLASH_Status & WIP_Flag) == SET); 
    w25qxx_disable(nFlash);
}

void w25qxx_enter_power_down(NFLASH_t *nFlash) {
    w25qxx_enable(nFlash);
    w25qxx_read_write_byte(nFlash, W25X_PowerDown);
    w25qxx_disable(nFlash);
}

void w25qxx_wakeup(NFLASH_t *nFlash) {
    w25qxx_enable(nFlash);
    w25qxx_read_write_byte(nFlash, W25X_ReleasePowerDown);
    w25qxx_disable(nFlash);
}


void w25qxx_enter_flash_mode(NFLASH_t *nFlash)
{
	uint8_t Temp;
	w25qxx_enable(nFlash);
	w25qxx_read_write_byte(nFlash, W25X_ReadStatusRegister3); 
	Temp = w25qxx_read_write_byte(nFlash, Dummy_Byte);
	w25qxx_disable(nFlash);
	
	if((Temp & 0x01) == 0)
	{
		w25qxx_enable(nFlash);
		w25qxx_read_write_byte(nFlash, W25X_Enter4ByteMode);
		w25qxx_disable(nFlash);
	}
}

void w25qxx_sector_erase(NFLASH_t *nFlash, uint32_t SectorAddr)
{
  w25qxx_write_enable(nFlash);

  w25qxx_wait_busy(nFlash);
  
  w25qxx_enable(nFlash);

  w25qxx_read_write_byte(nFlash, W25X_SectorErase);
  if(sFlash.addr_size == 24) {
    w25qxx_read_write_byte(nFlash, (SectorAddr & 0xFF000000) >> 24);
  }

  w25qxx_read_write_byte(nFlash, (SectorAddr & 0xFF0000) >> 16);

  w25qxx_read_write_byte(nFlash, (SectorAddr & 0xFF00) >> 8);

  w25qxx_read_write_byte(nFlash, SectorAddr & 0xFF);

  w25qxx_disable(nFlash);

  w25qxx_wait_busy(nFlash);
}

void w25qxx_chip_erase(NFLASH_t *nFlash)
{
  w25qxx_write_enable(nFlash);

  w25qxx_wait_busy(nFlash);

  w25qxx_enable(nFlash);

  w25qxx_read_write_byte(nFlash, W25X_ChipErase);

  w25qxx_disable(nFlash);

  w25qxx_wait_busy(nFlash);
}

void w25qxx_page_write(NFLASH_t *nFlash, uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
  w25qxx_write_enable(nFlash);

  w25qxx_enable(nFlash);

  w25qxx_read_write_byte(nFlash, W25X_PageProgram);

  if(sFlash.addr_size == 24) {
    w25qxx_read_write_byte(nFlash, (WriteAddr & 0xFF000000) >> 24);
  }

  w25qxx_read_write_byte(nFlash, (WriteAddr & 0xFF0000) >> 16);

  w25qxx_read_write_byte(nFlash, (WriteAddr & 0xFF00) >> 8);

  w25qxx_read_write_byte(nFlash, WriteAddr & 0xFF);
  
  if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
  {
     NumByteToWrite = SPI_FLASH_PerWritePageSize;
  }

  while (NumByteToWrite--)
  {
    w25qxx_read_write_byte(nFlash, *pBuffer);

    pBuffer++;
  }

  w25qxx_disable(nFlash);

  w25qxx_wait_busy(nFlash);
}

void w25qxx_buffer_write(NFLASH_t *nFlash, uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, 
          NumOfSingle = 0, 
          Addr = 0, 
          count = 0, 
          temp = 0;
	
  Addr = WriteAddr % SPI_FLASH_PageSize;
	
  count = SPI_FLASH_PageSize - Addr;	

  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;

  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

  if (Addr == 0) {
    if (NumOfPage == 0) 
    {
      w25qxx_page_write(nFlash, pBuffer, WriteAddr, NumByteToWrite);
    }
    else {

      while (NumOfPage--) {
        w25qxx_page_write(nFlash, pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
			
      w25qxx_page_write(nFlash, pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else {
    if (NumOfPage == 0) {

      if (NumOfSingle > count) 
      {
        temp = NumOfSingle - count;

        w25qxx_page_write(nFlash, pBuffer, WriteAddr, count);

        WriteAddr +=  count;

        pBuffer += count;
				
        w25qxx_page_write(nFlash, pBuffer, WriteAddr, temp);
      }
      else 
      {				
        w25qxx_page_write(nFlash, pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      w25qxx_page_write(nFlash, pBuffer, WriteAddr, count);

      WriteAddr +=  count;

      pBuffer += count;

      while (NumOfPage--)
      {
        w25qxx_page_write(nFlash, pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
      if (NumOfSingle != 0)
      {
        w25qxx_page_write(nFlash, pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

void w25qxx_buffer_read(NFLASH_t *nFlash, uint8_t* pBuffer, uint32_t ReadAddr, __IO uint32_t NumByteToRead)
{
  w25qxx_enable(nFlash);

  w25qxx_read_write_byte(nFlash, W25X_ReadData);

  if(sFlash.addr_size == 24) {
    w25qxx_read_write_byte(nFlash, (ReadAddr & 0xFF000000) >> 24);
  }

  w25qxx_read_write_byte(nFlash, (ReadAddr & 0xFF0000) >> 16);

  w25qxx_read_write_byte(nFlash, (ReadAddr& 0xFF00) >> 8);

  w25qxx_read_write_byte(nFlash, ReadAddr & 0xFF);

  for(uint16_t i = 0; i < NumByteToRead; i++) {
    pBuffer[i] = w25qxx_read_write_byte(nFlash, Dummy_Byte);
  }

  w25qxx_disable(nFlash);
}


/*************************************************************
 *                      w25qxx test
 * **********************************************************/
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize     (countof(Tx_Buffer)-1)

#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress

uint8_t Tx_Buffer[] = "abcd213213dcba";
uint8_t Rx_Buffer[BufferSize];

void w25qxx_test() {

  // 擦除FLASH
  printf("Begin erase....\n");
  w25qxx_sector_erase(&sFlash, FLASH_SectorToErase);

  
  // 往FLASH写入数据
  printf("Begin write data...\n");
  w25qxx_buffer_write(&sFlash, Tx_Buffer, FLASH_WriteAddress, BufferSize);

  printf("begin read data....\n");
  w25qxx_buffer_read(&sFlash, Rx_Buffer, FLASH_ReadAddress, BufferSize);

  printf("data:%s\n", Rx_Buffer);
}




#ifdef USE_FATFS
FATFS           wfs;

bool w25qxx_fs_init(void) {

  FRESULT fs_res;
  BYTE work[FF_MAX_SS];

  fs_res = f_mount(&wfs, W25QXX_FS_PATH, 1);

  if(fs_res == FR_NO_FILESYSTEM) {
        fs_res = f_mkfs("0:", NULL, work, sizeof(work));
        if(fs_res == FR_OK) { 
          fs_res = f_mount(&wfs, W25QXX_FS_PATH, 1);
          if(fs_res != FR_OK) { 
            // printf("W25QXX fs fail\n");
            return false;
          }
          get_w25qxx_fafts_info();
          return true; 
        }
        else { return false; }
  }else if(fs_res == FR_OK) {
    get_w25qxx_fafts_info();
    return true;
  }else {
    return false;
  }
}

void get_w25qxx_fafts_info(void) {

  FATFS *pfs = &wfs;

  DWORD fre_clust, fre_size, tot_size;
  
  uint8_t result = f_getfree( W25QXX_FS_PATH, &fre_clust, &pfs );
  
  if( result == FR_OK )
  {
      tot_size = (pfs->n_fatent - 2) * pfs->csize/2; // 总容量    单位Kbyte
      fre_size = fre_clust * pfs->csize/2;           // 可用容量  单位Kbyte
      printf("w25qxx total size:%ldMB\n", tot_size);
      printf("w25qxx free size:%ldMB\n", fre_size);
  }
  else{
    printf("NorFlash Error\n");
  }
}


void w25qxx_fatfs_test() {

  FRESULT fr = FR_OK;
  UINT br, bw;

  UINT btr, br1;

  char test_buff[128];

  fr = f_open(&wfs, W25QXX_FS_PATH, 1);

  printf("wait write file...\n");
  f_write(&wfs, "nihao", br, &bw);

  printf("wait read file...\n");
  f_read(&wfs, test_buff, btr, &br1); 
  printf("readfile:%s\n", test_buff);
}


bool w25qxx_f_open() {

  return true;
}

#endif

#endif


