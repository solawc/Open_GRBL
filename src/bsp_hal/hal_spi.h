#ifndef hal_spi_h
#define hal_spi_h

#include "main.h"

#define USE_SD_SPI
#define USE_TFT_SPI

#define SPI_DIV(div)  SPI_BAUDRATEPRESCALER_##div
#define SPI_NUM(num)  SPI##num
#define SPI_CLK_ENABLE(spi) __HAL_RCC_##spi##_CLK_ENABLE

typedef enum {
    SPI_1,
    SPI_2,
    SPI_3,
    SPI_4,
    SPI_5,
    // ..
}spi_num_t;

typedef enum {
    spi_mode_0,
    spi_mode_1,
    spi_mode_2,
    spi_mode_3,
}spi_mode_t;

typedef enum {
    size_8bit_date,
    size_16bit_date,
}spi_date_size_t;

typedef enum {
    master_full_trans,
    master_hard_trans_tx,
    master_hard_trans_rx,
    salve_full_trans,
    salve_hard_trans_tx,
    salve_hard_trans_rx,
}spi_trans_mode_t;

typedef enum {
    trans_msb_mode,
    trans_lsb_mode,
}spi_frist_bit_t;


typedef struct {
    spi_num_t           spi_num;
    uint32_t             spi_speed;
    spi_mode_t          spi_mode_set;
    spi_date_size_t     spi_date_size;
    spi_frist_bit_t     spi_frist_bit;
    spi_trans_mode_t    spi_trans_mode;
    bool            is_use_irq;
}spi_setting_t;


typedef struct {

#ifdef USE_HAL_DRIVER
    SPI_HandleTypeDef hal_spi;
#endif
    bool __spi_intrans;
    bool is_use_dma;
    void (* dev_spi_gpio_init_cb)(void);
    void (* dev_spi_init_cb)(void);
    void (* dev_spi_set_speed)(uint32_t speed);
    void (* dev_spi_data_mode)(uint32_t mode);
    uint16_t (* dev_spi_read_write_byte)(uint16_t data);
    void (* dev_spi_read_write_dma)(uint8_t buff, uint32_t size);        
}dev_spi_t;


// #define SPI_DMA_SEND_BUFF           65535
// #define SPI_DMA_READ_BUFF           65535

#define SPI_DMA_BUFF_SIZE               65535

typedef struct {

    DMA_HandleTypeDef dma_tx;
    DMA_HandleTypeDef dma_rx;

    uint8_t spi_dma_trans_buff[SPI_DMA_BUFF_SIZE];
    uint8_t spi_dma_read_buff[SPI_DMA_BUFF_SIZE];

    void(*dev_spi_dma_init)(void);
    void(*dev_spi_dma_trans_enable)(void);
    void(*dev_spi_dma_trans_diasble)();
    void(*dev_spi_dma_trans_buff)(uint8_t *, uint32_t );
    void(*dev_spi_dma_read_buff)(uint8_t *, uint32_t );
    void(*dev_spi_dma_trans_read_buff)(uint8_t *, uint8_t *, uint32_t );

    bool(*dev_is_spi_dma_busy)(void);
}dev_spi_dma_t;
extern dev_spi_dma_t w25qxx_dma;

void hal_spi_begin(dev_spi_t *drv, spi_setting_t *setting);
void hal_spi_register(dev_spi_t *dev_spi);
void hal_set_bit_order(dev_spi_t *drv, spi_setting_t *setting);
uint8_t hal_spi_transfer_revice_byte(dev_spi_t *drv, uint8_t byte);


void hal_spi_dma_init(dev_spi_dma_t *dev);

#endif

