#ifndef __grbl_hal_h
#define __grbl_hal_h


#include "main.h"
#include "stdbool.h"


// hal header
#include "hal_gpio.h"
#include "hal_uart.h"
#include "hal_i2c.h"
#include "hal_flash_eeprom.h"
#include "hal_spi.h"
#include "hal_tim.h"
//
#include "led_task.h"
#include "hal_w25qxx.h"

#if USE_ESP32_MCU
#define ISR_CODE ARR_IRM
#else
#define ISR_CODE
#endif 










#endif

