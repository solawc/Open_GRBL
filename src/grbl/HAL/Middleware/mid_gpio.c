/*
 mid_gpio.c

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "mid_gpio.h"

mid_gpio_t dev_gpio;

/* 通用GPIO初始化 */
void DevGpioInit(void) {
    dev_gpio.limit_gpio_init = BspLimitGpioInit;
    dev_gpio.limit_irq_enable = BspLimitGpioIrqEnable;
    dev_gpio.limit_irq_disable = BspLimitGpioIrqDisable;
    dev_gpio.limit_get_state = BspLimitGetAllState;
    dev_gpio.limit_get_mask = BspLimitGetState;

    dev_gpio.motor_gpio_init = BspStepGpioInit;
    dev_gpio.motor_set_dir = BspSetGpioDirState;
    dev_gpio.motor_set_en = BspSetGpioStepEnable;
    dev_gpio.motor_set_step = BspSetGpioStepState;
    dev_gpio.motor_get_dir_mask = BspGetStepDirMask;
    dev_gpio.motor_get_step_mask = BspGetStepGpioMask;

    dev_gpio.probe_gpio_init = hal_probe_gpio_init;
    dev_gpio.probe_gpio_read = hal_probe_gpio_read;

    dev_gpio.coolant_gpio_init = hal_coolant_pin_init;
    dev_gpio.coolant_set_flood = set_coolant_flood;
    dev_gpio.coolant_set_mist = set_coolant_mist;
    dev_gpio.coolant_get_flood = get_coolant_flood;
    dev_gpio.coolant_get_mist = get_coolant_mist;
}