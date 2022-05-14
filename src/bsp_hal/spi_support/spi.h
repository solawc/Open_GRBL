#ifndef __spi_h
#define __spi_h

#include "../../main.h"

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3



typedef struct {

    uint8_t _spi_num;
    uint16_t _spi_clk;
    uint16_t _spi_miso;
    uint16_t _spi_mosi;
    uint16_t _spi_cs;

    uint8_t _div;
    
    bool _in_transaction;
}spi_t;


#endif