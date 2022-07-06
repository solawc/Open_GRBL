#include "tft_lcd_dev.h"

dev_lcd_t tft;
SPI_HandleTypeDef lcd_hspi;         // g0 use spi3

static void hal_tft_spi_init(void) {

    GPIO_InitTypeDef GPIO_Init = {0};

    __HAL_RCC_SPI3_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_Init.Alternate = LCD_PIN_AF;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;

    GPIO_Init.Pin = LCD_SCK_PIN;
    HAL_GPIO_Init(LCD_SCK_PORT, &GPIO_Init);

    GPIO_Init.Pin = LCD_MISO_PIN;
    HAL_GPIO_Init(LCD_MISO_PORT, &GPIO_Init);

    GPIO_Init.Pin = LCD_MOSI_PIN;
    HAL_GPIO_Init(LCD_MOSI_PORT, &GPIO_Init);

    GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pull = GPIO_PULLUP;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;

    GPIO_Init.Pin = LCD_CS_PIN;
    HAL_GPIO_Init(LCD_CS_PORT, &GPIO_Init);

    GPIO_Init.Pin = LCD_TP_CS_PIN;
    HAL_GPIO_Init(LCD_TP_CS_PORT, &GPIO_Init);

    GPIO_Init.Pin = LCD_EN_PIN;
    HAL_GPIO_Init(LCD_EN_PORT, &GPIO_Init);

    GPIO_Init.Pin = LCD_DC_PIN;
    HAL_GPIO_Init(LCD_DC_PORT, &GPIO_Init);

#ifdef LCD_RS_PIN
    GPIO_Init.Pin = LCD_RS_PIN;
    HAL_GPIO_Init(LCD_RS_PORT, &GPIO_Init);
#endif

    spi_for_tft_init();

}

static void lcd_delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}

static void hal_tft_trans_enable(void) {
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
}

static void hal_tft_trans_disable() {
    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

static uint8_t hal_tft_write_8(uint8_t data) {
    // return hal_spi_transfer_revice_byte(&tft_spi, data);
    return 0;
}

// static uint16_t hal_tft_write_16(uint16_t data) {
//     // return hal_spi_transfer_revice_byte(&tft_spi, data);
//     uint16_t rdata = 0;
//     HAL_SPI_TransmitReceive(&tft_spi.hal_spi, (uint8_t *)&data, &rdata, 1,100);
//     return rdata;
// }


static void hal_tft_write_cmd_8(uint8_t data) {
    CMD_MODE_SET();
    hal_tft_trans_enable();
    hal_tft_write_8(data);
    hal_tft_trans_disable();
}

static void hal_tft_write_data_8(uint8_t data) {
    DATA_MODE_SET();
    hal_tft_trans_enable();
    hal_tft_write_8(data);
    hal_tft_trans_disable();
}

static void hal_set_16_mode(uint8_t data_size) {

    if(data_size == 0) {}
    else {}
}

static void hal_tft_write_data_16(uint16_t data) {
    hal_tft_write_8(data >> 8);
    hal_tft_write_8(data);
}

static void hal_tft_display_on(void) {
    hal_tft_write_cmd_8(0x29);
}

static void hal_tft_display_off(void) {
    hal_tft_write_cmd_8(0x28);
}

static void hal_tft_display_config(void) {

    tft.tft_lcd_write_cmd(0X11);   // Sleep out
    tft.tft_lcd_delay_ms(120);
    tft.tft_lcd_write_cmd(0X13);    // Normal display mode on

    tft.tft_lcd_write_cmd(0X36);
    tft.tft_lcd_write_data(0x08);

    // JLX240 display datasheet
    tft.tft_lcd_write_cmd(0xB6);
    tft.tft_lcd_write_data(0x0A);
    tft.tft_lcd_write_data(0x82);

    tft.tft_lcd_write_cmd(0xB0);
    tft.tft_lcd_write_data(0x00);
    tft.tft_lcd_write_data(0xE0); // 5 to 6 bit conversion: r0 = r5, b0 = b5

        
    tft.tft_lcd_write_cmd(0x3A);
    tft.tft_lcd_write_data(0x55);
    tft.tft_lcd_delay_ms(10);

    //--------------------------------ST7789V Frame rate setting----------------------------------//
    tft.tft_lcd_write_cmd(0xB2);
    tft.tft_lcd_write_data(0x0c);
    tft.tft_lcd_write_data(0x0c);
    tft.tft_lcd_write_data(0x00);
    tft.tft_lcd_write_data(0x33);
    tft.tft_lcd_write_data(0x33);

    tft.tft_lcd_write_cmd(0xB7);      // Voltages: VGH / VGL
    tft.tft_lcd_write_data(0x35);

    //---------------------------------ST7789V Power setting--------------------------------------//
    tft.tft_lcd_write_cmd(0xBB);
    tft.tft_lcd_write_data(0x28);		// JLX240 display datasheet

    tft.tft_lcd_write_cmd(0xC0);
    tft.tft_lcd_write_data(0x0C);

    tft.tft_lcd_write_cmd(0xC2);
    tft.tft_lcd_write_data(0x01);
    tft.tft_lcd_write_data(0xFF);

    tft.tft_lcd_write_cmd(0xC3);       // voltage VRHS
    tft.tft_lcd_write_data(0x10);

    tft.tft_lcd_write_cmd(0xC4);
    tft.tft_lcd_write_data(0x20);

    tft.tft_lcd_write_cmd(0xC6);
    tft.tft_lcd_write_data(0x0f);

    tft.tft_lcd_write_cmd(0xD0);
    tft.tft_lcd_write_data(0xa4);
    tft.tft_lcd_write_data(0xa1);

    //--------------------------------ST7789V gamma setting---------------------------------------//
    tft.tft_lcd_write_cmd(0xE0);
    tft.tft_lcd_write_data(0xd0);
    tft.tft_lcd_write_data(0x00);
    tft.tft_lcd_write_data(0x02);
    tft.tft_lcd_write_data(0x07);
    tft.tft_lcd_write_data(0x0a);
    tft.tft_lcd_write_data(0x28);
    tft.tft_lcd_write_data(0x32);
    tft.tft_lcd_write_data(0x44);
    tft.tft_lcd_write_data(0x42);
    tft.tft_lcd_write_data(0x06);
    tft.tft_lcd_write_data(0x0e);
    tft.tft_lcd_write_data(0x12);
    tft.tft_lcd_write_data(0x14);
    tft.tft_lcd_write_data(0x17);

    tft.tft_lcd_write_cmd(0xE1);
    tft.tft_lcd_write_data(0xd0);
    tft.tft_lcd_write_data(0x00);
    tft.tft_lcd_write_data(0x02);
    tft.tft_lcd_write_data(0x07);
    tft.tft_lcd_write_data(0x0a);
    tft.tft_lcd_write_data(0x28);
    tft.tft_lcd_write_data(0x31);
    tft.tft_lcd_write_data(0x54);
    tft.tft_lcd_write_data(0x47);
    tft.tft_lcd_write_data(0x0e);
    tft.tft_lcd_write_data(0x1c);
    tft.tft_lcd_write_data(0x17);
    tft.tft_lcd_write_data(0x1b);
    tft.tft_lcd_write_data(0x1e);

    tft.tft_lcd_write_cmd(0x21);

    tft.tft_lcd_write_cmd(0x2A);    // Column address set
    tft.tft_lcd_write_data(0x00);
    tft.tft_lcd_write_data(0x00);
    tft.tft_lcd_write_data(0x00);
    tft.tft_lcd_write_data(0x3F); // tft.tft_lcd_write_data(0xE5);    // 239

    tft.tft_lcd_write_cmd(0x2B);    // Row address set
    tft.tft_lcd_write_data(0x00);
    tft.tft_lcd_write_data(0x00);
    tft.tft_lcd_write_data(0x01);
    tft.tft_lcd_write_data(0xE5); // tft.tft_lcd_write_data(0x3F);    // 319

    tft.tft_lcd_delay_ms(120);
    tft.tft_lcd_write_cmd(0x29);    //Display on
    tft.tft_lcd_delay_ms(120);
}

void dev_lcd_init(void) {

    tft.tft_lcd_init = hal_tft_spi_init;
    tft.tft_lcd_enable = hal_tft_trans_enable;
    tft.tft_lcd_disable = hal_tft_trans_disable;
    tft.tft_lcd_write_cmd = hal_tft_write_cmd_8;
    tft.tft_lcd_write_data = hal_tft_write_data_8;
    tft.tft_lcd_display_on = hal_tft_display_on;
    tft.tft_lcd_display_off = hal_tft_display_off;
    tft.tft_lcd_delay_ms = lcd_delay_ms;

    tft.tft_lcd_init();
    
    hal_tft_display_config();
    HAL_GPIO_WritePin(LCD_EN_PORT, LCD_EN_PIN, GPIO_PIN_SET);
    dev_lcd_draw_fill(0, 0, 240, 320, 0x1010);
}

void dev_lcd_set_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    tft.tft_lcd_write_cmd(0x2A);
    tft.tft_lcd_write_data(x1>>8);
    tft.tft_lcd_write_data(x1);
    tft.tft_lcd_write_data(x2>>8);
    tft.tft_lcd_write_data(x2);
    
    tft.tft_lcd_write_cmd(0x2B);
    tft.tft_lcd_write_data(y1>>8);
    tft.tft_lcd_write_data(y1);
    tft.tft_lcd_write_data(y2>>8);
    tft.tft_lcd_write_data(y2);

    tft.tft_lcd_write_cmd(0x2C);
    DATA_MODE_SET();
}

void dev_lcd_draw_fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2, uint32_t color) {

    uint32_t x,y;

    y = (x2-x1)*(y2-y1);

    dev_lcd_set_window(x1,y1,x2,y2);      //设置光标位置

    DATA_MODE_SET();
    tft.tft_lcd_disable();
    hal_set_16_mode(1);
    for(x=0; x<y; x++) { hal_tft_write_data_16(color); }
    hal_set_16_mode(0);
    tft.tft_lcd_disable(); 
}






