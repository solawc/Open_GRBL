#ifndef __hal_w25qxx_h__
#define __hal_w25qxx_h__

#include "main.h"

// Flash choose
#define  sFLASH_ID_X16  0xEF3015   //W25X16
#define  sFLASH_ID_16  0xEF4015   //W25Q16
#define  sFLASH_ID_64  0XEF4017   //W25Q64
#define  sFLASH_ID_128  0XEF4018   //W25Q128
#define  sFLASH_ID_256  0XEF4019     //W25Q256

#define sFLAHS_SPI_MODE         0
#define sFLASH_QSPI_MODE        1

#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256

typedef struct{
    uint32_t flash_id;
    uint32_t flash_size;
    uint32_t flash_delay_time;
    uint8_t  flash_mode;
}NFLASH_t;
extern NFLASH_t sFlash;




#define W25QXX_SPI_PORT             SPI5
#define W25QXX_SPI_SCK_GPIO         GPIOF
#define W25QXX_SPI_SCK_PIN          GPIO_PIN_7
#define W25QXX_SPI_MISO_GPIO        GPIOF
#define W25QXX_SPI_MISO_PIN         GPIO_PIN_8
#define W25QXX_SPI_MOSI_GPIO        GPIOF
#define W25QXX_SPI_MOSI_PIN         GPIO_PIN_9
#define W25QXX_SPI_CS_GPIO          GPIOF
#define W25QXX_SPI_CS_PIN           GPIO_PIN_6

// Flash cmd
#define W25X_WriteEnable		        0x06 
#define W25X_WriteDisable		        0x04 
#define W25X_ReadStatusReg		        0x05 
#define W25X_ReadStatusReg2		        0x35 
#define W25X_ReadStatusReg3		        0x15
#define W25X_WriteStatusReg		        0x01 
#define W25X_WriteStatusReg2		    0x31 
#define W25X_WriteStatusReg3		    0x11
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		        0x0B 
#define W25X_FastReadDual		        0x3B 
#define W25X_PageProgram		        0x02 
#define W25X_BlockErase			        0xD8 
#define W25X_SectorErase		        0x20 
#define W25X_ChipErase			        0xC7 
#define W25X_PowerDown			        0xB9 
#define W25X_ReleasePowerDown	        0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	    0x90 
#define W25X_JedecDeviceID		        0x9F 
#define W25X_Enter4ByteMode		        0xB7
#define W25X_ReadStatusRegister3        0x15

#define WIP_Flag                        0x01  /* Write In Progress (WIP) flag */
#define Dummy_Byte                      0xFF



void hal_w25qxx_spi_init(void);
void w25qxx_init(void);
uint32_t w25qxx_read_id(void);
uint16_t w25qxx_read_write_byte(uint16_t wdata);
void w25qxx_read_buff(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void w15qxx_write_page(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void w25qxx_write_no_check(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void w25qxx_erase_chip(void);
void w25qxx_erase_sector(uint32_t Dst_Addr);
void w25qxx_write_buff(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);

void w25qxx_enter_flash_mode(void);
void w25qxx_sector_erase(uint32_t SectorAddr);
void w25qxx_bulk_erase(void);
void w25qxx_buffer_write(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
void w25qxx_buffer_read(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);

#endif
