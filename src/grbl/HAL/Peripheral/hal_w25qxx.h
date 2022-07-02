#ifndef __hal_w25qxx_h__
#define __hal_w25qxx_h__

#include "../../../main.h"

// Flash choose
// EF
#define  sFLASH_ID_X16  0x3015        //W25X16  
#define  sFLASH_ID_16   0x4015        //W25Q16
#define  sFLASH_ID_64   0X4017        //W25Q64
#define  sFLASH_ID_128  0X4018        //W25Q128
#define  sFLASH_ID_256  0X4019        //W25Q256  

#define sFLAHS_SPI_MODE                 0
#define sFLASH_QSPI_MODE                1

#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256

typedef struct{

    uint32_t flash_id;                  // Flash ID
    uint32_t flash_man;                 // Flash Man
    uint32_t flash_size;                
    uint32_t flash_delay_time;
    uint8_t  flash_mode;
    uint8_t  flash_state;               // check if flash can't read, use for FATFS

    /* Base Func */
    void (*w25qxx_spi_gpio_init)(void);           // 初始化GPIO的函数，包含GPIO复用
    void (*w25qxx_spi_init)(void);                // 初始化SPI外设
    uint8_t (*w25qxx_spi_read_write_byte)(uint8_t );   // SPI读写函数
    bool (*w25qxx_is_trans_finish)(void);         // 判断是否传输完成
    void (*w25qxx_enable_trans)(void);    
    void (*w25qxx_disable_trans)(void);

}NFLASH_t;
extern NFLASH_t sFlash;

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

void hal_w25qxx_spi_init(NFLASH_t *nFlash);
__WEAK void hal_w25qxx_spi_reg(NFLASH_t *nFlash);

void w25qxx_init(NFLASH_t *nFlash);
uint32_t w25qxx_read_id(NFLASH_t *nFlash);
uint16_t w25qxx_read_write_byte(NFLASH_t *nFlash, uint16_t wdata);
void w25qxx_read_buff(uint8_t *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void w15qxx_write_page(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void w25qxx_write_no_check(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void w25qxx_erase_chip(void);
void w25qxx_erase_sector(uint32_t Dst_Addr);
void w25qxx_write_buff(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);

void w25qxx_enter_flash_mode(NFLASH_t *nFlash);
void w25qxx_sector_erase(NFLASH_t *nFlash, uint32_t SectorAddr);
void w25qxx_bulk_erase(NFLASH_t *nFlash);
void w25qxx_buffer_write(NFLASH_t *nFlash, uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
void w25qxx_buffer_read(NFLASH_t *nFlash, uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);

void w25qxx_spi_regiest();


#endif
