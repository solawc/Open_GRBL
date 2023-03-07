/*
 mid_nvs.c

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "../inc/mid_nvs.h"

mid_nvs_t dev_nvs;

void DevNvsInit(void) {
    dev_nvs.nvsInit    = BspEepromInit;
    dev_nvs.nvsGetChar  = BspEeepromGetChar;
    dev_nvs.nvsFlush    = BspEepromFlush;
} 