/*
 eflash.h

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __hal_w25qxx_h__
#define __hal_w25qxx_h__

#include "../../grbl_config.h"

#ifdef HAS_W25Qxx

    #include "eflash_port.h"

    #define eFLASH_VERSION                   20221215

    // Flash choose
    // EF -- W25QXX
    #define  sFLASH_ID_X16  0x3015          /* W25X16  */ 
    #define  sFLASH_ID_16   0x4015          /* W25Q16  */
    #define  sFLASH_ID_64   0X4017          /* W25Q64  */
    #define  sFLASH_ID_128  0X4018          /* W25Q128 */
    #define  sFLASH_ID_256  0X4019          /* W25Q256 */  

    #define sFLAHS_SPI_MODE                 0
    #define sFLASH_QSPI_MODE                1

    #define SPI_FLASH_PageSize              256
    #define SPI_FLASH_PerWritePageSize      256

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


    /* Flash support list. */
    enum {
        W25QXX      = 0xEF,
        ZB25QXX     = 0x5E,
    }Flash_Man_t;

    typedef struct {
        uint32_t flash_id;                  /* Flash ID                                 */ 
        uint32_t flash_man;                 /* Flash device name                        */ 
        uint32_t flash_size;                /* Flash size(KB)                           */             
        uint32_t flash_delay_time;          /* Flash delay                              */
        uint32_t sector_size;               /* Flash sector size                        */
        uint8_t  flash_mode;                /* Flash mode(SPI or QSPI)                  */
        uint8_t  flash_state;               /* check if flash can't read, use for FATFS */ 
        uint8_t  addr_size;
    }eFLASH_INFO_t;

    typedef struct{
        
        eFLASH_INFO_t info;

        /* Base Func */
        void (*flashSpiGpioInit)(void);                        /* 初始化GPIO的函数，包含GPIO复用 */
        void (*flashSpiInit)(void);                            /* 初始化SPI外设 */
        uint8_t (*flashSpiReadWriteByte)(uint8_t );            /* SPI读写函数 */
        bool (*flashIsTransFinish)(void);                      /* 判断是否传输完成 */
        void (*flashEnableTrans)(void);    
        void (*flashDisableTrans)(void);

    }eFLASH_t;
    extern eFLASH_t sFlash;

    
    void flashSpiInit(eFLASH_t *nFlash);                           

    void w25qxxInit(eFLASH_t *nFlash);
    uint32_t w25qxxRead_ID(eFLASH_t *nFlash);
    uint16_t w25qxxReadWriteByte(eFLASH_t *nFlash, uint16_t wdata);

    void w25qxxEnterFlashMode(eFLASH_t *nFlash);
    void w25qxxSectorErase(eFLASH_t *nFlash, uint32_t SectorAddr);
    void w25qxxBlockErase(eFLASH_t *nFlash, uint32_t BlockAddr);
    void w25qxxChipErase(eFLASH_t *nFlash);
    void w25qxxBufferWrite(eFLASH_t *nFlash, uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
    void w25qxxBufferRead(eFLASH_t *nFlash, uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
    void w25qxxTest();
    #ifdef USE_FATFS
        bool w25qxx_fs_init(void);
        void get_w25qxx_fafts_info(void);
    #endif /* USE_FATFS */

#endif /* HAS_W25Qxx */

#endif /* __hal_w25qxx_h__ */
