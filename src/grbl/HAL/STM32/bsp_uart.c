/*
 bsp_uart.c

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "bsp_uart.h"

#define __USART(X)	USART##X
#define _USART(X)	__USART(X)
#define USART(X)	_USART(X)

ringbuff_t rb_serial_rx;
ringbuff_t rb_serial_tx;

UART_HandleTypeDef laser_uart;
UART_HandleTypeDef tft_uart;

/************************************************************
 * 			For Serial UART
 * *********************************************************/
void BspUartGpioInit(void) {

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	LASER_UART_CLK_ENABLE();

	GPIO_InitStruct.Pin = LASER_UART_TX_PIN|LASER_UART_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = LASER_UART_AF_MODE; 
    HAL_GPIO_Init(LASER_UART_TX_PORT, &GPIO_InitStruct);
}

void BspUartInit(void) {

	BspUartGpioInit();
    
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
	BspUartIrqSet();
}

void BspUartIrqSet(void) {
	HAL_NVIC_SetPriority(LaserUART_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LaserUART_IRQn);
	__HAL_UART_ENABLE_IT(&laser_uart, UART_IT_RXNE);
}

void BspUartSendByte(uint8_t data) { HAL_UART_Transmit(&laser_uart, &data, 1, 1000); }

/* For stm32 reg. */
#ifdef RDR
#define USAR_READ_REG			RDR
#else 
#define USAR_READ_REG			DR
#endif

uint8_t BspUartReadData(void) { 
	return laser_uart.Instance->USAR_READ_REG;
}

bool BspUartTcFlag(void) { 
	return (__HAL_UART_GET_FLAG(&laser_uart, UART_FLAG_TC));
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
	__IO uint16_t data;

#if defined(USE_FREERTOS_RTOS)
	ulReturn = taskENTER_CRITICAL_FROM_ISR();
#endif

	if(LASER_UART_RX_FLAG) {
		data = BspUartReadData();
		laser_uart_rx_handler(data);
	}

	HAL_UART_IRQHandler(&laser_uart);

#if defined(USE_FREERTOS_RTOS)
	taskEXIT_CRITICAL_FROM_ISR( ulReturn );
#endif
}

/************************************************************
 * 			For LCD TFT UART
 * *********************************************************/
static void tft_lcd_uart_pins_init() {


}

void tft_lcd_uart_init() {
	tft_lcd_uart_pins_init();
}



/********************------------------------------------********************/

void uartSetPin(hal_uart_t *uart, GPIO_TypeDef *tx_port, uint16_t tx_pin, GPIO_TypeDef *rx_port, uint16_t rx_pin, uint32_t af) {
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/*
	 * About GPIO clock, they will be init at system start, we will enabel all 
	 * GPIO clock.
 	*/

	uart->_tx_pin_port = tx_port;
	uart->_rx_pin_port = rx_port;
	uart->_tx_pin = tx_pin;
	uart->_rx_pin = rx_pin;
	uart->_af = af;

	// LASER_UART_CLK_ENABLE();

	/**********************BSP GPIO Init*********************
	* 这里可以修改程任意的板卡的GPIO的初始化部分，如果必须的话
	********************************************************/
	GPIO_InitStruct.Pin = uart->_tx_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = af; 
    HAL_GPIO_Init(uart->_tx_pin_port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = uart->_rx_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = af; 
    HAL_GPIO_Init(uart->_rx_pin_port, &GPIO_InitStruct);
}


void uartSetBaud(hal_uart_t *uart, uint32_t baud) {
	uart->_baud = baud;
}



void uartInit(hal_uart_t *uart, uint8_t uart_num) {
	uart->_uart_num = uart_num;


	// uart->obj.Instance = USART(uart->_uart_num);// LaserUART;
	uart->obj.Init.BaudRate = BAUD_RATE;
	uart->obj.Init.WordLength = UART_WORDLENGTH_8B;
	uart->obj.Init.StopBits = UART_STOPBITS_1;
	uart->obj.Init.Parity = UART_PARITY_NONE;
	uart->obj.Init.Mode = UART_MODE_TX_RX;
	uart->obj.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart->obj.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&uart->obj) != HAL_OK)
  	{
    	Error_Handler();
  	}
}



