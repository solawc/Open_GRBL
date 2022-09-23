/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "../../src/ex_dev/sd/sdcard.h"

/* Definitions of physical drive number for each drive */
#define DEV_FLASH		0	/* for SPI Flash driver 0 	*/
#define DEV_MMC			1	/* for SD Card driver 1 	*/
// #define DEV_USB		2	/* for USB driver  2 		*/


#define SD_BLOCKSIZE			512
#define FLASH_SECTOR_SIZE 		512

uint32_t FLASH_SECTOR_COUNT = 	1024*2*32;
#define FALSH_BLOCK_SIZE		8

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
	switch (pdrv) {

		case DEV_MMC :
			// 这里需要重新做检测，但应该是一种更确保的、而不是单纯的随意读写
			stat = RES_OK;
			return stat;
		break;

		case DEV_FLASH:
			stat = RES_OK;
			return stat;
		break;

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result = 0;
	switch (pdrv) {

		case DEV_MMC :
			result = SD_Initialize();	//SD卡初始化 

			// translate the reslut code here
			if (result == 0)
			{	
				stat = RES_OK;
			}else {
				stat = RES_ERROR;
			}
			return stat;
		break;

		case DEV_FLASH :
#ifdef HAS_W25Qxx
			w25qxxInit(&sFlash);

			if(sFlash.flash_state == 1) {
				stat = RES_OK;
			}else {
				stat = RES_ERROR;
			}
			FLASH_SECTOR_COUNT = 1024 * 2 * (sFlash.flash_size/1024); /* Setting Flash size */

			return stat;
#endif
		break;

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	switch (pdrv) {

		case DEV_MMC :
			res = SD_ReadDisk(buff, sector, count);
			while(res)//读出错
			{
				SD_Initialize();	//重新初始化SD卡
				res = SD_ReadDisk(buff, sector, count);	
			}
			// translate the reslut code here
			if(res == 0x00) return RES_OK;
			else return RES_ERROR;
		break;

		case DEV_FLASH :
#ifdef HAS_W25Qxx
			for(; count>0; count--) {
				w25qxxBufferRead(&sFlash, buff, sector*FLASH_SECTOR_SIZE, count*FLASH_SECTOR_SIZE);
				sector++;
				buff += FLASH_SECTOR_SIZE;
			}
#endif
			return RES_OK;
		break;

	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	switch (pdrv) {

		case DEV_MMC :
			res= SD_WriteDisk((uint8_t*)buff,sector,count);
			while(res)//写出错
			{
				SD_Initialize();	//重新初始化SD卡
				res = SD_WriteDisk((uint8_t*)buff,sector,count);	
			}
			return res;
		break;

		case DEV_FLASH :
			// w25qxxBufferWrite(&sFlash, (uint8_t*)buff, sector, count);
#ifdef HAS_W25Qxx
			for (; count>0; count--) {
				w25qxxSectorErase(&sFlash, sector*FLASH_SECTOR_SIZE);
				w25qxxBufferWrite(&sFlash, (uint8_t*)buff, sector*FLASH_SECTOR_SIZE, FLASH_SECTOR_SIZE);
				sector++;
				buff += FLASH_SECTOR_SIZE;
			}
#endif
			return RES_OK;
		break;
	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	switch (pdrv) {

		case DEV_MMC :

			// Process of the command for the MMC/SD card

			switch(cmd) {

				case CTRL_SYNC: res = RES_OK; break;

				case GET_SECTOR_SIZE:
					*(DWORD*)buff = SD_BLOCKSIZE; 
					res = RES_OK;
				break;

				case GET_BLOCK_SIZE:
					*(WORD*)buff = 8;
					res = RES_OK;
				break;

				case GET_SECTOR_COUNT:
					*(DWORD*)buff = SD_GetSectorCount();
					res = RES_OK;
				break;
				
				default:
					res = RES_PARERR;
					break;
			}
			return res;
		break;


		case DEV_FLASH :

			switch(cmd) {

				case CTRL_SYNC: res = RES_OK; break;

				case GET_SECTOR_SIZE:
					*(DWORD*)buff = FLASH_SECTOR_SIZE; 
					res = RES_OK;
				break;

				case GET_BLOCK_SIZE:
					*(WORD*)buff = 1; // FALSH_BLOCK_SIZE;
					res = RES_OK;
				break;

				case GET_SECTOR_COUNT:
					*(DWORD*)buff = FLASH_SECTOR_COUNT;
					res = RES_OK;
				break;
			}
			return res;
		break;

	}

	return RES_PARERR;
}

