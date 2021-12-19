#ifndef __grbl_hal_h
#define __grbl_hal_h


#include "main.h"
#include "stdbool.h"

#include "grbl_config.h"

// hal header
// #include "hal_gpio.h"
#include "hal_uart.h"
// #include "hal_i2c.h"
#include "hal_flash_eeprom.h"
// #include "hal_spi.h"
// #include "hal_tim.h"
// 
// #include "led_task.h"
// #include "hal_w25qxx.h"

#ifdef STM32F429xx
#define MCU_INFI_NAME       "STM32F429IG"
#define MCU_INFO_FLASH      "1024K"
#define MCU_INFO_RAM        "512K"
#elif defined(STM32G0B0xx) 
#define MCU_INFI_NAME       "STM32G0B0CE"
#define MCU_INFO_FLASH      "512K"
#define MCU_INFO_RAM        "144K"
#endif

void grbl_report_mcu_info(void);




#endif

