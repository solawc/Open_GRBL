#include "hal_spi.h"

void set_spi_clk(dev_spi_t *drv, uint8_t num) {

    switch(num) {
        case SPI_1: 
#ifdef SPI1
            __HAL_RCC_SPI1_CLK_ENABLE(); 
            drv->hal_spi.Instance = SPI1; 
#endif
            break;
        case SPI_2:
#ifdef SPI2
            __HAL_RCC_SPI2_CLK_ENABLE(); 
            drv->hal_spi.Instance = SPI2; 
#endif
            break;
        case SPI_3: 
#ifdef SPI3
            __HAL_RCC_SPI3_CLK_ENABLE(); 
            drv->hal_spi.Instance = SPI3; 
#endif
            break;
        case SPI_4: 
#ifdef SPI4
            __HAL_RCC_SPI4_CLK_ENABLE(); 
            drv->hal_spi.Instance = SPI4; 
#endif
            break;
        case SPI_5: 
#ifdef SPI5
            __HAL_RCC_SPI5_CLK_ENABLE(); 
            drv->hal_spi.Instance = SPI5; 
#endif 
            break;
    }
}

void set_spi_mode(dev_spi_t *drv, uint8_t num) {

    switch(num) {
        case spi_mode_0: 
            drv->hal_spi.Init.CLKPhase = SPI_PHASE_1EDGE;
            drv->hal_spi.Init.CLKPolarity = SPI_POLARITY_LOW;
        break;
        case spi_mode_1: 
            drv->hal_spi.Init.CLKPhase = SPI_PHASE_1EDGE;
            drv->hal_spi.Init.CLKPolarity = SPI_POLARITY_HIGH;
        break;
        case spi_mode_2: 
            drv->hal_spi.Init.CLKPhase = SPI_PHASE_2EDGE;
            drv->hal_spi.Init.CLKPolarity = SPI_POLARITY_LOW;
        break;
        case spi_mode_3: 
            drv->hal_spi.Init.CLKPhase = SPI_PHASE_2EDGE;
            drv->hal_spi.Init.CLKPolarity = SPI_POLARITY_HIGH;
        break;
    }
}

void set_spi_trans_mode(dev_spi_t *drv, uint8_t num) {

    switch(num) {

        case master_full_trans:
            drv->hal_spi.Init.Mode = SPI_MODE_MASTER;
            drv->hal_spi.Init.Direction = SPI_DIRECTION_2LINES;
        break;

        case master_hard_trans_tx:
            drv->hal_spi.Init.Mode = SPI_MODE_MASTER;
            drv->hal_spi.Init.Direction = SPI_DIRECTION_1LINE;
        break;

        case master_hard_trans_rx:
            drv->hal_spi.Init.Mode = SPI_MODE_MASTER;
            drv->hal_spi.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
        break;

        case salve_full_trans:
            drv->hal_spi.Init.Mode = SPI_MODE_SLAVE;
            drv->hal_spi.Init.Direction = SPI_DIRECTION_2LINES;
        break;

        case salve_hard_trans_tx:
            drv->hal_spi.Init.Mode = SPI_MODE_SLAVE;
            drv->hal_spi.Init.Direction = SPI_DIRECTION_1LINE;
        break;

        case salve_hard_trans_rx:
            drv->hal_spi.Init.Mode = SPI_MODE_SLAVE;
            drv->hal_spi.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
        break;
    }
}

void set_spi_speed(dev_spi_t *drv, uint32_t speed) {
    drv->hal_spi.Init.BaudRatePrescaler = speed;
}

void set_spi_date_size(dev_spi_t *drv, uint8_t num) {
    if(num == size_16bit_date) drv->hal_spi.Init.DataSize = SPI_DATASIZE_16BIT;
    else drv->hal_spi.Init.DataSize = SPI_DATASIZE_8BIT;
}

void set_spi_first_bit(dev_spi_t *drv, uint8_t num) {
    if(num == trans_lsb_mode) drv->hal_spi.Init.FirstBit = SPI_FIRSTBIT_LSB;
    else drv->hal_spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
}

void set_spi_irq_enable(dev_spi_t *drv, bool num) {
    if(num == true) drv->hal_spi.Init.TIMode = SPI_TIMODE_ENABLE;
    else drv->hal_spi.Init.TIMode = SPI_TIMODE_DISABLE;
}

void set_spi_others(dev_spi_t *drv) {
    drv->hal_spi.Init.NSS = SPI_NSS_SOFT;
    drv->hal_spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    drv->hal_spi.Init.CRCPolynomial = 7;
}

void set_spi_start(dev_spi_t *drv) {
    __HAL_SPI_ENABLE(&drv->hal_spi);
}   

uint8_t hal_spi_transfer_revice_byte(dev_spi_t *drv, uint8_t byte) {
    uint8_t rdata = 0;
    HAL_SPI_TransmitReceive(&drv->hal_spi, (uint8_t *)&byte, &rdata, 1,1000);
    return rdata;
}

uint8_t hal_spi_transfer_revice_buff(dev_spi_t *drv, uint8_t byte) {
    uint8_t rdata = 0;
    HAL_SPI_TransmitReceive(&drv->hal_spi, (uint8_t *)&byte, &rdata, 1,1000);
    return rdata;
}

uint8_t hal_spi_trans_revice_buf_dma(dev_spi_t *drv, uint8_t *buf, uint32_t buf_size) {
    
    
    return 0;
}

/*******************************************************************************
 *                                  Warning
 *  Do not change the code if it is not necessary
 *******************************************************************************/
void hal_spi_begin(dev_spi_t *drv, spi_setting_t *setting) {

    // enable spi clk
    set_spi_clk(drv, setting->spi_num);

    // set spi speed
    set_spi_speed(drv, setting->spi_speed);

    // set spi mode
    set_spi_mode(drv, setting->spi_mode_set);

    // set spi transfre mode
    set_spi_trans_mode(drv, setting->spi_trans_mode);

    // set spi date size
    set_spi_date_size(drv, setting->spi_date_size);
    
    // set spi first bit
    set_spi_first_bit(drv, setting->spi_frist_bit);

    // if enable spi irq
    set_spi_irq_enable(drv, setting->is_use_irq);

    // others
    set_spi_others(drv);

    // init
    HAL_SPI_Init(&drv->hal_spi);

    // start
    set_spi_start(drv);
}

void hal_set_bit_order(dev_spi_t *drv, spi_setting_t *setting) {
    set_spi_date_size(drv, setting->spi_date_size);
    HAL_SPI_Init(&drv->hal_spi);
}


void hal_spi_register(dev_spi_t *drv) {

    drv->dev_spi_init_cb();

    if(drv->is_use_dma == true) {
        // spi dma init
    }
}

void hal_spi_change_speed(dev_spi_t *drv, uint32_t speed) { 
    set_spi_speed(drv, speed);
    HAL_SPI_Init(&drv->hal_spi);
}









