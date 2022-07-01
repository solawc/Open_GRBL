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
// #include "../../src/external_device/SD/sdcard.h"
#include "../../src/ex_dev/sd/sdcard.h"

/* Definitions of physical drive number for each drive */
// #define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
// #define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */
#define DEV_FLASH		0	/* for SPI Flash driver 0 */

#define SD_BLOCKSIZE			512
#define FLASH_SECTOR_SIZE 		4096// 512

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
			// result = 
			w25qxx_init(&sFlash);

			if(sFlash.flash_state == 1) {
				stat = RES_OK;
			}else {
				stat = RES_ERROR;
			}
			return stat;
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
			w25qxx_buffer_read(&sFlash, buff, sector, count);
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
			w25qxx_buffer_write(&sFlash, (uint8_t*)buff, sector, count);
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
					*(WORD*)buff = 1;
					res = RES_OK;
				break;

				case GET_SECTOR_COUNT:
					*(DWORD*)buff = 4096; // SD_GetSectorCount();
					res = RES_OK;
				break;
			}

		break;

	}

	return RES_PARERR;
}

