#ifndef __mid_gpio_h
#define __mid_gpio_h

#include "../../../main.h"

typedef struct {

    /******************Limit*******************/
    void (*limit_gpio_init) (void);
    void (*limit_irq_enable)(void);
    void (*limit_irq_disable)(void);
    uint8_t (*limit_get_state)(uint8_t );
    uint8_t (*limit_get_mask)(uint8_t );

    /******************Motor*******************/
    void (*motor_gpio_init)(void);
    void (*motor_set_dir)(uint8_t);
    void (*motor_set_en)(bool);
    void (*motor_set_step)(uint8_t);
    uint8_t (*motor_get_dir_mask)(uint8_t);     // 用于GPIO按位偏移
    uint8_t (*motor_get_step_mask)(uint8_t);

    /******************Probe*******************/
    void (*probe_gpio_init)(void);
    uint8_t (*probe_gpio_read)(void);

    /******************Coolant*****************/
    void (*coolant_gpio_init)(void);
    void (*coolant_set_flood)(bool);
    void (*coolant_set_mist)(bool);
    uint8_t (*coolant_get_flood)(void);
    uint8_t (*coolant_get_mist)(void);

}mid_gpio_t;
extern mid_gpio_t dev_gpio;



void DevGpioInit(void);

#endif
