#include "grbl_hal.h"

void grbl_report_mcu_info(void) {

    printf("/*********************************************************/\r\n");
    printf("ST-GRBL\r\n");
    printf("CPU Name:%s\r\n",   MCU_INFI_NAME);
    printf("CPU Flash:%s\r\n",  MCU_INFI_NAME);
    printf("CPU RAM:%s\r\n",    MCU_INFI_NAME);
    printf("Flash Info 0x%x, flash_size = %dMB\n", sFlash.flash_id, (sFlash.flash_size / 1024));
    printf("/*********************************************************/\r\n");
}


void hal_delay_ms(uint32_t tick) {
    HAL_Delay(tick);
}





