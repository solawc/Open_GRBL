#ifndef __hal_uart_h
#define __hal_uart_h

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define UART_RB_BUFF_MAX                255
#define UART_RB_BUFF_MIN                0

#define  __HAL_UART_CLK(uart)	        __HAL_RCC_##uart##_CLK_ENABLE()
#define  UART_IRQn(uart)                uart##_IRQn

#ifdef STM32F429xx
#define LaserUART		                USART1
#define LaserUART_IRQn                  UART_IRQn(USART1)
#define LASER_UART_CLK_ENABLE()          __HAL_UART_CLK(USART1)
#define LASER_UART_TX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE();
#define LASER_UART_RX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE();
#define LASER_UART_TX_PORT              GPIOA
#define LASER_UART_TX_PIN               GPIO_PIN_9
#define LASER_UART_RX_PORT              GPIOA
#define LASER_UART_RX_PIN               GPIO_PIN_10
#define LASER_UART_AF_MODE              GPIO_AF7_USART1
#define LASER_UART_IRQHANDLER           USART1_IRQHandler
#define LASER_UART_RX_FLAG              __HAL_UART_GET_FLAG(&laser_uart, UART_FLAG_RXNE) == SET
#elif defined(STM32G0B0xx) 
#define LaserUART		                USART2
#define LaserUART_IRQn                  UART_IRQn(USART2)
#define LASER_UART_CLK_ENABLE()         __HAL_UART_CLK(USART2)
#define LASER_UART_TX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE();
#define LASER_UART_RX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE();
#define LASER_UART_TX_PORT              GPIOA
#define LASER_UART_TX_PIN               GPIO_PIN_2
#define LASER_UART_RX_PORT              GPIOA
#define LASER_UART_RX_PIN               GPIO_PIN_3
#define LASER_UART_AF_MODE              GPIO_AF1_USART2
#define LASER_UART_IRQHANDLER           USART2_IRQHandler
#define LASER_UART_RX_FLAG              __HAL_UART_GET_FLAG(&laser_uart, UART_FLAG_RXNE) == SET
#endif


void hal_uart_gpio_init(void);
void hal_uart_init(void);
void hal_uart_irq_set(void);
void hal_laser_uart_irq_enable(void);
void hal_laser_uart_irq_disable(void);
void hal_uart_sendbyte(uint8_t data);
bool hal_is_uart_sr_txe(void);

void uart_send_dma(uint8_t *str, uint16_t size);


#endif
