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

    hal_tft_write_cmd_8(0X11);   // Sleep out
    lcd_delay_ms(120);
    hal_tft_write_cmd_8(0X13);    // Normal display mode on

    hal_tft_write_cmd_8(0X36);
    hal_tft_write_data_8(0x08);

    // JLX240 display datasheet
    hal_tft_write_cmd_8(0xB6);
    hal_tft_write_data_8(0x0A);
    hal_tft_write_data_8(0x82);

    hal_tft_write_cmd_8(0xB0);
    hal_tft_write_data_8(0x00);
    hal_tft_write_data_8(0xE0); // 5 to 6 bit conversion: r0 = r5, b0 = b5

        
    hal_tft_write_cmd_8(0x3A);
    hal_tft_write_data_8(0x55);
    lcd_delay_ms(10);

    //--------------------------------ST7789V Frame rate setting----------------------------------//
    hal_tft_write_cmd_8(0xB2);
    hal_tft_write_data_8(0x0c);
    hal_tft_write_data_8(0x0c);
    hal_tft_write_data_8(0x00);
    hal_tft_write_data_8(0x33);
    hal_tft_write_data_8(0x33);

    hal_tft_write_cmd_8(0xB7);      // Voltages: VGH / VGL
    hal_tft_write_data_8(0x35);

    //---------------------------------ST7789V Power setting--------------------------------------//
    hal_tft_write_cmd_8(0xBB);
    hal_tft_write_data_8(0x28);		// JLX240 display datasheet

    hal_tft_write_cmd_8(0xC0);
    hal_tft_write_data_8(0x0C);

    hal_tft_write_cmd_8(0xC2);
    hal_tft_write_data_8(0x01);
    hal_tft_write_data_8(0xFF);

    hal_tft_write_cmd_8(0xC3);       // voltage VRHS
    hal_tft_write_data_8(0x10);

    hal_tft_write_cmd_8(0xC4);
    hal_tft_write_data_8(0x20);

    hal_tft_write_cmd_8(0xC6);
    hal_tft_write_data_8(0x0f);

    hal_tft_write_cmd_8(0xD0);
    hal_tft_write_data_8(0xa4);
    hal_tft_write_data_8(0xa1);

    //--------------------------------ST7789V gamma setting---------------------------------------//
    hal_tft_write_cmd_8(0xE0);
    hal_tft_write_data_8(0xd0);
    hal_tft_write_data_8(0x00);
    hal_tft_write_data_8(0x02);
    hal_tft_write_data_8(0x07);
    hal_tft_write_data_8(0x0a);
    hal_tft_write_data_8(0x28);
    hal_tft_write_data_8(0x32);
    hal_tft_write_data_8(0x44);
    hal_tft_write_data_8(0x42);
    hal_tft_write_data_8(0x06);
    hal_tft_write_data_8(0x0e);
    hal_tft_write_data_8(0x12);
    hal_tft_write_data_8(0x14);
    hal_tft_write_data_8(0x17);

    hal_tft_write_cmd_8(0xE1);
    hal_tft_write_data_8(0xd0);
    hal_tft_write_data_8(0x00);
    hal_tft_write_data_8(0x02);
    hal_tft_write_data_8(0x07);
    hal_tft_write_data_8(0x0a);
    hal_tft_write_data_8(0x28);
    hal_tft_write_data_8(0x31);
    hal_tft_write_data_8(0x54);
    hal_tft_write_data_8(0x47);
    hal_tft_write_data_8(0x0e);
    hal_tft_write_data_8(0x1c);
    hal_tft_write_data_8(0x17);
    hal_tft_write_data_8(0x1b);
    hal_tft_write_data_8(0x1e);

    hal_tft_write_cmd_8(0x21);

    hal_tft_write_cmd_8(0x2A);    // Column address set
    hal_tft_write_data_8(0x00);
    hal_tft_write_data_8(0x00);
    hal_tft_write_data_8(0x00);
    hal_tft_write_data_8(0x3F); // hal_tft_write_data_8(0xE5);    // 239

    hal_tft_write_cmd_8(0x2B);    // Row address set
    hal_tft_write_data_8(0x00);
    hal_tft_write_data_8(0x00);
    hal_tft_write_data_8(0x01);
    hal_tft_write_data_8(0xE5); // hal_tft_write_data_8(0x3F);    // 319

    lcd_delay_ms(120);
    hal_tft_write_cmd_8(0x29);    //Display on
    lcd_delay_ms(120);
}

void dev_lcd_init(void) {

    tft.tft_lcd_init = hal_tft_spi_init;
    tft.tft_lcd_enable = hal_tft_trans_enable;
    tft.tft_lcd_disable = hal_tft_trans_disable;
    tft.tft_lcd_write_cmd = hal_tft_write_cmd_8;
    tft.tft_lcd_write_data = hal_tft_write_data_8;
    tft.tft_lcd_display_on = hal_tft_display_on;
    tft.tft_lcd_display_off = hal_tft_display_off;

    printf("[debug]enter lcd init\n");
    // tft.tft_lcd_init();
    printf("[debug]enter lcd init finish\n");
    printf("[debug]enter lcd config\n");
    hal_tft_display_config();
    printf("[debug]enter lcd config finish\n");
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

    // tft.tft_lcd_enable();

    DATA_MODE_SET();
    hal_tft_trans_enable();
    hal_set_16_mode(1);
    for(x=0; x<y; x++)  { hal_tft_write_data_16(color); }
    hal_set_16_mode(0);
    hal_tft_trans_disable();
    tft.tft_lcd_disable(); 
}






