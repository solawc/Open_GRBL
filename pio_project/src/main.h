#ifndef __MAIN_H
#define __MAIN_H

#ifdef STM32G070xx
    #include "stm32g0xx_hal.h"
#elif defined(STM32F429xx)
    #include "stm32f4xx_hal.h"
    #include "bsp_hal/bsp_f429ig/hal_f429_system.h"
    #include "bsp_hal/bsp_f429ig/grbl_hal.h"
    #include "bsp_hal/bsp_f429ig/hal_uart.h"
    #include "bsp_hal/bsp_f429ig/grbl_config.h"
    #include "bsp_hal/bsp_f429ig/hal_gpio.h"
    #include "bsp_hal/bsp_f429ig/hal_tim.h"
    #include "bsp_hal/bsp_f429ig/hal_flash_eeprom.h"
    #include "bsp_hal/bsp_f429ig/hal_spi.h"


    #include "bsp_hal/bsp_f429ig/hal_w25qxx.h"
#endif





#endif
