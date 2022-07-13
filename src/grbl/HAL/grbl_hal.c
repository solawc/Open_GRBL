/*
  grbl_hal.c - rs274/ngc parser.
  Part of Grbl

  Copyright (c) 2011-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2021-2022 sola

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

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
#ifdef HAS_W25Qxx
    printf("*-Flash Info 0x%lx, flash_size = %ldMB\n", (uint32_t)sFlash.flash_id, (sFlash.flash_size / (uint32_t)1024));
#endif
    printf("*-BuildVersion%s:\n", GRBL_VERSION_BUILD);
    printf("/*********************************************************/\r\n");
}

void grbl_hw_info_get(void) {
    grbl_hw_get.mcu_clk         = HAL_RCC_GetHCLKFreq();
    grbl_hw_get.step_tim_clk    = HAL_RCC_GetHCLKFreq();
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

    // if(w25qxx_fs_init()) {
    //     printf("W25QXX FS Succeeds\n");
    // }
#endif
}
