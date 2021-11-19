#include "main.h"

int main() {

    HAL_Init();

    hal_f429_system_init();

    hal_uart_init();

    grbl_report_mcu_info();

    while(1) {

        
    }
}