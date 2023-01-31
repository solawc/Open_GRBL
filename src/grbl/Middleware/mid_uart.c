/*
 mid_uart.c

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "mid_uart.h"

mid_uart_t dev_uart;

void DevUartInit(void) {

    dev_uart.uartInit = BspUartInit;
    dev_uart.uartSendByte = BspUartSendByte;
    dev_uart.uartTransComplateFlag = BspUartTcFlag;
}

/*************************************************************
 * A ringbuffer init
 * **********************************************************/
void serial_rb_init(ringbuff_t *rb) {
	rb->head = 0;
	rb->tail = 0;
}

/*************************************************************
 * write a data to ringbuffer
 * **********************************************************/
void serial_rb_write(ringbuff_t *rb, uint8_t data) {

	uint8_t next = rb->head + 1;

	if(next == UART_RB_BUFF_MAX) { next = 0; }

	if(next != rb->tail) {
		rb->buffer[rb->head] = data;
		rb->head = next;
	}
}

/*************************************************************
 * read a data from ringbuffer
 * **********************************************************/
uint8_t serial_rb_read(ringbuff_t *rb, uint8_t *data) {

	uint8_t tail = rb->tail;

	if(rb->head == tail) {
		return 0;
	}else {
		*data = rb->buffer[tail];
		tail++;
		if(tail == UART_RB_BUFF_MAX) {tail = 0;}
		rb->tail = tail;
		return 1;
	}
}

/*************************************************************
 * if ringbuffer abailable
 * **********************************************************/
uint16_t serial_rb_abailable(ringbuff_t *rb) {
	uint8_t tmp_tail = rb->tail;						
	if(rb->head > tmp_tail) return (rb->head - tmp_tail);
	return (tmp_tail - rb->head); 
}

/*************************************************************
 * get ringbuffer count
 * **********************************************************/
uint16_t serial_rb_buff_count(ringbuff_t *rb) {
	uint8_t tmp_tail = rb->tail;
	if(rb->head >= tmp_tail) {return (rb->head - tmp_tail);}
	return (UART_RB_BUFF_MAX - (tmp_tail - rb->head));
} 

/************************************************************
 * Reset ringbuffer
 * *********************************************************/
void serial_rb_reset(ringbuff_t *rb) {
	rb->tail = rb->head;
}
