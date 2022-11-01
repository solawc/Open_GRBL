/*
 mid_spi.h

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __mid_spi_h
#define __mid_spi_h

#include "../../../main.h"

#ifdef CPU_STM32
typedef SPI_HandleTypeDef   BSP_SPI_HandleTypeDef;
typedef GPIO_InitTypeDef    BSP_GPIO_HandleTypeDef;
#endif

typedef struct {

    bool (*spi_init)(BSP_SPI_HandleTypeDef*);
    void (*spi_clk_enable)(void);
    void (*spi_clk_disable)(void);
    void (*spi_trans_enable)(void);
    void (*spi_trans_end)(void);
    uint8_t (*spi_trans_byte)(BSP_SPI_HandleTypeDef*, uint8_t);
    void (*spi_trans_buff)(BSP_SPI_HandleTypeDef*, uint8_t*, uint8_t*, uint32_t);


    void (*spi_gpio_init)(void);

}dev_spi_t;



#endif
