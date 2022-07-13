#include "hal_uart.h"


hal_uart_t rb_serial_rx;

UART_HandleTypeDef laser_uart;
UART_HandleTypeDef tft_uart;

DMA_HandleTypeDef dma_tx;
DMA_HandleTypeDef dma_rx;

uint8_t laser_dma_rx_buf[5];

// #define DATA_MAX 1024
// uint16_t UART3_RX_NUM = 0;
// uint8_t UART3_RX_BUFFER[DATA_MAX];
hal_uart_dma_t hal_uart_dma;


static void uart2_dma_init();
static void uart_dma_settings();

/************************************************************
 * 			For Serial UART
 * *********************************************************/
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

	uart2_dma_init();

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

	uart_dma_settings();

	hal_uart_irq_set();

	__HAL_UART_ENABLE_IT(&laser_uart, UART_IT_IDLE);

	HAL_UART_Receive_DMA(&laser_uart, hal_uart_dma.dma_i_buff, UART_DMA_MAX_BUFF);
}

void hal_uart_irq_set(void) {
	HAL_NVIC_SetPriority(LaserUART_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LaserUART_IRQn);
	__HAL_UART_ENABLE_IT(&laser_uart, UART_IT_RXNE);
}

void hal_laser_uart_irq_enable(void) { __HAL_UART_ENABLE_IT(&laser_uart, UART_IT_RXNE); }
void hal_laser_uart_irq_disable(void) { __HAL_UART_DISABLE_IT(&laser_uart, UART_IT_RXNE); }
void hal_uart_sendbyte(uint8_t data) { HAL_UART_Transmit(&laser_uart, &data, 1, 1000); }

uint8_t hal_uart_read_dr(void) { 

#ifdef STM32G0B0xx
	return laser_uart.Instance->RDR;
#endif

#ifdef STM32F429xx
	return laser_uart.Instance->DR;
#endif
}

bool hal_is_uart_sr_txe(void) { 
#ifdef STM32F429xx
	return (__HAL_UART_GET_FLAG(&laser_uart, USART_FLAG_TXE));
#elif defined(STM32G0B0xx)
	return (__HAL_UART_GET_FLAG(&laser_uart, UART_FLAG_TC)); 
#endif
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



/************************************************************
 * 			For UART DMA Settings
 * *********************************************************/


static void uart2_dma_init() {

	__HAL_RCC_DMA1_CLK_ENABLE();

	HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

static void uart_dma_settings() {

	/* USART2 DMA Init */
    /* USART2_RX Init */
	
    hal_uart_dma.hdma_rx.Instance = DMA1_Channel1;
    hal_uart_dma.hdma_rx.Init.Request = DMA_REQUEST_USART2_RX;
    hal_uart_dma.hdma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hal_uart_dma.hdma_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hal_uart_dma.hdma_rx.Init.MemInc = DMA_MINC_ENABLE;
    hal_uart_dma.hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hal_uart_dma.hdma_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hal_uart_dma.hdma_rx.Init.Mode = DMA_CIRCULAR;
    hal_uart_dma.hdma_rx.Init.Priority = DMA_PRIORITY_MEDIUM;
    if (HAL_DMA_Init(&hal_uart_dma.hdma_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(&laser_uart, hdmarx, hal_uart_dma.hdma_rx);
}


void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hal_uart_dma.hdma_rx);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}


// Serial UART ISR Handler
void LASER_UART_IRQHANDLER() {

#if defined(USE_FREERTOS_RTOS)
	uint32_t ulReturn;
#endif
	// __IO uint16_t data;

#if defined(USE_FREERTOS_RTOS)
	ulReturn = taskENTER_CRITICAL_FROM_ISR();
#endif

	// if(LASER_UART_RX_FLAG) {
	// 	data = hal_uart_read_dr();
	// 	laser_uart_rx_handler(data);
	// }

	uint8_t temp1,temp2 = 0;

	temp1 = __HAL_UART_GET_FLAG(&laser_uart, UART_FLAG_IDLE);
	temp2 = __HAL_UART_GET_IT_SOURCE(&laser_uart, UART_IT_IDLE);

	if((temp1 != RESET)&&(temp2 != RESET))
	{
		__HAL_UART_CLEAR_IDLEFLAG(&laser_uart);										//清除中断标志位
		__HAL_DMA_DISABLE(&hal_uart_dma.hdma_rx);									//失能DMA_UART3_RX	
		hal_uart_dma.dma_count = (UART_DMA_MAX_BUFF) - hal_uart_dma.hdma_rx.Instance->CNDTR;	//获取DMA搬运的数据
		hal_uart_dma.hdma_rx.Instance->CNDTR = UART_DMA_MAX_BUFF;					//设置DMA_UART3_RX接收大小为DATA_MAX，即重新等待接收。
		/*  
			
			这里需要处理接收的数据
		*/
		HAL_UART_Transmit(&laser_uart,hal_uart_dma.dma_i_buff,(hal_uart_dma.dma_count),10);

		__HAL_DMA_ENABLE(&hal_uart_dma.hdma_rx);							//使能DMA_UART_RX
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

/*************************************************************
 * A ringbuffer init
 * **********************************************************/
void serial_rb_init(hal_uart_t *rb) {
	rb->head = 0;
	rb->tail = 0;
}

/*************************************************************
 * write a data to ringbuffer
 * **********************************************************/
void serial_rb_write(hal_uart_t *rb, uint8_t data) {

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
uint8_t serial_rb_read(hal_uart_t *rb, uint8_t *data) {

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
uint16_t serial_rb_abailable(hal_uart_t *rb) {

	uint8_t tmp_tail = rb->tail;						
	if(rb->head > tmp_tail) return (rb->head - tmp_tail);
	return (tmp_tail - rb->head); 
}

/*************************************************************
 * get ringbuffer count
 * **********************************************************/
uint16_t serial_rb_buff_count(hal_uart_t *rb) {

	uint8_t tmp_tail = rb->tail;
	if(rb->head >= tmp_tail) {return (rb->head - tmp_tail);}
	return (UART_RB_BUFF_MAX - (tmp_tail - rb->head));
} 

/************************************************************
 * Reset ringbuffer
 * *********************************************************/
void serial_rb_reset(hal_uart_t *rb) {

	rb->tail = rb->head;
}





