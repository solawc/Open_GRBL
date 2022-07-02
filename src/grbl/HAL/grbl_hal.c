#include "grbl_hal.h"

grbl_hw_t grbl_hw_get;

void grbl_report_mcu_info(void) {

    grbl_hw_info_get();

    printf("/*********************************************************/\r\n");
    printf("*-\\    |    /\n");
    printf("* --OpenGRBL--\r\n");
    printf("*-/    |    \\\n");
    printf("*-CPU Name:%s\r\n", MCU_INFI_NAME);
    printf("*-CPU Flash:%s\r\n", MCU_INFO_FLASH);
    printf("*-CPU RAM:%s\r\n", MCU_INFO_RAM);
    printf("*-CPU Clock:%ldMHz\r\n", grbl_hw_get.mcu_clk/1000000);
    printf("*-CPU Step Clock:%ldMHz\r\n", grbl_hw_get.step_tim_clk/1000000);
    printf("*-Flash Info 0x%lx, flash_size = %ldMB\n", (uint32_t)sFlash.flash_id, (sFlash.flash_size / (uint32_t)1024));
    printf("*-BuildVersion%s:\n", GRBL_VERSION_BUILD);
    printf("/*********************************************************/\r\n");
}

void grbl_hw_info_get(void) {
    grbl_hw_get.mcu_clk = HAL_RCC_GetHCLKFreq();
    grbl_hw_get.step_tim_clk = HAL_RCC_GetHCLKFreq();
}



void grbl_hw_init(void) {

    HAL_Init();

    SYSTEM_INTI();

    SYSTEM_UART();      // hal_uart_init();

#ifndef DEBUG_TEST
    SYSTEM_LASER();     // hal_pwm_init();

    SYSTEM_FLASH();     // w25qxx_init();

    SYSTEM_SDCARD();    // sd_init()
    
    SYSTEM_LCD();       // dev_lcd_init();

    if(w25qxx_fs_init()) {
        printf("W25QXX FS Succeeds\n");
    }

    // FRESULT fs_res;

    // fs_res = f_mount(&wfs,"0:",1);
    // BYTE work[FF_MAX_SS];

    // if(fs_res == FR_NO_FILESYSTEM) {
    //     printf("rebuild fatfs\n");
    //     fs_res = f_mkfs("0:", NULL, work, sizeof(work));
    //     if(fs_res != FR_OK) {
    //         printf("W25qxx fatfs fail\n");
    //     }else {
    //         printf("W25qxx fatfs succeed\n");
    //     }
    // }

    // if(fs_res == FR_OK){
    //     printf("W25qxx fatfs succeed\n");
    // }else {
    //     printf("W25qxx fatfs fail\n");
    // }


#endif
}
