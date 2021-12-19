#ifndef __hal_flash_eeprom_h__
#define __hal_flash_eeprom_h__

#include "grbl_hal.h"

#define USE_FLASH_AS_EEPROM
#define USE_EEPROM_IC        
#ifdef  USE_EEPROM_IC
#define USE_AT24C02

#if defined(USE_AT24C02)
#define EEPROM_ADDR 0XA0
#endif
#endif

#define PAGE_SIZE                   0x400
#define EEPROM_SIZE(str)            sizeof(str)/4+(( sizeof(str) %4 )?1:0)          
#define EEPROM_START_ADDR           ((uint32_t)0x0807F800)  
#define EEPROM_END_ADDR             ((uint32_t)0x080407FF)

//FLASH起始地址
#define STM32_FLASH_BASE            0x08000000 	        //STM32 FLASH的起始地址
#define FLASH_WAITETIME             50000               //FLASH等待超时时间

//FLASH 扇区的起始地址
#define ADDR_FLASH_PAGE_0       ((uint32_t)0x08000000) 	
#define ADDR_FLASH_PAGE_1       ((uint32_t)0x08000800) 	
#define ADDR_FLASH_PAGE_2       ((uint32_t)0x08001000) 	
#define ADDR_FLASH_PAGE_127     ((uint32_t)0x0803F800) 	

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
