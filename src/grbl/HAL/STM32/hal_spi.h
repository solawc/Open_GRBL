/*
 hal_spi.h

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef hal_spi_h
#define hal_spi_h

#include "../../../main.h"

extern SPI_HandleTypeDef w25qxx_spi;

void spi_for_w25qxx_init(void);

uint8_t w25qxx_spi_read_write(uint8_t data);

void spi_for_tft_init(void);

#endif

