/*
  main.h 
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

#ifndef __MAIN_H
#define __MAIN_H

#define USE_FREERTOS_RTOS

// #define DEBUG_TEST

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#include "grbl/HAL/grbl_mb.h"

#if MB_BOARD==BOARD_FIRE_BOARD_F429
    #include "grbl/HAL/STM32/bsp_FireBoard_F429V2/hal_FireBoard_system.h"
    #include "grbl/HAL/Pins/pins_fireboard_f429.h"
#elif MB_BOARD==BOARD_NUCLEO_G070RB
    #include "grbl/HAL/STM32/bsp_nucleo_g070rb/hal_nucleo_g070rb.h"
    #include "grbl/HAL/Pins/pins_nucleo_g070rb.h"
#elif MB_BOARD==BOARD_MKS_DLC_LG0_V3
    #include "grbl/HAL/STM32/bsp_mks_dlc_lg0_v3/bsp_mks_dlc_lg0_v3_system.h"
    #include "grbl/HAL/Pins/pins_mks_dlc_lg0_v3.h"
#endif


#if defined(USE_FREERTOS_RTOS)
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#endif

#include "grbl/grbl_main.h"

#include "grbl/HAL/grbl_hal.h"
#include "grbl/HAL/grbl_config.h"

#include "grbl/HAL/STM32/bsp_gpio.h"
#include "grbl/HAL/STM32/hal_uart.h"
#include "grbl/HAL/STM32/hal_tim.h"
#include "grbl/HAL/STM32/hal_flash_eeprom.h"
#include "grbl/HAL/STM32/hal_spi.h"
#include "grbl/HAL/STM32/hal_wdg.h"
#include "grbl/HAL/STM32/bsp_sdram.h"
#include "grbl/HAL/STM32/bsp_ltdc.h"

#include "grbl/HAL/Peripheral/hal_sdcard.h"
#include "grbl/HAL/Peripheral/hal_w25qxx.h"

#include "grbl/HAL/Middleware/mid_gpio.h"
#include "grbl/HAL/Middleware/mid_timer.h"
#include "grbl/HAL/Middleware/mid_nvs.h"

#include "ex_dev/lcd/tft_lcd_dev.h"
#include "ex_dev/sd/sdcard.h"
#include "ex_dev/sd/sd_file.h"

#include "ui/lv_port/lv_disp_port.h"


#include "client.h"

#include "grbl/grbl.h"

// For Fatfs 
#include "ff.h"

#define SYSTEM_UART()       BspUartInit()

#ifdef HAS_WDG
#define SYSTEM_WDG()        hal_wdg_init()
#else 
#define SYSTEM_WDG()
#endif

#ifdef HAS_W25Qxx 
#define SYSTEM_FLASH()      w25qxxSpiRegiest(); \
                            w25qxxInit(&sFlash); \
                            w25qxx_fs_init();
#else 
#define SYSTEM_FLASH()
#endif

#ifdef HAS_SDRAM
#define SYSTEM_SDRAM()      sdramInit()
#endif

#if defined(LCD_MKS_TS35) || defined(LCD_MKS_TS24) 
#define SYSTEM_LCD()        dev_lcd_init()
#else 
#define SYSTEM_LCD()
#endif

#if defined(HAS_SDCARD)
#define SYSTEM_SDCARD()     sd_init()
#else 
#define SYSTEM_SDCARD()
#endif

void _delay_ms(uint32_t tick);
void _delay_us(uint32_t tick);

#endif
