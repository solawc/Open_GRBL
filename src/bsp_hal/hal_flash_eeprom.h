#ifndef __hal_flash_eeprom_h__
#define __hal_flash_eeprom_h__

#include "grbl_hal.h"

#define USE_FLASH_AS_EEPROM
// #define USE_EEPROM_IC        
#ifdef  USE_EEPROM_IC
#define USE_AT24C02

#if defined(USE_AT24C02)
#define EEPROM_ADDR 0XA0
#endif
#endif

// #define PAGE_SIZE                   0X400
#define PAGE_SIZE                   0x400
#define EEPROM_SIZE(str)            sizeof(str)/4+(( sizeof(str) %4 )?1:0)   

#ifdef STM32F429xx
#define EEPROM_START_ADDR           ADDR_FLASH_SECTOR_11  // 80D FC00  ADDR_FLASH_SECTOR_11
#define EEPROM_END_ADDR             ((uint32_t)0x080fffff)
#elif defined(STM32G0B0xx)
#define EEPROM_START_ADDR           ((uint32_t)0x0807F800)  
#define EEPROM_END_ADDR             ((uint32_t)0x080407FF)
#endif

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址
#define FLASH_WAITETIME  50000          //FLASH等待超时时间

#ifdef STM32F429xx
//FLASH 扇区的起始地址
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) 	//扇区0起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) 	//扇区1起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) 	//扇区2起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) 	//扇区3起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) 	//扇区4起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) 	//扇区5起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) 	//扇区6起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) 	//扇区7起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) 	//扇区8起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) 	//扇区9起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) 	//扇区10起始地址,128 Kbytes  
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) 	//扇区11起始地址,128 Kbytes 

#define ADDR_FLASH_SECTOR_12	((uint32_t)0x08100000) 	//扇区12起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_13	((uint32_t)0x08104000) 	//扇区13起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_14    ((uint32_t)0x08108000) 	//扇区14起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_15	((uint32_t)0x0810C000) 	//扇区15起始地址, 16 Kbytes  
#define ADDR_FLASH_SECTOR_16    ((uint32_t)0x08110000) 	//扇区16起始地址, 64 Kbytes  
#define ADDR_FLASH_SECTOR_17	((uint32_t)0x08120000) 	//扇区17起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_18	((uint32_t)0x08140000) 	//扇区18起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_19	((uint32_t)0x08160000) 	//扇区19起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_20    ((uint32_t)0x08180000) 	//扇区20起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_21	((uint32_t)0x081A0000) 	//扇区21起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_22    ((uint32_t)0x081C0000) 	//扇区22起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_23    ((uint32_t)0x081E0000) 	//扇区23起始地址, 128 Kbytes  
#endif

extern uint8_t eeprom_buf[PAGE_SIZE];

void hal_eeprom_init(void);
uint8_t hal_eeprom_get_char(unsigned int addr);
void hal_eeprom_put_char(unsigned int addr, unsigned char new_value);
void hal_eeprom_flush(void);
void hal_flash_unlock(void);
uint8_t hal_get_flash_sector(uint32_t addr);
void hal_flash_write_buff(uint32_t addr ,uint32_t *buff, uint32_t num);
void hal_flash_read_buf(uint32_t addr, uint32_t *buff, uint32_t num);
#endif
