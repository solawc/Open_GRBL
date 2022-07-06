#include "mid_gpio.h"

mid_gpio_t dev_gpio;

/* 通用GPIO初始化 */
void dev_gpio_init() {

    dev_gpio.limit_gpio_init = hal_limit_gpio_init;
    dev_gpio.limit_irq_enable = hal_limit_gpio_irq_enable;
    dev_gpio.limit_irq_disable = hal_limit_gpio_irq_disable;
    dev_gpio.limit_get_state = hal_get_all_limits_status;
    dev_gpio.limit_get_mask = hal_limits_get_gpio_status;

    dev_gpio.motor_gpio_init = hal_motor_gpio_init;
    dev_gpio.motor_set_dir = hal_set_dir_gpio_status;
    dev_gpio.motor_set_en = hal_step_en_gpio_set;
    dev_gpio.motor_set_step = hal_set_step_gpio_status;
    dev_gpio.motor_get_dir_mask = hal_get_moter_dir_gpio_mask;
    dev_gpio.motor_get_step_mask = hal_get_moter_axis_gpio_mask;

    dev_gpio.probe_gpio_init = hal_probe_gpio_init;
    dev_gpio.probe_gpio_read = hal_probe_gpio_read;

    dev_gpio.coolant_gpio_init = hal_coolant_pin_init;
    dev_gpio.coolant_set_flood = set_coolant_flood;
    dev_gpio.coolant_set_mist = set_coolant_mist;
    dev_gpio.coolant_get_flood = get_coolant_flood;
    dev_gpio.coolant_get_mist = get_coolant_mist;
}