/*
  grbl_hal.c 
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

void grblReprotMcuInfo(void) {

    grblHwInfoGet();

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
    printf("*-BuildVersion:%s\n", GRBL_VERSION_BUILD);
    printf("/*********************************************************/\r\n");
}

void grblHwInfoGet(void) {
    grbl_hw_get.mcu_clk         = HAL_RCC_GetHCLKFreq();
    grbl_hw_get.step_tim_clk    = HAL_RCC_GetHCLKFreq();
}

void systemInit() {

    HAL_Init();

    SYSTEM_INIT();

    SYSTEM_UART();      

    SYSTEM_FLASH();  

    SYSTEM_SDRAM();   
    
    SYSTEM_SDCARD();    
    
    SYSTEM_LCD();       

    SYSTEM_WDG();
}

/** 
 * 将外设驱动单独描述，以注册的方式进行，这样即便切换不一样的MCU，提供相同的
 * 外设驱动接口，也可以正常运行OpenGRBL，大大提高了可移植性。 
 * 这里使用了模板的方式作为接口，方便后续的移植。
 */
void grblDeviceInit() {

    DevGpioInit();     

    DevUartInit();
         
    DevTimerInit();

    DevNvsInit();
}

/** 
 * 启动MCU，配置MCU内核时钟、外设时钟等等，初始化外设接口
 */
void grblHwInit(void) {

    systemInit();

    grblDeviceInit();
}
