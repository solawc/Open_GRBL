#ifndef __hal_i2c_h
#define __hal_i2c_h

#include "main.h"

#define EEPROM_I2C_PORT         I2C1
#define EEPROM_I2C_SCL_PORT     GPIOB
#define EEPROM_I2C_SCL_PIN      GPIO_PIN_8
#define EEPROM_I2C_SDA_PORT     GPIOB
#define EEPROM_I2C_SDA_PIN      GPIO_PIN_9

void hal_i2c_gpio_init(void);
void hal_i2c1_init(void);

#endif
