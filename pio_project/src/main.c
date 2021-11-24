#include "main.h"

int main() {

    HAL_Init();

    hal_f429_system_init();

    hal_uart_init();

    hal_led_gpio_init();

    w25qxx_init();

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