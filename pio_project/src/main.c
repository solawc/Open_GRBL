#include "main.h"

void led_init(void) {

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



int main() {

    HAL_Init();

    hal_f429_system_init();

    hal_uart_init();

    led_init();

    grbl_report_mcu_info();

    while(1) {
        hal_led_toggle();
        HAL_Delay(500);
    }
}


void SysTick_Handler(void)
{
    HAL_IncTick();
}