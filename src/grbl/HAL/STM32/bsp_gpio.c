/*
 bsp_gpio.c

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "bsp_gpio.h"

void BspGpioSet(GPIO_TypeDef *GPIOx, uint16_t PIN, GPIO_InitTypeDef *settings) {
	settings->Pin = PIN;
	HAL_GPIO_Init(GPIOx, settings);
}

/*******************************************************************************
 * Choose limits pins need know, if use st mcu ,you must konw pins interrupt 
 * int whitch exit line? you'd best make the pins in the same exit line! than 
 * you just need to use the same irq handle function to deal with the job.
*******************************************************************************/
void BspLimitGpioInit(void) {

	GPIO_InitTypeDef GPIO_Init = {0};
	GPIO_Init.Mode = GPIO_MODE_IT_RISING;
	GPIO_Init.Pull = GPIO_NOPULL;

#ifdef LIMIT_X_PIN
	GPIO_Init.Pin = LIMIT_X_PIN;
    HAL_GPIO_Init(LIMIT_X_PORT, &GPIO_Init);
#endif

#ifdef LIMIT_Y_PIN
	GPIO_Init.Pin = LIMIT_Y_PIN;
    HAL_GPIO_Init(LIMIT_Y_PORT, &GPIO_Init);
#endif

#ifdef LIMIT_Z_PIN 
	GPIO_Init.Pin = LIMIT_Z_PIN;
    HAL_GPIO_Init(LIMIT_Z_PORT, &GPIO_Init);
#endif
}

void BspLimitGpioIrqEnable(void) {

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(LIMIT_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(LIMIT_IRQn);
}

void BspLimitGpioIrqDisable(void) {

	HAL_NVIC_DisableIRQ(LIMIT_IRQn);
}

void hal_probe_gpio_init(void) {

	GPIO_InitTypeDef GPIO_Init = {
		.Mode = MODE_INPUT,
		.Pull = GPIO_NOPULL,
		.Speed = GPIO_SPEED_FREQ_HIGH,
	};

	GPIO_Init.Pin = PROBE_PIN;
    HAL_GPIO_Init(PROBE_PORT, &GPIO_Init);
}

uint8_t hal_probe_gpio_read(void) {

	return HAL_GPIO_ReadPin(PROBE_PORT, PROBE_PIN); 
}

uint8_t BspLimitGetState(uint8_t axis) {
#ifdef LIMIT_X_PIN
	if(axis == X_AXIS) 			return HAL_GPIO_ReadPin(LIMIT_X_PORT, LIMIT_X_PIN);
#ifdef LIMIT_Y_PIN
		else if(axis == Y_AXIS)		return HAL_GPIO_ReadPin(LIMIT_Y_PORT, LIMIT_Y_PIN);
#endif

#ifdef LIMIT_Z_PIN
	else if(axis == Z_AXIS)		return HAL_GPIO_ReadPin(LIMIT_Z_PORT, LIMIT_Z_PIN);
#endif
    else return 0;
#else 
	return 0;
#endif
}

uint8_t BspLimitGetAllState(uint8_t bit_select) {

	uint8_t limit_status = 0x00;
	
	limit_status |= HAL_GPIO_ReadPin(LIMIT_X_PORT, LIMIT_X_PIN) << 0;
	limit_status |= (HAL_GPIO_ReadPin(LIMIT_Y_PORT, LIMIT_Y_PIN)) << 1;
#ifdef LIMIT_Z_PIN
	limit_status |= (HAL_GPIO_ReadPin(LIMIT_Y_PORT, LIMIT_Y_PIN)) << 2;
#endif
	return limit_status;
}


static void hal_motor_en_gpio_init(void) {

	GPIO_InitTypeDef GPIO_Init; 

	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;

#ifdef STEP_EN_PORT
	GPIO_Init.Pin = STEP_EN_PIN;
    HAL_GPIO_Init(STEP_EN_PORT, &GPIO_Init);
#endif

#ifdef STEP_X_EN_PORT
	GPIO_Init.Pin = STEP_X_EN_PIN;
    HAL_GPIO_Init(STEP_X_EN_PORT, &GPIO_Init);
#endif

#ifdef STEP_Y_EN_PORT
	GPIO_Init.Pin = STEP_Y_EN_PIN;
    HAL_GPIO_Init(STEP_Y_EN_PORT, &GPIO_Init);
#endif

#ifdef STEP_Z_EN_PORT
	GPIO_Init.Pin = STEP_Z_EN_PIN;
    HAL_GPIO_Init(STEP_Z_EN_PORT, &GPIO_Init);
#endif

}

static void hal_motor_dir_gpio_init(void) {

	GPIO_InitTypeDef GPIO_Init; 
	
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;

	GPIO_Init.Pin = MOTOR_X_DIR_PIN;
    HAL_GPIO_Init(MOTOR_X_DIR_PORT, &GPIO_Init);

	GPIO_Init.Pin = MOTOR_Y_DIR_PIN;
    HAL_GPIO_Init(MOTOR_Y_DIR_PORT, &GPIO_Init);
#ifdef MOTOR_Z_DIR_PIN
	GPIO_Init.Pin = MOTOR_Z_DIR_PIN;
    HAL_GPIO_Init(MOTOR_Z_DIR_PORT, &GPIO_Init);
#endif
}

static void hal_motor_axis_gpio_init(void) {

	GPIO_InitTypeDef GPIO_Init; 

	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;

	GPIO_Init.Pin = MOTOR_X_AXIS_PIN;
    HAL_GPIO_Init(MOTOR_X_AXIS_PORT, &GPIO_Init);

	GPIO_Init.Pin = MOTOR_Y_AXIS_PIN;
    HAL_GPIO_Init(MOTOR_Y_AXIS_PORT, &GPIO_Init);
#ifdef MOTOR_Z_AXIS_PIN
	GPIO_Init.Pin = MOTOR_Z_AXIS_PIN;
    HAL_GPIO_Init(MOTOR_Z_AXIS_PORT, &GPIO_Init);
#endif
}


void BspStepGpioInit(void) {
	hal_motor_en_gpio_init();
	hal_motor_dir_gpio_init();
	hal_motor_axis_gpio_init();
}


void BspSetGpioStepEnable(bool status) {
	if(status) { 
	#ifdef STEP_EN_PORT
		HAL_GPIO_WritePin(STEP_EN_PORT, STEP_EN_PIN, GPIO_PIN_SET); 
	#endif

	#ifdef STEP_X_EN_PORT
		HAL_GPIO_WritePin(STEP_X_EN_PORT, STEP_X_EN_PIN, GPIO_PIN_SET); 
	#endif

	#ifdef STEP_Y_EN_PORT
		HAL_GPIO_WritePin(STEP_Y_EN_PORT, STEP_Y_EN_PIN, GPIO_PIN_SET); 
	#endif

	#ifdef STEP_Z_EN_PORT
		HAL_GPIO_WritePin(STEP_Z_EN_PORT, STEP_Z_EN_PIN, GPIO_PIN_SET); 
	#endif 
	}
	else { 
	#ifdef STEP_EN_PORT
		HAL_GPIO_WritePin(STEP_EN_PORT, STEP_EN_PIN, GPIO_PIN_RESET); 
	#endif

	#ifdef STEP_X_EN_PORT
		HAL_GPIO_WritePin(STEP_X_EN_PORT, STEP_X_EN_PIN, GPIO_PIN_RESET); 
	#endif

	#ifdef STEP_Y_EN_PORT
		HAL_GPIO_WritePin(STEP_Y_EN_PORT, STEP_Y_EN_PIN, GPIO_PIN_RESET); 
	#endif

	#ifdef STEP_Z_EN_PORT
		HAL_GPIO_WritePin(STEP_Z_EN_PORT, STEP_Z_EN_PIN, GPIO_PIN_RESET); 
	#endif 
	}
}

void BspSetGpioDirState(uint8_t mask) {

	if(mask & 0x01) {HAL_GPIO_WritePin(MOTOR_X_DIR_PORT, MOTOR_X_DIR_PIN, GPIO_PIN_SET);}
	else {HAL_GPIO_WritePin(MOTOR_X_DIR_PORT, MOTOR_X_DIR_PIN, GPIO_PIN_RESET);}

	if(mask & 0x02) {HAL_GPIO_WritePin(MOTOR_Y_DIR_PORT, MOTOR_Y_DIR_PIN, GPIO_PIN_SET);}
	else {HAL_GPIO_WritePin(MOTOR_Y_DIR_PORT, MOTOR_Y_DIR_PIN, GPIO_PIN_RESET);}

#ifdef MOTOR_Z_AXIS_PIN
	if(mask & 0x04) {HAL_GPIO_WritePin(MOTOR_Z_DIR_PORT, MOTOR_Z_DIR_PIN, GPIO_PIN_SET);}
	else {HAL_GPIO_WritePin(MOTOR_Z_DIR_PORT, MOTOR_Z_DIR_PIN, GPIO_PIN_RESET);}
#endif
}


void BspSetGpioStepState(uint8_t mask) {

	if(mask & 0x01) {HAL_GPIO_WritePin(MOTOR_X_AXIS_PORT, MOTOR_X_AXIS_PIN, GPIO_PIN_SET);}
	else {HAL_GPIO_WritePin(MOTOR_X_AXIS_PORT, MOTOR_X_AXIS_PIN, GPIO_PIN_RESET);}

	if(mask & 0x02) {HAL_GPIO_WritePin(MOTOR_Y_AXIS_PORT, MOTOR_Y_AXIS_PIN, GPIO_PIN_SET);}
	else {HAL_GPIO_WritePin(MOTOR_Y_AXIS_PORT, MOTOR_Y_AXIS_PIN, GPIO_PIN_RESET);}

	#ifdef MOTOR_Z_AXIS_PIN
		if(mask & 0x04) {HAL_GPIO_WritePin(MOTOR_Z_AXIS_PORT, MOTOR_Z_AXIS_PIN, GPIO_PIN_SET);}
		else {HAL_GPIO_WritePin(MOTOR_Z_AXIS_PORT, MOTOR_Z_AXIS_PIN, GPIO_PIN_RESET);}
	#endif
}


uint8_t BspGetStepDirMask(uint8_t axis) {
	if(axis == X_AXIS) return 0x01;
	else if(axis == Y_AXIS)	return 0x02;
	else return 0x04;
}

uint8_t BspGetStepGpioMask(uint8_t axis) {
	
	if(axis == X_AXIS) return 0x01;
	else if(axis == Y_AXIS)	return 0x02;
	else return 0x04;
}


void hal_coolant_pin_init(void) {

	GPIO_InitTypeDef GPIO_Init; 
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

#ifdef FLOOD_PORT
	GPIO_Init.Pin = FLOOD_PIN;
    HAL_GPIO_Init(FLOOD_PORT, &GPIO_Init);
#endif
	GPIO_Init.Pin = MIST_PIN;
    HAL_GPIO_Init(MIST_PORT, &GPIO_Init);
}


void set_coolant_flood(bool status) {
#ifdef FLOOD_PORT
	if(status){
		HAL_GPIO_WritePin(FLOOD_PORT, FLOOD_PIN, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(FLOOD_PORT, FLOOD_PIN, GPIO_PIN_RESET);
	}
#endif
} 

void set_coolant_mist(bool status) {
	if(status){
		HAL_GPIO_WritePin(MIST_PORT, MIST_PIN, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(MIST_PORT, MIST_PIN, GPIO_PIN_RESET);
	}
} 


uint8_t get_coolant_flood(void) {
#ifdef FLOOD_PORT
	uint32_t odr;
	odr = FLOOD_PORT->ODR;
	return (odr & FLOOD_PIN);
#else 
	return 0;
#endif
}

uint8_t get_coolant_mist(void) {

	uint32_t odr;

	odr = MIST_PORT->ODR;

	return (odr & MIST_PIN);
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

int regs_to_pin(GPIO_TypeDef  *regs, uint32_t bit) {
	int i;
    for (i=0; i<ARRAY_SIZE(digital_regs); i++)
        if (digital_regs[i] == regs)
            return GPIO('A' + i, ffs(bit)-1);
    return 0;
}

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



struct test_io {

	struct gpio_out test_io0;

};

struct test_io test_io_obj;

#define LED_GPIO_PIN		regs_to_pin(GPIOA, 4)

void goio_test_init(void) {

	test_io_obj.test_io0 = gpio_out_setup(LED_GPIO_PIN, 0);
}

void gpio_test_run(void) {

	while(1) {
		gpio_out_write(test_io_obj.test_io0, 0);
		delay_ms(1000);
		gpio_out_write(test_io_obj.test_io0, 1);
		delay_ms(1000);
	}
}









