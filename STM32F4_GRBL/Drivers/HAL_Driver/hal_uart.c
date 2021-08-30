#include "hal_uart.h"


UART_HandleTypeDef huart1;

void hal_uart_gpio_init(void) {

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_USART1_CLK_ENABLE();
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
    huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
  	{
    	Error_Handler();
  	}

	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
}

void hal_uart_irq_set(void) {

	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
}

void hal_laser_uart_irq_enable(void) {
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
}

void hal_laser_uart_irq_disable(void) {
	__HAL_UART_DISABLE_IT(&huart1, UART_IT_RXNE);
}

void hal_uart_sendbyte(uint8_t data) {
	HAL_UART_Transmit(&huart1, &data, 1, 1000);
}

bool hal_is_uart_sr_txe(void) {

	// return (USART1->ISR & USART_FLAG_TXE);
	return (USART1->SR & USART_FLAG_TXE);
}

uint32_t hal_read_usrt_status_reg(void) {

	// return USART1->ISR;
	return USART1->SR;
}

uint32_t hal_read_uart_dr_reg(void) {

	// USART1->RDR & 0x1FF
	return USART1->DR & 0x1FF;
}

void hal_clean_isr(void) {
	// USART1->ISR &= ~USART_FLAG_RXNE;
	USART1->SR &= ~USART_FLAG_RXNE;
}

// use printf , but no suggest!!
int fputc(int ch,FILE *f)
{
    uint32_t temp = ch;
    HAL_UART_Transmit(&huart1, (uint8_t *)&temp, 1, 1000);        //huart3是串口的句柄
    return ch;
}




