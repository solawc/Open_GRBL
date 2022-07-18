#ifndef __hal_uart_h
#define __hal_uart_h

#include "../../../main.h"

#define USR_MY_RINGBUFFER

#define UART_RB_BUFF_MAX                255
#define UART_RB_BUFF_MIN                0

#define LaserUART		                BOARD_UART
#define LaserUART_IRQn                  BOARD_UART_IRQ
#define LASER_UART_CLK_ENABLE()         BOARD_UART_CLK_ENABLE()   
#define LASER_UART_TX_CLK_ENABLE()      BOARD_UART_TX_CLK_ENABLE()
#define LASER_UART_RX_CLK_ENABLE()      BOARD_UART_RX_CLK_ENABLE()
#define LASER_UART_TX_PORT              BOARD_UART_TX_PORT
#define LASER_UART_TX_PIN               BOARD_UART_TX_PIN 
#define LASER_UART_RX_PORT              BOARD_UART_RX_PORT
#define LASER_UART_RX_PIN               BOARD_UART_RX_PIN 
#define LASER_UART_AF_MODE              BOARD_UART_AF_MODE
#define LASER_UART_IRQHANDLER           BOARD_UART_IRQnHANDLER
#define LASER_UART_RX_FLAG              BOARD_UART_RX_FLAG

typedef struct {
    uint8_t head;
    uint8_t tail;
    uint8_t buffer[UART_RB_BUFF_MAX];
}hal_uart_t;
extern hal_uart_t rb_serial_rx;


#define UART_DMA_MAX_BUFF               12192        // dma接收buff使用1K数据,127条数据缓存
typedef struct {

    bool uart_dma_busy;

    uint8_t dma_i_buff[UART_DMA_MAX_BUFF];
    
    uint32_t dma_count;

    uint32_t buff_len;
    
    DMA_HandleTypeDef hdma_rx;

}hal_uart_dma_t;

void hal_uart_gpio_init(void);
void hal_uart_init(void);
void hal_uart_irq_set(void);
void hal_laser_uart_irq_enable(void);
void hal_laser_uart_irq_disable(void);
void hal_uart_sendbyte(uint8_t data);
bool hal_is_uart_sr_txe(void);

// ringbuffer
void serial_rb_init(hal_uart_t *rb);
void serial_rb_write(hal_uart_t *rb, uint8_t data);
uint8_t serial_rb_read(hal_uart_t *rb, uint8_t *data);
uint16_t serial_rb_abailable(hal_uart_t *rb);
uint16_t serial_rb_buff_count(hal_uart_t *rb);
void serial_rb_reset(hal_uart_t *rb);

#endif
