#include "hal_uart.h"


UART_HandleTypeDef laser_uart;

DMA_HandleTypeDef dma_tx;
DMA_HandleTypeDef dma_rx;

static void hal_uart1_dma_init() {

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


void uart_send_dma(uint8_t *str,  uint16_t size) {

	HAL_UART_Transmit_DMA (&laser_uart ,str ,size);
}


void hal_uart_gpio_init(void) {

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_UART_CLK(USART1);
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
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

	hal_uart1_dma_init();

	HAL_NVIC_SetPriority(LaserUART_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LaserUART_IRQn);
	__HAL_UART_ENABLE_IT(&laser_uart, UART_IT_RXNE);
}

void hal_uart_irq_set(void) {
	HAL_NVIC_SetPriority(LaserUART_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LaserUART_IRQn);
}

void hal_laser_uart_irq_enable(void) { __HAL_UART_ENABLE_IT(&laser_uart, UART_IT_RXNE); }

void hal_laser_uart_irq_disable(void) { __HAL_UART_DISABLE_IT(&laser_uart, UART_IT_RXNE); }

void hal_uart_sendbyte(uint8_t data) { HAL_UART_Transmit(&laser_uart, &data, 1, 1000); }

bool hal_is_uart_sr_txe(void) { return (laser_uart.Instance->SR & USART_FLAG_TXE); }

uint32_t hal_read_usrt_status_reg(void) { return laser_uart.Instance->SR; }

uint32_t hal_read_uart_dr_reg(void) { return laser_uart.Instance->DR & 0x1FF; }

void hal_clean_isr(void) { laser_uart.Instance->SR &= ~USART_FLAG_RXNE; }

// use printf , but no suggest!!
int fputc(int ch,FILE *f)
{
    uint32_t temp = ch;
    HAL_UART_Transmit(&laser_uart, (uint8_t *)&temp, 1, 1000);        //huart3是串口的句柄
    return ch;
}




