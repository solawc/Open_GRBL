/*
  grbl_hal.h - rs274/ngc parser.
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

#ifndef __grbl_hal_h
#define __grbl_hal_h


#include "main.h"
#include "stdbool.h"

#include "grbl_config.h"
#include "grbl_mb.h"

/***************************************************
 *                  MCU Platform
 * Here we mainly describe the relevant 
 * information of MCU model
 * ************************************************/
#ifdef STM32F429xx
#define MCU_INFI_NAME       "STM32F429IG"
#define MCU_INFO_FLASH      "1024K"
#define MCU_INFO_RAM        "512K"
#elif defined(STM32G0B0xx) 
#define MCU_INFI_NAME       "STM32G0B0CE"
#define MCU_INFO_FLASH      "512K"
#define MCU_INFO_RAM        "144K"
#elif defined(STM32G070xx)
#define MCU_INFI_NAME       "STM32G070RB"
#define MCU_INFO_FLASH      "512K"
#define MCU_INFO_RAM        "144K"
#elif defined(STM32407xx)  
#define MCU_INFI_NAME       "STM32F407VE"
#define MCU_INFO_FLASH      "512K"
#define MCU_INFO_RAM        "128K"
#endif


typedef struct {
    uint32_t mcu_clk;
    uint32_t step_tim_clk;   
}grbl_hw_t;


void grblReprotMcuInfo(void);
void grblHwInfoGet(void);
void grblHwInit(void);

#endif

