#ifndef __tft_lcd_dev_h
#define __tft_lcd_dev_h

#include "../../main.h"


#ifdef LCD_TFT_SUPPORT

#define LCD_MOSI_PORT       GPIOB
#define LCD_MOSI_PIN        GPIO_PIN_5
#define LCD_MISO_PORT       GPIOB
#define LCD_MISO_PIN        GPIO_PIN_4
#define LCD_SCK_PORT        GPIOB
#define LCD_SCK_PIN         GPIO_PIN_3
#define LCD_CS_PORT         GPIOD
#define LCD_CS_PIN          GPIO_PIN_3
#define LCD_EN_PORT         GPIOD
#define LCD_EN_PIN          GPIO_PIN_2
#define LCD_RS_PORT         GPIOD
#define LCD_RS_PIN          GPIO_PIN_1
#define LCD_DC_PORT         GPIOA
#define LCD_DC_PIN          GPIO_PIN_15
#define LCD_TP_CS_PORT      GPIOD
#define LCD_TP_CS_PIN       GPIO_PIN_0
#define LCD_PIN_AF          GPIO_AF5_SPI3

#define CMD_MODE_SET()      HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET)
#define DATA_MODE_SET()     HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET)

typedef enum {
    LCD_TFT_24,     // mks ts24 2.4 inc LCD, Use spi dma to driver
    LCD_TFT_35,     // mks ts35 3.5 inc LCD, Use spi dma to driver 
    LCD_FIRE_5,     // fire 5.0 inc LCD, Use dma2d to driver
}dev_lcd_id_t;

typedef struct {

    uint32_t lcd_id;

    void (*tft_lcd_delay_ms)(uint32_t );

    void (*tft_lcd_init)(void);
    void (*tft_lcd_config)(void);
    void (*tft_lcd_touch_init)(void);
    void (*tft_lcd_enable)(void);
    void (*tft_lcd_disable)(void);
    void (*tft_touch_enable)(void);
    void (*tft_touch_disable)(void);

    void (*tft_lcd_display_on)(void);
    void (*tft_lcd_display_off)(void);

    void (*tft_lcd_write_cmd)(uint8_t);
    void (*tft_lcd_write_data)(uint8_t);

    void (*tft_lcd_write_buff)(uint8_t *);
    void (*tft_lcd_write_buff_dma)(uint8_t *);

    void (*tft_lcd_draw_point)(uint16_t ,uint16_t ,uint16_t);
    void (*tft_lcd_draw_fill)(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
    void (*tft_lcd_clear)(uint16_t);

}dev_lcd_t;

void dev_lcd_init(void);
void dev_lcd_draw_fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2, uint32_t color);

#endif

#endif /* __tft_lcd_dev_h */
