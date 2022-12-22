
#ifndef __bsp_mks_dlc_lg0_v3_system_h
#define __bsp_mks_dlc_lg0_v3_system_h

#ifdef BOARD_MKS_DLC_LG0_V3_INI

#include "stm32f4xx_hal.h"
#include "core_cm4.h"

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) 	//扇区0起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) 	//扇区1起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) 	//扇区2起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) 	//扇区3起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) 	//扇区4起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) 	//扇区5起始地址, 128 Kbytes  



void BspMksDlcLg0SystemInit(void);
void BspMksDlcLg0ClkInit(void);
void Error_Handler(void);
uint8_t BspGetEepromAddress(uint32_t addr);

#endif

#endif