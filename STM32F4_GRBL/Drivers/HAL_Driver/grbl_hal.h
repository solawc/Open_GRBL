#ifndef __grbl_hal_h
#define __grbl_hal_h


#include "main.h"
#include "stdbool.h"


// hal header
#include "hal_gpio.h"
#include "hal_uart.h"
#include "hal_i2c.h"
#include "hal_flash_eeprom.h"
#include "hal_spi.h"
#include "hal_tim.h"
//
#include "led_task.h"
#include "hal_w25qxx.h"

#if USE_ESP32_MCU
#define ISR_CODE ARR_IRM
#else
#define ISR_CODE
#endif 


// limit contrl struct
typedef struct {
    bool is_enable_soft_limit;
    bool is_enable_hard_limit;
    void (* limit_interrupt_handle)(void);
}mc_limit_t;


// spindle contrl struct
typedef struct {

    bool        use_cnc_or_laser;           // set 0 is cnc, set 1 is laser
    uint32_t    pwm_freq;                   // laser or cnc pwm freq, default 1KHz (0-20KHz)
    uint32_t    pwm_set;                    // set laser or cnc pwm value (0-255) 
    void        (* spindle_cnc_pwm_set)(uint32_t pwm);
    void        (* spindle_laser_pwm_set)(uint32_t pwm);

}mc_spindle_t;


typedef enum {
    W25QXX,
    SDCard,
    NorFlash,
    Eeprom,
    // ...
}flash_mode_t;

typedef struct {
    flash_mode_t flash_mode;
    void (* flash_init_cb)(void);                       
    void (* flash_write_byte_cb)(uint8_t data);
    void (* flash_write_buff_cb)(uint8_t *data);
    void (* flash_read_buff_cb)(uint8_t *data);
    void (* flash_eraser_s_cb)(uint8_t *data);
}hal_flash_t;




typedef struct {

    mc_limit_t hal_limit;
    



}mcu_hal_t;





#endif

