/*
 mid_nvs.h

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __mid_nvs_h
#define __mid_nvs_h

#include "../../../main.h"

typedef struct {

    void (*nvsInit)(void);
    void (*nvsFlush)(void);
    uint8_t (*nvsGetChar)(unsigned int );

}mid_nvs_t;
extern mid_nvs_t dev_nvs;

void DevNvsInit(void);


#endif
