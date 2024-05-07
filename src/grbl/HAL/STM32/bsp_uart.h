/*
 bsp_uart.h

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __bsp_uart_h
#define __bsp_uart_h

#include "../../../main.h"

#define LaserUART		                BOARD_UART
#define LaserUART_IRQn                  BOARD_UART_IRQ
#define LASER_UART_CLK_ENABLE()         BOARD_UART_CLK_ENABLE()   
#define LASER_UART_TX_PORT              BOARD_UART_TX_PORT
#define LASER_UART_TX_PIN               BOARD_UART_TX_PIN 
#define LASER_UART_RX_PORT              BOARD_UART_RX_PORT
#define LASER_UART_RX_PIN               BOARD_UART_RX_PIN 
#define LASER_UART_AF_MODE              BOARD_UART_AF_MODE
#define LASER_UART_IRQHANDLER           BOARD_UART_IRQnHANDLER
#define LASER_UART_RX_FLAG              BOARD_UART_RX_FLAG

typedef struct {
    UART_HandleTypeDef obj;     /* any cpu lib obj */
    uint8_t         _uart_num;
    GPIO_TypeDef    *_tx_pin_port;
    GPIO_TypeDef    *_rx_pin_port;
    uint16_t        _tx_pin;
    uint16_t        _rx_pin;
    uint32_t        _af;
    uint32_t        _baud;
}hal_uart_t;

void uart_init(void);
void uart_enable_rx_irq(void);
void uart_send_byte(uint8_t data);

#endif
