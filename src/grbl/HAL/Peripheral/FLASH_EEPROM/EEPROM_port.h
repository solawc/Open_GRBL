/*
 EEPROM_port.h

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __EEPROM_port_h
#define __EEPROM_port_h

#include "main.h"

typedef struct {

    void (*eepromInit)(uint32_t);
    void (*eepromWriteByte)(uint32_t, uint8_t );
    void (*eepromReadByte)(uint32_t, uint8_t );

}EEPROM_DEV_t;

void eepromI2cRegiest(void);

#endif
