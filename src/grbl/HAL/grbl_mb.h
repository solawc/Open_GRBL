#ifndef __grbl_mb_h
#define __grbl_mb_h

#include "grbl_hal.h"

/* Cortex-CM0+ */
#define BOARD_NUCLEO_G070RB                     1000
/* Cortex-CM4 */
#define BOARD_FIRE_BOARD_F429                   4000
#define BOARD_MKS_DLC_LG0_V3                    4001

/* Define Mother Board */
#if MB_BOARD==BOARD_FIRE_BOARD_F429
    #define SYSTEM_INIT()                   Bsp_FireBoard_SystemInit()
#elif MB_BOARD==BOARD_NUCLEO_G070RB
    #define SYSTEM_INIT()                   hal_nucleo_g070rb_system_init()    
#elif MB_BOARD==BOARD_MKS_DLC_LG0_V3
    #define SYSTEM_INIT()                   BspMksDlcLg0SystemInit()
#endif


#endif