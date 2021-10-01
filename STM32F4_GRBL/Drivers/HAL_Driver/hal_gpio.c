#include "hal_gpio.h"
#include "grbl.h"



void hal_led_gpio_init(void) {
	
    GPIO_InitTypeDef GPIO_Init; 
	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pin = GPIO_PIN_10;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOH, &GPIO_Init);
}

void hal_led_on(void) {
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10, GPIO_PIN_RESET);
}

void hal_led_off(void) {
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10, GPIO_PIN_SET);
}

void hal_led_toggle(void) {
	HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_10);
}

/*
	Choose limits pins need know, if use st mcu ,you must konw pins interrupt 
	int whitch exit line? you'd best make the pins in the same exit line! than 
	you just need to use the same irq handle function to deal with the job.
*/
void hal_limit_gpio_init(void) {

	GPIO_InitTypeDef GPIO_Init = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_Init.Mode = GPIO_MODE_IT_RISING;
	GPIO_Init.Pull = GPIO_NOPULL;

	GPIO_Init.Pin = LIMIT_X_PIN;
    HAL_GPIO_Init(LIMIT_X_PORT, &GPIO_Init);

	GPIO_Init.Pin = LIMIT_Y_PIN;
    HAL_GPIO_Init(LIMIT_Y_PORT, &GPIO_Init);

	GPIO_Init.Pin = LIMIT_Z_PIN;
    HAL_GPIO_Init(LIMIT_Z_PORT, &GPIO_Init);
}

void hal_limit_gpio_irq_enable(void) {

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void hal_limit_gpio_irq_disable(void) {

	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
}

uint8_t hal_limits_get_gpio_status(uint8_t axis) {
	if(axis == X_AXIS) 			return HAL_GPIO_ReadPin(LIMIT_X_PORT, LIMIT_X_PIN);
	else if(axis == Y_AXIS)		return HAL_GPIO_ReadPin(LIMIT_Y_PORT, LIMIT_Y_PIN);
	else if(axis == Z_AXIS)		return HAL_GPIO_ReadPin(LIMIT_Z_PORT, LIMIT_Z_PIN);
    else return 255;
}


static void hal_motor_en_gpio_init(void) {

	GPIO_InitTypeDef GPIO_Init; 
	
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;

	GPIO_Init.Pin = STEP_EN_PIN;
    HAL_GPIO_Init(STEP_EN_PORT, &GPIO_Init);
}

static void hal_motor_dir_gpio_init(void) {

	GPIO_InitTypeDef GPIO_Init; 
	
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_Init.Mode = GPIO_MODE_INPUT;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;

	GPIO_Init.Pin = MOTOR_X_DIR_PIN;
    HAL_GPIO_Init(MOTOR_X_DIR_PORT, &GPIO_Init);

	GPIO_Init.Pin = MOTOR_Y_DIR_PIN;
    HAL_GPIO_Init(MOTOR_Y_DIR_PORT, &GPIO_Init);

	GPIO_Init.Pin = MOTOR_Z_DIR_PIN;
    HAL_GPIO_Init(MOTOR_Z_DIR_PORT, &GPIO_Init);
}

static void hal_motor_axis_gpio_init(void) {

	GPIO_InitTypeDef GPIO_Init; 
	
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;

	GPIO_Init.Pin = MOTOR_X_AXIS_PIN;
    HAL_GPIO_Init(MOTOR_X_AXIS_PORT, &GPIO_Init);

	GPIO_Init.Pin = MOTOR_Y_AXIS_PIN;
    HAL_GPIO_Init(MOTOR_Y_AXIS_PORT, &GPIO_Init);

	GPIO_Init.Pin = MOTOR_Z_AXIS_PIN;
    HAL_GPIO_Init(MOTOR_Z_AXIS_PORT, &GPIO_Init);
}


void hal_motor_gpio_init(void) {

	hal_motor_en_gpio_init();
	hal_motor_dir_gpio_init();
	hal_motor_axis_gpio_init();
}

void hal_step_en_gpio_set(bool status) {
	if(status) { HAL_GPIO_WritePin(STEP_EN_PORT, STEP_EN_PIN, GPIO_PIN_SET); }
	else { HAL_GPIO_WritePin(STEP_EN_PORT, STEP_EN_PIN, GPIO_PIN_RESET); }
}

uint8_t hal_return_axix_gpio_status(uint8_t axis) {
	uint8_t mask = 0;
	switch(axis) {
		case X_AXIS: mask = READ_BIT(MOTOR_X_AXIS_PORT->ODR, MOTOR_X_AXIS_PIN); break;
		case Y_AXIS: mask = READ_BIT(MOTOR_Y_AXIS_PORT->ODR, MOTOR_Y_AXIS_PIN); break;
		case Z_AXIS: mask = READ_BIT(MOTOR_Z_AXIS_PORT->ODR, MOTOR_Z_AXIS_PIN); break;
	}
	return mask;
}

uint8_t hal_return_dir_gpio_status(uint8_t axis) {

	uint8_t mask = 0;
	switch(axis) {
		case X_AXIS: mask = READ_BIT(MOTOR_X_DIR_PORT->ODR, MOTOR_X_DIR_PIN); break;
		case Y_AXIS: mask = READ_BIT(MOTOR_Y_DIR_PORT->ODR, MOTOR_Y_DIR_PIN); break;
		case Z_AXIS: mask = READ_BIT(MOTOR_Z_DIR_PORT->ODR, MOTOR_Z_DIR_PIN); break;
	}
	return mask;
}

uint8_t hal_get_moter_dir_gpio_mask(uint8_t axis) {

	// uint8_t mask = 0;
	// mask |= hal_return_dir_gpio_status(Z_AXIS) << 2;
	// mask |= hal_return_dir_gpio_status(Y_AXIS) << 1;
	// mask |= hal_return_dir_gpio_status(X_AXIS) << 0;
	// mask = hal_return_dir_gpio_status(axis);
	if(axis == X_AXIS) return 0x01;// hal_return_dir_gpio_status(X_AXIS) << 0;
	else if(axis == Y_AXIS)	return 0x02;//hal_return_dir_gpio_status(Y_AXIS) << 1;
	else if(axis == Z_AXIS)	return 0x04;// hal_return_dir_hal_return_dir_gpio_status(Z_AXIS) << 2;
	// return mask;
}

uint8_t hal_get_moter_axis_gpio_mask(uint8_t axis) {
	// uint8_t mask = 0;
	// mask |= hal_return_axix_gpio_status(Z_AXIS) << 2;
	// mask |= hal_return_axix_gpio_status(Y_AXIS) << 1;
	// mask |= hal_return_axix_gpio_status(X_AXIS) << 0;
	if(axis == X_AXIS) return hal_return_axix_gpio_status(X_AXIS) << 0;
	else if(axis == Y_AXIS)	return hal_return_axix_gpio_status(Y_AXIS) << 1;
	else return hal_return_axix_gpio_status(Z_AXIS) << 2;
}








