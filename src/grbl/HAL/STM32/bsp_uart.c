/*
 bsp_uart.c

 Copyright (c) 2021-2023 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "bsp_uart.h"

ringbuff_t rb_serial_rx;
ringbuff_t rb_serial_tx;

UART_HandleTypeDef laser_uart;

/************************************************************
 * 			For Serial UART
 * *********************************************************/

/* 串口接收中断标志位 */
uint32_t _uart_irq_rx_flag(void) {

	return laser_uart.Instance->SR & (USART_SR_RXNE | USART_SR_ORE);
}

/* 串口发送中断标志位 */
uint32_t _uart_irq_tx_flag(void) {

	return laser_uart.Instance->SR & USART_SR_TXE && laser_uart.Instance->CR1 & USART_CR1_TXEIE;
}

/* 使能UART中断 */
void uart_enable_irq(void) {

	HAL_NVIC_SetPriority(LaserUART_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(LaserUART_IRQn);
}

/* 使能UART 接收中断 */
void uart_enable_rx_irq(void) {

	__HAL_UART_ENABLE_IT(&laser_uart, UART_IT_RXNE);
}

/* 使能UART 发送中断 */
void uart_enable_tx_irq(void) {

	__HAL_UART_ENABLE_IT(&laser_uart, UART_IT_TXE);
}

/* 禁用UART 接收中断 */
void uart_disable_tx_irq(void) {

	__HAL_UART_DISABLE_IT(&laser_uart, UART_IT_TXE);
}


/* 初始化串口/串口GPIO */
void uart_init(void) {

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	LASER_UART_CLK_ENABLE();

	GPIO_InitStruct.Pin = LASER_UART_TX_PIN|LASER_UART_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = LASER_UART_AF_MODE; 
    HAL_GPIO_Init(LASER_UART_TX_PORT, &GPIO_InitStruct);
    
	laser_uart.Instance = LaserUART;
	laser_uart.Init.BaudRate = BAUD_RATE;
	laser_uart.Init.WordLength = UART_WORDLENGTH_8B;
	laser_uart.Init.StopBits = UART_STOPBITS_1;
	laser_uart.Init.Parity = UART_PARITY_NONE;
	laser_uart.Init.Mode = UART_MODE_TX_RX;
	laser_uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	laser_uart.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&laser_uart) != HAL_OK)
  	{
    	Error_Handler();
  	}
	
#ifdef STM32G0B0xx
	if (HAL_UARTEx_SetTxFifoThreshold(&laser_uart, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&laser_uart, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_UARTEx_DisableFifoMode(&laser_uart) != HAL_OK)
	{
		Error_Handler();
	}
#endif
	uart_enable_irq();
	uart_enable_rx_irq();
}

/* STM32 UART 数据寄存器分两种命名，DR / RDR */
#ifdef RDR
#define USAR_READ_REG			RDR
#else 
#define USAR_READ_REG			DR
#endif

/* UART 发送一个字节 */
// void uart_send_byte(uint8_t data) { HAL_UART_Transmit(&laser_uart, &data, 1, 1000); }
void uart_send_byte(uint8_t data) { laser_uart.Instance->DR = data; }

uint8_t uart_rx_data(void) { 

	return laser_uart.Instance->USAR_READ_REG;
}

void uart_tx_data(uint8_t data) {

	laser_uart.Instance->USAR_READ_REG = data;
}

/*
 * C标准库的重定向, 该方法适用于使用Keil/IAR等这类型的编译器，如果使用GCC/G++等编译链工具进行编译，
 * 请使用_write(int fd, char *ptr, int len)	
 * 进行重定向，否则会出现串口无法打印的情况
*/
#ifdef __CC_ARM
int fputc(int ch,FILE *f)
{
    uint32_t temp = ch;
    HAL_UART_Transmit(&laser_uart, (uint8_t *)&temp, 1, 1000);        //huart3是串口的句柄
    return ch;
}
#else 
int _write(int fd, char *ptr, int len)
{	
	HAL_UART_Transmit(&laser_uart, (uint8_t *)ptr, len, 1000);        //huart3是串口的句柄
	return len;
}
#endif

// Serial UART ISR Handler
void LASER_UART_IRQHANDLER() {

#if defined(USE_FREERTOS_RTOS)
	uint32_t ulReturn;
#endif

#if defined(USE_FREERTOS_RTOS)
	ulReturn = taskENTER_CRITICAL_FROM_ISR();
#endif

	if(_uart_irq_rx_flag()) {  // LASER_UART_RX_FLAG
		laser_uart_rx_handler(uart_rx_data());		// 讲道理这里不应该在这处理，需要做一下变更才行
	}

	if(_uart_irq_tx_flag()) {
		__IO uint8_t data = 0; // 从缓冲区中获取数据
		__IO int ret = -1;
		if(ret) {
			uart_disable_tx_irq();
		}else {
			uart_tx_data(data);
		}
	}

	// HAL_UART_IRQHandler(&laser_uart);

#if defined(USE_FREERTOS_RTOS)
	taskEXIT_CRITICAL_FROM_ISR( ulReturn );
#endif
}





