#include "mid_nvs.h"

mid_nvs_t dev_nvs;

void DevNvsInit(void) {
    dev_nvs.nvsFlush = BspEepromInit;
    dev_nvs.nvsGetChar = BspEeepromGetChar;
    dev_nvs.nvsFlush = BspEepromFlush;
}