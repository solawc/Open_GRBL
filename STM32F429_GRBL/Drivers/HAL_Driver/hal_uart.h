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

#define UART_TX_DMA_BUFF_SIZE       1024
#define UART_RX_DMA_BUFF_SIZE       1024

#define  __HAL_UART_CLK(uart)   __HAL_RCC_##uart##_CLK_ENABLE()

#define  UART_IRQn(uart)        uart##_IRQn

#define LASER_UART_PORT         1
#define _UART(X)    USART##X
#define UART(X)     _UART(X)

#define LaserUART	    UART(LASER_UART_PORT)	// USART1
#define LaserUART_IRQn  UART_IRQn(USART1)

typedef enum {
    UART_MODE_TX_ONLY,
    UART_MODE_RX_ONLY,
    UART_MODE_BOTH,         // default both
}uart_mode_t;

typedef struct {
    uart_def        debug_uart;
    uart_mode_t     uart_mode;
    uint32_t        baud;               // default is 115200
    uint32_t        stop_bit;           // default is 1
    uint32_t        parity;             // default is none

    void (* dev_uart_init)(uint32_t baud);
    void (* dev_uart_trans_byte_cb)(uint8_t data);
    void (* dev_uart_irq_set_cb)(void);

}dev_uart_t;


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

void uart_send_dma(uint8_t *str, uint16_t size);

#endif
