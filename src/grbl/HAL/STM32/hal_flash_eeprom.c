#include "hal_flash_eeprom.h"
// #include "grbl.h"

uint8_t eeprom_buf[PAGE_SIZE];

FLASH_EraseInitTypeDef eeprom_flash;


#ifdef USE_EEPROM_IC

void hal_eeprom_i2c_init(void) {
    hal_i2c1_init();
}

void hal_eeprom_read_id() {

    
}

void hal_i2c_eeprom_write_page(uint8_t *buff) {
    
}
#endif


void hal_flash_unlock(void) {
    // HAL_FLASH_Unlock();
}

uint32_t hal_read_flash_word(uint32_t addr) {

    return *(volatile uint32_t *)addr; 
}

void hal_eeprom_flush(void) {

    hal_flash_write_buff(EEPROM_START_ADDR, (uint32_t *)eeprom_buf, EEPROM_SIZE(eeprom_buf));
}

void hal_eeprom_init(void) {

    uint16_t    var = 0;
    uint8_t     *temp = eeprom_buf;

    hal_flash_read_buf(EEPROM_START_ADDR, (uint32_t *)eeprom_buf, EEPROM_SIZE(eeprom_buf));
    
    if(eeprom_buf[0] != SETTINGS_VERSION) {

        temp = eeprom_buf;

        for (var = 0; var < PAGE_SIZE; var++)
		{
			*temp++ = 0xFF;
		}
    }
}

uint8_t hal_eeprom_get_char(unsigned int addr) {
    return eeprom_buf[addr];
}

void hal_eeprom_put_char(unsigned int addr, unsigned char new_value) {
    eeprom_buf[addr] = new_value;
}

uint32_t hal_falsh_eeprom_read(uint32_t addr) {

    return *(volatile uint32_t *)addr;
}

uint8_t hal_get_flash_sector(uint32_t addr) {
#ifdef STM32F429xx
    if(addr<ADDR_FLASH_SECTOR_1)return FLASH_SECTOR_0;
    else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_SECTOR_1;
    else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_SECTOR_2;
    else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_SECTOR_3;
    else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_SECTOR_4;
    else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_SECTOR_5;
    else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_SECTOR_6;
    else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_SECTOR_7;
    else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_SECTOR_8;
    else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_SECTOR_9;
    else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_SECTOR_10;
    else if(addr<ADDR_FLASH_SECTOR_12)return FLASH_SECTOR_11;
    else if(addr<ADDR_FLASH_SECTOR_13)return FLASH_SECTOR_12;
    else if(addr<ADDR_FLASH_SECTOR_14)return FLASH_SECTOR_13;
    else if(addr<ADDR_FLASH_SECTOR_15)return FLASH_SECTOR_14;
    else if(addr<ADDR_FLASH_SECTOR_16)return FLASH_SECTOR_15;
    else if(addr<ADDR_FLASH_SECTOR_17)return FLASH_SECTOR_16;
    else if(addr<ADDR_FLASH_SECTOR_18)return FLASH_SECTOR_17;
    else if(addr<ADDR_FLASH_SECTOR_19)return FLASH_SECTOR_18;
    else if(addr<ADDR_FLASH_SECTOR_20)return FLASH_SECTOR_19;
    else if(addr<ADDR_FLASH_SECTOR_21)return FLASH_SECTOR_20;
    else if(addr<ADDR_FLASH_SECTOR_22)return FLASH_SECTOR_21;
    else if(addr<ADDR_FLASH_SECTOR_23)return FLASH_SECTOR_22;
    return FLASH_SECTOR_23;
#else 
    return 0;
#endif
}

uint32_t STMFLASH_ReadWord(uint32_t faddr)
{
	return *(volatile uint32_t *)faddr; 
}

void hal_flash_write_buff(uint32_t addr ,uint32_t *buff, uint32_t num) {

    FLASH_EraseInitTypeDef FlashEraseInit;
	HAL_StatusTypeDef FlashStatus=HAL_OK;
    uint32_t SectorError=0;
	uint32_t addrx=0;
	uint32_t endaddr=0;	
    HAL_StatusTypeDef status;
    
    if( addr <STM32_FLASH_BASE || addr % 4 ) return;	//????????????

    HAL_FLASH_Unlock();             //??????	

    addrx=addr;				//?????????????????????

	endaddr = addr+num*4;	//??????????????????
 
    if(addrx < 0X1FFF0000)
	{
		while(addrx < endaddr)		//??????????????????.(??????FFFFFFFF?????????,?????????)
		{
			if(STMFLASH_ReadWord(addrx) != 0XFFFFFFFF)//??????0XFFFFFFFF?????????,?????????????????????
			{   
#ifdef STM32F429xx
				FlashEraseInit.TypeErase=FLASH_TYPEERASE_SECTORS;       //??????????????????????????? 
				FlashEraseInit.Sector=hal_get_flash_sector(addrx);   //??????????????????
				FlashEraseInit.NbSectors=1;                             //???????????????????????????
				FlashEraseInit.VoltageRange=FLASH_VOLTAGE_RANGE_3;      //???????????????VCC=2.7~3.6V??????!!
#elif defined(STM32G0B0xx)
                FlashEraseInit.Banks = FLASH_BANK_2;
                FlashEraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
                FlashEraseInit.Page = 383;
                FlashEraseInit.NbPages = 1;
#endif
                if(HAL_FLASHEx_Erase(&FlashEraseInit,&SectorError)!=HAL_OK) 
				{
					break;//???????????????	
				}
				}else {
                    addrx+=4;
                }

				FLASH_WaitForLastOperation(FLASH_WAITETIME);                //????????????????????????
		}
	}
	FlashStatus=FLASH_WaitForLastOperation(FLASH_WAITETIME);            //????????????????????????

	if(FlashStatus==HAL_OK)
	{
		 while(addr < endaddr)//?????????
		 {
#ifdef STM32F429xx

            status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, *buff);

			if(status != HAL_OK)//????????????
			{ 
				break;	//????????????
			}
			addr+=4;
			buff++;

#elif defined(STM32G0B0xx)
            status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, addr, *(uint64_t*)buff);

			if(status != HAL_OK)//????????????
			{   
				break;	//????????????
			}
			addr += 8;
			buff += 2;
#endif
		}  
	}

	HAL_FLASH_Lock();           //??????
}



void hal_flash_read_buf(uint32_t addr, uint32_t *buff, uint32_t num)   	
{
	uint32_t i;
	for(i=0;i<num;i++)
	{
		buff[i]=STMFLASH_ReadWord(addr);//??????4?????????.
		addr+=4;//??????4?????????.	
	}
}


