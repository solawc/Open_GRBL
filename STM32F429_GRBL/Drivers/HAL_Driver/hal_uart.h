#ifndef __hal_uart_h
#define __hal_uart_h

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef UART_HandleTypeDef  uart_def;

#define USE_UART_DMA_MODE

#define RX_BUFFER_SIZE	255
#define TX_BUFFER_SIZE 	255

#define  __HAL_UART_CLK(uart)	__HAL_RCC_##uart##_CLK_ENABLE()
#define  UART_IRQn(uart)        uart##_IRQn


#define LaserUART		USART1
#define LaserUART_IRQn  UART_IRQn(USART1)

typedef enum {

    UART_MODE_TX_ONLY,
    UART_MODE_RX_ONLY,
    UART_MODE_TX_RX,
}uart_mode_t;

typedef struct {

    uart_def        debug_uart;
    uart_mode_t     uart_mode;

    uint32_t        baud;      // default is 115200
    uint32_t        stop_bit;  // default is 1
    uint32_t        parity;    // default is none
    bool            uart_is_busy;
}hal_uart_t;


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
