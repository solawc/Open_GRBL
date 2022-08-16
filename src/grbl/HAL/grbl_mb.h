#ifndef __grbl_mb_h
#define __grbl_mb_h

#include "grbl_hal.h"

/* Cortex-CM0+ */
#define BOARD_LASER_V1_0_BOX                    1000
#define BOARD_LASER_BOX_4AXIS                   1001
#define BOARD_NUCLEO_G070RB                     1002
/* Cortex-CM4 */
#define BOARD_FIRE_BOARD_F429                   4000

/* Define Mother Board */
#if MB_BOARD==BOARD_FIRE_BOARD_F429
    #define SYSTEM_INTI()                   hal_f429_system_init()
#elif MB_BOARD==BOARD_LASER_V1_0_BOX
    #define SYSTEM_INTI()                   hal_g0b0_system_init()
#elif MB_BOARD==BOARD_LASER_BOX_4AXIS
    #define SYSTEM_INTI()                   hal_nucleo_g070rb_system_init()
#elif MB_BOARD==BOARD_NUCLEO_G070RB
    #define SYSTEM_INTI()                   hal_nucleo_g070rb_system_init()              
#endif


#endif