/*
 hal_flash_eeprom.c

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "bsp_flash_eeprom.h"

uint8_t eeprom_buf[PAGE_SIZE];

FLASH_EraseInitTypeDef eeprom_flash;

void BspEepromFlush(void) {

    BspFlashWriteBuff(EEPROM_START_ADDR, (uint32_t *)eeprom_buf, EEPROM_SIZE(eeprom_buf));
}

void BspEepromInit(void) {

    uint16_t    var = 0;
    uint8_t     *temp = eeprom_buf;

    BspFlashReadBuff(EEPROM_START_ADDR, (uint32_t *)eeprom_buf, EEPROM_SIZE(eeprom_buf));
    
    if(eeprom_buf[0] != SETTINGS_VERSION) {

        temp = eeprom_buf;

        for (var = 0; var < PAGE_SIZE; var++)
		{
			*temp++ = 0xFF;
		}
    }
}

uint8_t BspEeepromGetChar(unsigned int addr) {
    return eeprom_buf[addr];
}

uint8_t hal_get_flash_sector(uint32_t addr) {

    return BspGetEepromAddress(addr);
}

uint32_t STMFLASH_ReadWord(uint32_t faddr)
{
	return *(volatile uint32_t *)faddr; 
}

void BspFlashWriteBuff(uint32_t addr ,uint32_t *buff, uint32_t num) {

    FLASH_EraseInitTypeDef FlashEraseInit;
	HAL_StatusTypeDef FlashStatus=HAL_OK;
    uint32_t SectorError=0;
	uint32_t addrx=0;
	uint32_t endaddr=0;	
    HAL_StatusTypeDef status;
    
    if( addr <STM32_FLASH_BASE || addr % 4 ) return;	//非法地址

    HAL_FLASH_Unlock();             					//解锁	

    addrx=addr;											//写入的起始地址

	endaddr = addr+num*4;								//写入的结束地
 
    if(addrx < 0X1FFF0000)
	{
		while(addrx < endaddr)							//扫清一切障碍.(对非FFFFFFFF的地方,先擦除)
		{
			if(STMFLASH_ReadWord(addrx) != 0XFFFFFFFF)	//有非0XFFFFFFFF的地方,要擦除这个扇区
			{   
#ifdef FLASH_WRITE_SECTORS_WORD
				FlashEraseInit.TypeErase=FLASH_TYPEERASE_SECTORS;       //擦除类型，扇区擦除 
				FlashEraseInit.Sector=hal_get_flash_sector(addrx);   	//要擦除的扇区
				FlashEraseInit.NbSectors=1;                             //一次只擦除一个扇区
				FlashEraseInit.VoltageRange=FLASH_VOLTAGE_RANGE_3;      //电压范围，VCC=2.7~3.6V之间!!
#else
                FlashEraseInit.Banks = FLASH_BANK_2;
                FlashEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
                FlashEraseInit.Page = 383;
                FlashEraseInit.NbPages = 1;
#endif
                if(HAL_FLASHEx_Erase(&FlashEraseInit,&SectorError)!=HAL_OK) 
				{
					break;//发生错误了	
				}
				}else {
                    addrx+=4;
                }

				FLASH_WaitForLastOperation(FLASH_WAITETIME);                //等待上次操作完成
		}
	}
	FlashStatus=FLASH_WaitForLastOperation(FLASH_WAITETIME);            	//等待上次操作完成

	if(FlashStatus==HAL_OK)
	{
		 while(addr < endaddr)//写数据
		 {
#ifdef FLASH_WRITE_SECTORS_WORD

            status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, *buff);

			if(status != HAL_OK)//写入数据
			{ 
				break;	//写入异常
			}
			addr+=4;
			buff++;

#elif defined(FLASH_WRITE_PAGE_DOUBLEWORD)
            status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addr, *(uint64_t*)buff);

			if(status != HAL_OK)//写入数据
			{   
				break;	//写入异常
			}
			addr += 8;
			buff += 2;
#endif
		}  
	}
	HAL_FLASH_Lock();           //上锁
}



void BspFlashReadBuff(uint32_t addr, uint32_t *buff, uint32_t num)   	
{
	uint32_t i;
	for(i=0;i<num;i++)
	{
		buff[i]=STMFLASH_ReadWord(addr);//读取4个字节.
		addr+=4;//偏移4个字节.	
	}
}


