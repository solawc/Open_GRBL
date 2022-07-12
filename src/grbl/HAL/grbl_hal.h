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

// hal header
#include "STM32/hal_gpio.h"
#include "STM32/hal_uart.h"
// #include "hal_i2c.h"
#include "STM32/hal_flash_eeprom.h"
#include "STM32/hal_spi.h"
#include "STM32/hal_tim.h"


#include "grbl/HAL/Peripheral/hal_w25qxx.h"

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

/*
 * 这是一个用于保存grbl需求信息的结构体
 * 它需要包含一下内容：
 * 1、MCU主频
 * 2、定时器主频
*/ 
typedef struct {
    uint32_t mcu_clk;
    uint32_t step_tim_clk;   
}grbl_hw_t;

typedef struct {

/*********************************************
 * Motor
 * ******************************************/
    void (*motor_pin_init)(void *);   
    void (*motor_set_dir)(uint8_t mask); 
    void (*motor_set_en)(bool status);
    uint8_t (*motor_get_dir)(uint8_t axis);
    uint8_t (*motor_get_axis)(uint8_t axis);

/*********************************************
 * Limit
 * ******************************************/
    void (*limit_pin_init)(void *);
    void (*limit_pin_isr)(uint16_t pin);
    void (*limit_irq_enable)(void *);
    void (*limit_irq_disable)(void *);
    uint8_t (*limit_get_status)(uint8_t axis);
    uint8_t (*limit_get_all)(uint8_t bit);
    
}hal_gpio_t;


typedef struct{



}hal_t;



void grbl_report_mcu_info(void);
void grbl_hw_info_get(void);
void grbl_hw_init(void);


#endif

