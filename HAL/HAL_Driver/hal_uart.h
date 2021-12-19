#ifndef __hal_uart_h
#define __hal_uart_h

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

extern UART_HandleTypeDef laser_uart;
extern uint8_t laser_get_buf[1];

//#define RX_BUFFER_SIZE	1024
//#define TX_BUFFER_SIZE 	255

#define  __HAL_UART_CLK(uart)	__HAL_RCC_##uart##_CLK_ENABLE()
#define  UART_IRQn(uart)        uart##_IRQn

#define LaserUART		USART2
#define LaserUART_IRQn  UART_IRQn(USART2)


void hal_uart_gpio_init(void);
void hal_uart_init(void);
void hal_uart_irq_set(void);
void hal_laser_uart_irq_enable(void);
void hal_laser_uart_irq_disable(void);
void hal_uart_sendbyte(uint8_t data);
bool hal_is_uart_sr_txe(void);
uint32_t hal_read_usrt_status_reg(void);
uint32_t hal_read_uart_dr_reg(void);
void hal_clean_isr(void) ;
#endif
