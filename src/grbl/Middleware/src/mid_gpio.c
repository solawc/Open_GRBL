/*
 mid_gpio.c

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "../inc/mid_gpio.h"

mid_gpio_t dev_gpio;

/* 通用GPIO初始化 */
void DevGpioInit(void) {
    
    /* for limit */
    dev_gpio.limit_gpio_init        = BspLimitGpioInit;
    dev_gpio.limit_irq_enable       = BspLimitGpioIrqEnable;
    dev_gpio.limit_irq_disable      = BspLimitGpioIrqDisable;
    dev_gpio.limit_get_state        = BspLimitGetAllState;
    dev_gpio.limit_get_mask         = BspLimitGetState;

    /* for motor stepper */
    dev_gpio.motor_gpio_init        = BspStepGpioInit;
    dev_gpio.motor_set_dir          = BspSetGpioDirState;
    dev_gpio.motor_set_en           = BspSetGpioStepEnable;
    dev_gpio.motor_set_step         = BspSetGpioStepState;
    dev_gpio.motor_get_dir_mask     = BspGetStepDirMask;
    dev_gpio.motor_get_step_mask    = BspGetStepGpioMask;

    /* for probe */
    dev_gpio.probe_gpio_init        = hal_probe_gpio_init;
    dev_gpio.probe_gpio_read        = hal_probe_gpio_read;

    /* for coolant */
    dev_gpio.coolant_gpio_init      = hal_coolant_pin_init;
    dev_gpio.coolant_set_flood      = set_coolant_flood;
    dev_gpio.coolant_set_mist       = set_coolant_mist;
    dev_gpio.coolant_get_flood      = get_coolant_flood;
    dev_gpio.coolant_get_mist       = get_coolant_mist;
}

struct motor_gpio {

    struct gpio_out motor_step_x;
    struct gpio_out motor_step_y;
    struct gpio_out motor_step_z;

    struct gpio_out motor_en_x;
    struct gpio_out motor_en_y;
    struct gpio_out motor_en_z;

    struct gpio_out motor_dir_x;
    struct gpio_out motor_dir_y;
    struct gpio_out motor_dir_z;
};

struct motor_gpio stepper;

void motor_init(void) { 

    stepper.motor_step_x = gpio_out_setup(regs_to_pin(MOTOR_X_AXIS_PORT, 4), 0);
    stepper.motor_step_y = gpio_out_setup(regs_to_pin(MOTOR_Y_AXIS_PORT, 6), 0);
    stepper.motor_step_z = gpio_out_setup(regs_to_pin(MOTOR_Z_AXIS_PORT, 8), 0);
}
