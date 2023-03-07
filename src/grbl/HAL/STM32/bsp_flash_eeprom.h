/*
 bsp_flash_eeprom.h

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __hal_flash_eeprom_h__
#define __hal_flash_eeprom_h__

#ifdef __cplusplus
extern "C" {
#endif

#include "../grbl_hal.h"

#define USE_FLASH_AS_EEPROM
      
#ifdef  I2C_EEPEOM
#define USE_AT24C02

#if defined(USE_AT24C02)
#define EEPROM_ADDR 0XA0
#endif
#endif

#define PAGE_SIZE                       0x400
#define EEPROM_SIZE(str)                sizeof(str)/4+( ( sizeof(str) % 4 ) ? 1 : 0 )   

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址
#define FLASH_WAITETIME  50000          //FLASH等待超时时间

extern uint8_t eeprom_buf[PAGE_SIZE];

void BspEepromInit(void);
void BspEepromFlush(void);
void BspFlashWriteBuff(uint32_t addr ,uint32_t *buff, uint32_t num);
void BspFlashReadBuff(uint32_t addr, uint32_t *buff, uint32_t num);
uint8_t BspEeepromGetChar(unsigned int addr);
uint8_t hal_get_flash_sector(uint32_t addr);

#ifdef __cplusplus
}
#endif

#endif
