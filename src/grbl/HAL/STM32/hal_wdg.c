#include "hal_wdg.h"

IWDG_HandleTypeDef hiwdg;

void hal_wdg_init(void) {

    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_64;
    // hiwdg.Init.Window = 4095;
    hiwdg.Init.Reload = 4095;
    if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
    {
        Error_Handler();
    }
}

void hal_feedWDG(void) {

    HAL_IWDG_Refresh(&hiwdg);
}








