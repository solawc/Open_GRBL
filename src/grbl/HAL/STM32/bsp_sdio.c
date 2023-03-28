/*
 bsp_sdio.c

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "bsp_sdio.h"

#ifdef SD_USE_SDIO

SD_HandleTypeDef SD_HANDLER;
HAL_SD_CardInfoTypeDef SDCardInfo;

uint8_t bsp_sdio_init() {

    HAL_StatusTypeDef SD_Error;

    SD_HANDLER.Instance = SDIO;
    SD_HANDLER.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
    SD_HANDLER.Init.ClockBypass=SDIO_CLOCK_BYPASS_DISABLE;
    SD_HANDLER.Init.ClockPowerSave=SDIO_CLOCK_POWER_SAVE_DISABLE;
    SD_HANDLER.Init.BusWide=SDIO_BUS_WIDE_1B;
    SD_HANDLER.Init.HardwareFlowControl= SDIO_HARDWARE_FLOW_CONTROL_DISABLE;//关闭硬件流控
    SD_HANDLER.Init.ClockDiv=SDIO_TRANSFER_CLK_DIV;

    //SD 传输时钟频率最大 25MHZ
    SD_Error = HAL_SD_Init(&SD_HANDLER);

    if(SD_Error!=HAL_OK) return 1;

    //获取 SD 卡信息
    HAL_SD_GetCardInfo(&SD_HANDLER, &SDCardInfo);

    SD_Error=HAL_SD_ConfigWideBusOperation(&SD_HANDLER,

    SDIO_BUS_WIDE_4B);//使能宽总线模式

    if(SD_Error!=HAL_OK) return 2;

    return 0;
}

#endif