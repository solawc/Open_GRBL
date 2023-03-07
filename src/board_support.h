/*
 board_support.h

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __board_support_h
#define __board_support_h

#include HAL_PATH(grbl_hal.h)
#include HAL_PATH(grbl_mb.h)

#if MB_BOARD==BOARD_FIRE_CHALLENGER
    #include HAL_BSP_PATH(bsp_FireBoard_F429V2/hal_FireBoard_system.h)
    #include HAL_PINS_PATH(pins_fireboard_f429.h)
#elif MB_BOARD==BOARD_NUCLEO_G070RB
    #include HAL_BSP_PATH(bsp_nucleo_g070rb/hal_nucleo_g070rb.h)
    #include HAL_PINS_PATH(pins_nucleo_g070rb.h)
#elif MB_BOARD==BOARD_MKS_DLC_LG0_V3
    #include HAL_BSP_PATH(bsp_mks_dlc_lg0_v3/bsp_mks_dlc_lg0_v3_system.h)
    #include HAL_PINS_PATH(pins_mks_dlc_lg0_v3.h)
#elif MB_BOARD==BOARD_MKS_ROBIN_NANO_V3
    #include HAL_BSP_PATH(bsp_mks_nano_v3/hal_robin_nano_v3_system.h)
    #include HAL_PINS_PATH(pins_mks_nano_v3.h)
#endif


#endif /* __board_support_h */