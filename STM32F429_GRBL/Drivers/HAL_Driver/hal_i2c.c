#include "hal_i2c.h"

I2C_HandleTypeDef flash_hi2c;


void hal_i2c_gpio_init(void) {

    GPIO_InitTypeDef GPIO_InitStruct;
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C1_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    __HAL_RCC_I2C1_CLK_ENABLE();
}

void hal_i2c1_init(void) {

    hal_i2c_gpio_init();

    flash_hi2c.Instance = I2C1;
    flash_hi2c.Init.ClockSpeed = 400000;
    flash_hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
    flash_hi2c.Init.OwnAddress1 = 0;
    flash_hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    flash_hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    flash_hi2c.Init.OwnAddress2 = 0;
    flash_hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    flash_hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if(HAL_I2C_Init(&flash_hi2c) != HAL_OK) {
        Error_Handler();
    }
    
    if (HAL_I2CEx_ConfigAnalogFilter(&flash_hi2c, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_I2CEx_ConfigDigitalFilter(&flash_hi2c, 0) != HAL_OK)
    {
        Error_Handler();
    }
}







