#ifndef __hal_uart_h
#define __hal_uart_h

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define RX_BUFFER_SIZE	255
#define TX_BUFFER_SIZE 	255

typedef enum {

	UART_9600,
	UART_115200,
	// ...待添加
}LASER_BAUD_T;


typedef struct {

	LASER_BAUD_T laser_baud; 
	
}LASET_UART_T; 

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
