/*
 mid_uart.h

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#ifndef __mid_uart_h
#define __mid_uart_h

#include "../../main.h"

#define UART_RB_BUFF_MAX                255

typedef struct 
{
    void (*uartInit)(void);
    void (*uartSendByte)(uint8_t );
    bool (*uartTransComplateFlag)(void);
}mid_uart_t;

typedef struct {
    uint32_t head;
    uint32_t tail;
    uint8_t buffer[UART_RB_BUFF_MAX];
}ringbuff_t;
extern ringbuff_t rb_serial_rx;
extern ringbuff_t rb_serial_tx;




void DevUartInit(void);

// ringbuffer
void serial_rb_init(ringbuff_t *rb);
void serial_rb_write(ringbuff_t *rb, uint8_t data);
uint8_t serial_rb_read(ringbuff_t *rb, uint8_t *data);
uint16_t serial_rb_abailable(ringbuff_t *rb);
uint16_t serial_rb_buff_count(ringbuff_t *rb);
void serial_rb_reset(ringbuff_t *rb);

#endif
