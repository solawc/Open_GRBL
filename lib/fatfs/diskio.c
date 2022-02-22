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
#include "../../src/external_device/SD/sdcard.h"

/* Definitions of physical drive number for each drive */
// #define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
// #define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

#define SD_BLOCKSIZE 512
#define FLASH_SECTOR_SIZE 	512

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
	switch (pdrv) {
	// case DEV_RAM :
	
	// 	result = RAM_disk_status();

	// 	// translate the reslut code here

	// 	return stat;

	case DEV_MMC :
		// result = MMC_disk_status();

		// translate the reslut code here
		stat = RES_OK;
		
		return stat;

	// case DEV_USB :

	// 	result = USB_disk_status();

	// 	// translate the reslut code here

	// 	return stat;
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
	// case DEV_RAM :
	// 	result = RAM_disk_initialize();

	// 	// translate the reslut code here

	// 	return stat;

	case DEV_MMC :
		// result = MMC_disk_initialize();

		result = SD_Initialize();	//SD卡初始化 

		// translate the reslut code here
		if (result == 0)
		{	
			stat = RES_OK;
		}else {
			stat = RES_ERROR;
			DEBUG_PRINT("SD Init fail");
			DEBUG_PRINT("error code: %d", stat);
		}
		return stat;

	break;
	// case DEV_USB :
	// 	result = USB_disk_initialize();

	// 	// translate the reslut code here

	// 	return stat;
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
	// case DEV_RAM :
	// 	// translate the arguments here

	// 	result = RAM_disk_read(buff, sector, count);

	// 	// translate the reslut code here

	// 	return res;

	case DEV_MMC :
		// translate the arguments here

		// result = MMC_disk_read(buff, sector, count);

		res = SD_ReadDisk(buff, sector, count);
		while(res)//读出错
		{
			SD_Initialize();	//重新初始化SD卡
			res = SD_ReadDisk(buff,sector,count);	
		}
		// translate the reslut code here
		if(res == 0x00) return RES_OK;
		else return RES_ERROR;
	break;

	// case DEV_USB :
	// 	// translate the arguments here

	// 	result = USB_disk_read(buff, sector, count);

	// 	// translate the reslut code here

	// 	return res;
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
	// case DEV_RAM :
	// 	// translate the arguments here

	// 	result = RAM_disk_write(buff, sector, count);

	// 	// translate the reslut code here

	// 	return res;

	case DEV_MMC :
		// translate the arguments here

		res= SD_WriteDisk((uint8_t*)buff,sector,count);
		while(res)//写出错
		{
			SD_Initialize();	//重新初始化SD卡
			res = SD_WriteDisk((uint8_t*)buff,sector,count);	
		}
		// translate the reslut code here
		return res;

	// case DEV_USB :
	// 	// translate the arguments here

	// 	result = USB_disk_write(buff, sector, count);

	// 	// translate the reslut code here

	// 	return res;
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
	// case DEV_RAM :

	// 	// Process of the command for the RAM drive

	// 	return res;

	case DEV_MMC :

		// Process of the command for the MMC/SD card

		switch(cmd) {

			case CTRL_SYNC: res = RES_OK; break;
			case GET_SECTOR_SIZE:
				*(DWORD*)buff = 512; 
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

	// case DEV_USB :

	// 	// Process of the command the USB drive

	// 	return res;
	}

	return RES_PARERR;
}

