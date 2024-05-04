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

//----------------------------------New driver------------------------------//

GPIO_TypeDef  * const digital_regs[]={
    GPIOA,
    GPIOB,
    GPIOC,
#ifdef GPIOD
    GPIOD,
#endif

#ifdef GPIOE
    GPIOE,
#endif

#ifdef GPIOF
    GPIOF,
#endif

#ifdef GPIOG
    GPIOG,
#endif

#ifdef GPIOH
    GPIOH,
#endif
};

// 校验GPIO端口和pin引脚是否和芯片复合
static int
gpio_valid(uint32_t pin)
{
    uint32_t port = GPIO2PORT(pin);
    return port < ARRAY_SIZE(digital_regs) && digital_regs[port];
}

static void gpio_out_init(GPIO_TypeDef  *GPIOx ,uint32_t gpio_pin, uint32_t val) {

    GPIO_InitTypeDef GPIO_Init;

    HAL_GPIO_WritePin(GPIOx, gpio_pin, (GPIO_PinState)val);

    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Pin = gpio_pin;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOx, &GPIO_Init);
}
 
struct gpio_out 
gpio_out_setup(uint32_t pin, uint32_t val) {

    // HAL CLK Init
    // 在stm32的底层接口上，基本使用HAL库，方便迁移。

    if(gpio_valid(pin)) {
        // error!;
        while(1);
    }

    GPIO_TypeDef  *gpio_port = digital_regs[GPIO2PORT(pin)];

    uint32_t bit = GPIO2BIT(pin);

    gpio_out_init(gpio_port, bit, val);  // 真正初始化的地方

    struct gpio_out g = {.gpio_port=gpio_port,.bit=bit}; //记录并返回对应的GPIO信息

    return g;
}

void gpio_out_write(struct gpio_out g, uint32_t val) {

    HAL_GPIO_WritePin(g.gpio_port, g.bit, (GPIO_PinState)val);
}

struct gpio_in
gpio_in_setup(uint32_t pin, uint32_t val) {

    if(gpio_valid(pin)) {
        // error!;
        while(1);
    }

    GPIO_TypeDef  *gpio_port = digital_regs[GPIO2PORT(pin)];

    uint32_t bit = GPIO2BIT(pin);

    gpio_out_init(gpio_port, bit, val);  // 真正初始化的地方

    struct gpio_in g = {.gpio_port=gpio_port,.bit=bit}; //记录并返回对应的GPIO信息

    return g;

}

