#include "tft_lcd_dev.h"

dev_lcd_t tft;
dev_spi_t tft_spi;
spi_setting_t tft_spi_set;

static void hal_tft_spi_init(void) {

    GPIO_InitTypeDef GPIO_Init = {0};

    GPIO_Init.Alternate = LCD_PIN_AF;
    GPIO_Init.Mode = GPIO_MODE_AF_PP;
    GPIO_Init.Pull = GPIO_NOPULL;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;

    GPIO_Init.Pin = LCD_SCK_PIN;
    HAL_GPIO_Init(LCD_SCK_PORT, &GPIO_Init);

    GPIO_Init.Pin = LCD_MISO_PIN;
    HAL_GPIO_Init(LCD_MISO_PORT, &GPIO_Init);

    GPIO_Init.Pin = LCD_MOSI_PORT;
    HAL_GPIO_Init(LCD_MOSI_PIN, &GPIO_Init);


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

    GPIO_Init.Pin = LCD_RS_PIN;
    HAL_GPIO_Init(LCD_RS_PORT, &GPIO_Init);

    tft_spi_set.is_use_irq = false;
    tft_spi_set.spi_num = SPI_3;
    tft_spi_set.spi_speed = 8;
    tft_spi_set.spi_mode_set = spi_mode_3;
    tft_spi_set.spi_date_size = size_8bit_date;
    tft_spi_set.spi_trans_mode = master_full_trans;
    tft_spi_set.spi_frist_bit = trans_msb_mode;
    hal_spi_begin(&tft_spi, &tft_spi_set);
}

static void hal_tft_trans_enable(void) {

    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
}

static void hal_tft_trans_disable() {

    HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

static uint8_t hal_tft_write_8(uint8_t data) {

    return hal_spi_transfer_revice_byte(&tft_spi, data);
}

static void hal_tft_write_cmd_8(uint8_t data) {
    CMD_MODE_SET();
    hal_tft_write_8(data);
}

static void hal_tft_write_data_8(uint8_t data) {
    DATA_MODE_SET();
    hal_tft_write_8(data);
}

static void hal_tft_display_on(void) {
    hal_tft_write_cmd_8(0x29);
}

static void hal_tft_display_off(void) {
    hal_tft_write_cmd_8(0x28);
}


void dev_lcd_init(void) {
    tft.tft_lcd_init = hal_tft_spi_init;
    tft.tft_lcd_enable = hal_tft_trans_enable;
    tft.tft_lcd_disable = hal_tft_trans_disable;
    tft.tft_lcd_write_cmd = hal_tft_write_cmd_8;
    tft.tft_lcd_write_data = hal_tft_write_data_8;
    tft.tft_lcd_display_on = hal_tft_display_on;
    tft.tft_lcd_display_off = hal_tft_display_off;

    tft.tft_lcd_init();
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

void dev_lcd_draw_fill() {





}






