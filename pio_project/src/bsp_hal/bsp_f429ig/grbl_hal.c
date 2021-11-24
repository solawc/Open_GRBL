#include "grbl_hal.h"

void grbl_report_mcu_info(void) {

    printf("/*********************************************************/\r\n");
    printf("ST-GRBL\r\n");
    printf("CPU Name:%s\r\n", MCU_INFI_NAME);
    printf("CPU Flash:%s\r\n", MCU_INFI_NAME);
    printf("CPU RAM:%s\r\n", MCU_INFI_NAME);
    printf("CPU CLK:%dMHz\r\n", HAL_RCC_GetHCLKFreq()/1000000);
    printf("Flash Info 0x%x, flash_size = %dMB\n", (uint32_t)sFlash.flash_id, (sFlash.flash_size / (uint32_t)1024));
    printf("/*********************************************************/\r\n");
}




