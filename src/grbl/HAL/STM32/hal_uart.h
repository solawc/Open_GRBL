#ifndef __hal_uart_h
#define __hal_uart_h

#include "../../../main.h"


#define UART_RB_BUFF_MAX                255
#define UART_RB_BUFF_MIN                0

// #ifndef UART_IRQn(uart) 
// #define  __HAL_UART_CLK(uart)	        __HAL_RCC_##uart##_CLK_ENABLE()
// #define  UART_IRQn(uart)                uart##_IRQn
// #endif

// #ifdef STM32F429xx
// #define LaserUART		                USART1
// #define LaserUART_IRQn                  UART_IRQn(USART1)
// #define LASER_UART_CLK_ENABLE()          __HAL_UART_CLK(USART1)
// #define LASER_UART_TX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE();
// #define LASER_UART_RX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE();
// #define LASER_UART_TX_PORT              GPIOA
// #define LASER_UART_TX_PIN               GPIO_PIN_9
// #define LASER_UART_RX_PORT              GPIOA
// #define LASER_UART_RX_PIN               GPIO_PIN_10
// #define LASER_UART_AF_MODE              GPIO_AF7_USART1
// #define LASER_UART_IRQHANDLER           USART1_IRQHandler
// #define LASER_UART_RX_FLAG              __HAL_UART_GET_FLAG(&laser_uart, UART_FLAG_RXNE) == SET
// #elif defined(STM32G0B0xx) 
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
// #elif defined(STM32F407xx) 
// #define LaserUART		                USART3
// #define LaserUART_IRQn                  UART_IRQn(USART3)
// #define LASER_UART_CLK_ENABLE()         __HAL_UART_CLK(USART3)
// #define LASER_UART_TX_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE();
// #define LASER_UART_RX_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE();
// #define LASER_UART_TX_PORT              GPIOB
// #define LASER_UART_TX_PIN               GPIO_PIN_10
// #define LASER_UART_RX_PORT              GPIOB
// #define LASER_UART_RX_PIN               GPIO_PIN_11
// #define LASER_UART_AF_MODE              GPIO_AF7_USART3
// #define LASER_UART_IRQHANDLER           USART3_IRQHandler
// #define LASER_UART_RX_FLAG              __HAL_UART_GET_FLAG(&laser_uart, UART_FLAG_RXNE) == SET
// #endif

typedef struct {
    uint8_t head;
    uint8_t tail;
    uint8_t buffer[255];
}hal_uart_t;
extern hal_uart_t rb_serial_rx;

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

#endif
