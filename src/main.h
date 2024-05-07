/*
  main.h 
  Part of grbl

  Copyright (c) 2011-2016 Sungeun K. Jeon for Gnea Research LLC
  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2021-2023 sola

  grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __MAIN_H
#define __MAIN_H

#define USE_FREERTOS_RTOS

// #define DEBUG_TEST

/* STD Libraries */
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

/*******************************************
 * define PATH
 *******************************************/
#define XSTR(V...) #V
#define HAL_PATH(NAME)          XSTR(grbl/HAL/NAME)
#define HAL_PINS_PATH(NAME)     XSTR(grbl/HAL/Pins/NAME)
#define HAL_BSP_PATH(NAME)      XSTR(grbl/HAL/STM32/NAME)
#define MID_PATH(NAME)          XSTR(grbl/Middleware/inc/NAME)
#define GRBL_SRC_PATH(NAME)     XSTR(grbl/grbl_src/NAME)


#include "board_support.h"

#if defined(USE_FREERTOS_RTOS)
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#endif

#include GRBL_SRC_PATH(grbl_main.h)

#include HAL_PATH(grbl_config.h)
#include HAL_PATH(arm_support/arm_support.h)

#include HAL_BSP_PATH(bsp_gpio.h)
#include HAL_BSP_PATH(bsp_uart.h)
#include HAL_BSP_PATH(bsp_tim.h)
#include HAL_BSP_PATH(bsp_flash_eeprom.h)
#include HAL_BSP_PATH(hal_spi.h)
#include HAL_BSP_PATH(bsp_wdg.h)
#include HAL_BSP_PATH(bsp_sdram.h)
#include HAL_BSP_PATH(bsp_ltdc.h)


#ifdef HAS_SDCARD
#include "grbl/HAL/Peripheral/FLASH_eSDCARD/hal_sdcard.h"
#include "ff.h"     // For Fatfs 
#endif

#ifdef HAS_W25Qxx 
#include "grbl/HAL/Peripheral/FLASH_eW25QXX/eflash.h"
#endif

#include MID_PATH(debug.h)
#include MID_PATH(mid_gpio.h)
#include MID_PATH(mid_timer.h)
#include MID_PATH(mid_nvs.h)
#include MID_PATH(mid_uart.h)

#include "ex_dev/lcd/tft_lcd_dev.h"
#include "ex_dev/sd/sdcard.h"
#include "ex_dev/sd/sd_file.h"

#include "ui/lv_port/lv_disp_port.h"


#define SYSTEM_UART()       uart_init()

#ifdef HAS_WDG
#define SYSTEM_WDG()        hal_wdg_init()
#else 
#define SYSTEM_WDG()
#endif

#ifdef HAS_W25Qxx 
#define SYSTEM_FLASH()      w25qxxSpiRegiest(); \
                            w25qxxInit(&sFlash); 
#else 
#define SYSTEM_FLASH()
#endif

#ifdef HAS_SDRAM
#define SYSTEM_SDRAM()      sdramInit()
#else 
#define SYSTEM_SDRAM()
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


// 编译相关
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))


void _delay_ms(uint32_t tick);
void _delay_us(uint32_t tick);

#endif
