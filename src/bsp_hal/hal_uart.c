#include "hal_uart.h"


UART_HandleTypeDef laser_uart;

DMA_HandleTypeDef dma_tx;
DMA_HandleTypeDef dma_rx;

uint8_t laser_rx_buf[1];

// #define USE_SERIAL_DMA

#if defined(USE_SERIAL_DMA)
static void hal_uart1_dma_init() {

#ifdef STM32F429xx
	__HAL_RCC_DMA2_CLK_ENABLE();

	dma_tx.Instance = DMA2_Stream7;
	dma_tx.Init.Channel = DMA_CHANNEL_4;
	dma_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	dma_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	dma_tx.Init.MemInc = DMA_MINC_ENABLE;
	dma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;  // 8bit
	dma_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	dma_tx.Init.Mode = DMA_NORMAL;
	dma_tx.Init.Priority = DMA_PRIORITY_MEDIUM;
	dma_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	dma_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	dma_tx.Init.MemBurst = DMA_MBURST_SINGLE;
	dma_tx.Init.PeriphBurst = DMA_PBURST_SINGLE;
	HAL_DMA_DeInit(&dma_tx);
	HAL_DMA_Init(&dma_tx);
	__HAL_LINKDMA(&laser_uart, hdmatx, dma_tx);
}
#elif defined(STM32G0B0xx)

	__HAL_RCC_DMA1_CLK_ENABLE();

	dma_tx.Instance = DMA1_Channel2;
    dma_tx.Init.Request = DMA_REQUEST_USART2_TX;
    dma_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    dma_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    dma_tx.Init.MemInc = DMA_MINC_ENABLE;
    dma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    dma_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    dma_tx.Init.Mode = DMA_NORMAL;
    dma_tx.Init.Priority = DMA_PRIORITY_LOW;

    if (HAL_DMA_Init(&dma_tx) != HAL_OK)
    {
      Error_Handler();
    }

	__HAL_LINKDMA(&laser_uart, hdmatx, dma_tx);

	HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
  	HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
}
#endif
#endif

void uart_send_dma(uint8_t *str,  uint16_t size) {	
	HAL_UART_Transmit_DMA (&laser_uart ,str ,size);
}

void hal_uart_gpio_init(void) {

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	LASER_UART_CLK_ENABLE();
	LASER_UART_TX_CLK_ENABLE();
	LASER_UART_RX_CLK_ENABLE();

	GPIO_InitStruct.Pin = LASER_UART_TX_PIN|LASER_UART_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = LASER_UART_AF_MODE;
    HAL_GPIO_Init(LASER_UART_TX_PORT, &GPIO_InitStruct);
}

void hal_uart_init(void) {

	hal_uart_gpio_init();
    laser_uart.Instance = LaserUART;
	laser_uart.Init.BaudRate = 115200;
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

#ifdef USE_SERIAL_DMA
	hal_uart1_dma_init();
#else 

#endif
	hal_uart_irq_set();

	// HAL_UART_Receive_IT(&laser_uart, laser_rx_buf, 1);
}

void hal_uart_irq_set(void) {
	HAL_NVIC_SetPriority(LaserUART_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LaserUART_IRQn);
	__HAL_UART_ENABLE_IT(&laser_uart, UART_IT_RXNE);
}

void hal_laser_uart_irq_enable(void) { __HAL_UART_ENABLE_IT(&laser_uart, UART_IT_RXNE); }

void hal_laser_uart_irq_disable(void) { __HAL_UART_DISABLE_IT(&laser_uart, UART_IT_RXNE); }

void hal_uart_sendbyte(uint8_t data) { HAL_UART_Transmit(&laser_uart, &data, 1, 1000); }

bool hal_is_uart_sr_txe(void) { 
#ifdef STM32F429xx
	return (__HAL_UART_GET_FLAG(&laser_uart, USART_FLAG_TXE));
#elif defined(STM32G0B0xx)
	return (__HAL_UART_GET_FLAG(&laser_uart, USART_FLAG_TXE)); 
#endif
}

// use printf , but no suggest!!
/*
 * C标准库的重定向, 该方法适用于使用Keil/IAR等这类型的编译器，如果使用GCC/G++等编译链工具进行编译，请使用_write(int fd, char *ptr, int len)	
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
#ifdef USE_SERIAL_DMA
	uart_trans_lock = true;
	uart_send_dma((uint8_t*)ptr, len);
	while(!hal_is_uart_sr_txe());
#else 
	HAL_UART_Transmit(&laser_uart, (uint8_t *)ptr, len, 1000);        //huart3是串口的句柄
#endif
	return len;
}
#endif

#ifdef USE_SERIAL_DMA
void DMA1_Channel1_IRQHandler(void)
{
	printf("enter dma handler\n");
	HAL_DMA_IRQHandler(&dma_rx);
}

void DMA1_Channel2_3_IRQHandler(void)
{
  	HAL_DMA_IRQHandler(&dma_tx);
}
#endif

#ifdef USE_SERIAL_DMA
	bool uart_trans_lock = false;
#endif


// Serial UART ISR Handler
void LASER_UART_IRQHANDLER() {

#if defined(USE_FREERTOS_RTOS)
	uint32_t ulReturn;
#endif
	uint16_t data;

#if defined(USE_FREERTOS_RTOS)
	ulReturn = taskENTER_CRITICAL_FROM_ISR();
#endif

	// HAL_UART_IRQHandler(&laser_uart);
	
	if(__HAL_UART_GET_FLAG(&laser_uart, UART_FLAG_RXNE) == SET) {
		data = laser_uart.Instance->RDR;
		laser_uart_rx_handler(data);
	}

	HAL_UART_IRQHandler(&laser_uart);

#if defined(USE_FREERTOS_RTOS)
	taskEXIT_CRITICAL_FROM_ISR( ulReturn );
#endif
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{	
	// if(huart == &laser_uart) {
	// 	laser_uart_rx_handler(laser_rx_buf[0]);
	// 	HAL_UART_Receive_IT(&laser_uart, laser_rx_buf, 1);       // 重新注册一次，要不然下次收不到了
	// }
}





