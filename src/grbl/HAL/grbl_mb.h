/*
 grbl_mb.h

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/


#ifndef __grbl_mb_h
#define __grbl_mb_h

#include "grbl_hal.h"

/* Cortex-CM0+ */
#define BOARD_NUCLEO_G070RB                     1000    // STM32G070RB

/* Cortex-CM3 */

/* Cortex-CM4 */

#define BOARD_FIRE_CHALLENGER                   4000    // STM32F429IG
#define BOARD_MKS_DLC_LG0_V3                    4001    // STM32F401RC/STM32F402RC
#define BOARD_MKS_ROBIN_NANO_V3                 4002    // STM32F407VE/STM32F407VG

/* Cortex-CM7 */
#define BOARD_GIGA_R1_WIFI                      7000    // STM32H747XI
#define BOARD_FIRE_H750XB_H743XI_PRO            7001    // STM32H750XB

/* Cortex-M33 */

/* Cortex-M55 */


/* Define Mother Board */
#if MB_BOARD==BOARD_FIRE_CHALLENGER
    #define SYSTEM_INIT()                       Bsp_FireBoard_SystemInit()
#elif MB_BOARD==BOARD_NUCLEO_G070RB
    #define SYSTEM_INIT()                       hal_nucleo_g070rb_system_init()    
#elif MB_BOARD==BOARD_MKS_DLC_LG0_V3
    #define SYSTEM_INIT()                       BspMksDlcLg0SystemInit()
#elif MB_BOARD==BOARD_MKS_ROBIN_NANO_V3
    #define SYSTEM_INIT()                       Bsp_RobinNanoV3_SystemInit()
#endif


#endif