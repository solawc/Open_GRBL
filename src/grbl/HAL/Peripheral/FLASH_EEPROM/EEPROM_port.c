/*
 EEPROM_port.c

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "EEPROM_port.h"

EEPROM_DEV_t sEEPROM;

void eepromI2cRegiest(void) {
    sEEPROM.eepromInit = NULL;
    sEEPROM.eepromReadByte = NULL;
    sEEPROM.eepromWriteByte = NULL;
}


