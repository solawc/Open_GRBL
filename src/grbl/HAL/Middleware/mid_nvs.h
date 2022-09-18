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
