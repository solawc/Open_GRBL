/*
 bsp_sdram.c

 Copyright (c) 2021-2022 sola

 This part of the code belongs to the corresponding platform that 
 I adapt to, has nothing to do with GRBL, and is only related to 
 the platform. Therefore, if you use this part of the code, 
 please indicate the source
*/

#include "bsp_sdram.h"

#ifdef HAS_SDRAM

FMC_SDRAM_CommandTypeDef Command;

SDRAM_HandleTypeDef sdramHandle;

static void SDRAM_delay(__IO uint32_t nCount)
{
  __IO uint32_t index = 0; 
  for(index = (100000 * nCount); index != 0; index--)
  {
  }
}

static void sdramFmcGpioInit(void)
{		
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* 使能SDRAM相关的GPIO时钟 */

  /*地址信号线*/
  FMC_A0_GPIO_CLK;  FMC_A1_GPIO_CLK;  FMC_A2_GPIO_CLK;
  FMC_A3_GPIO_CLK;FMC_A4_GPIO_CLK;FMC_A5_GPIO_CLK;
  FMC_A6_GPIO_CLK; FMC_A7_GPIO_CLK; FMC_A8_GPIO_CLK;
  FMC_A9_GPIO_CLK; FMC_A10_GPIO_CLK;FMC_A11_GPIO_CLK; 
  FMC_A12_GPIO_CLK;
  /*数据信号线*/
  FMC_D0_GPIO_CLK; FMC_D1_GPIO_CLK ; FMC_D2_GPIO_CLK ; 
  FMC_D3_GPIO_CLK ; FMC_D4_GPIO_CLK ; FMC_D5_GPIO_CLK ;
  FMC_D6_GPIO_CLK; FMC_D7_GPIO_CLK ; FMC_D8_GPIO_CLK ;
  FMC_D9_GPIO_CLK ;FMC_D10_GPIO_CLK; FMC_D11_GPIO_CLK;
  FMC_D12_GPIO_CLK; FMC_D13_GPIO_CLK; FMC_D14_GPIO_CLK;
  FMC_D15_GPIO_CLK;  
  /*控制信号线*/
  FMC_CS_GPIO_CLK ; FMC_BA0_GPIO_CLK; FMC_BA1_GPIO_CLK ;
  FMC_WE_GPIO_CLK ; FMC_RAS_GPIO_CLK ; FMC_CAS_GPIO_CLK;
  FMC_CLK_GPIO_CLK ; FMC_CKE_GPIO_CLK; FMC_UDQM_GPIO_CLK;
  FMC_LDQM_GPIO_CLK;

  /*-- GPIO 配置 -----------------------------------------------------*/

  /* 通用 GPIO 配置 */       
  GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;//配置为复用功能
  GPIO_InitStructure.Pull      = GPIO_PULLUP;
  GPIO_InitStructure.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStructure.Alternate = GPIO_AF12_FMC;
  
  
  /*地址信号线 针对引脚配置*/
  GPIO_InitStructure.Pin = FMC_A0_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A0_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.Pin = FMC_A1_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A1_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.Pin = FMC_A2_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A2_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.Pin = FMC_A3_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A3_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.Pin = FMC_A4_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A4_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.Pin = FMC_A5_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A5_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_A6_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A6_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_A7_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A7_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_A8_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A8_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_A9_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A9_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_A10_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A10_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_A11_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A11_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.Pin = FMC_A12_GPIO_PIN; 
  HAL_GPIO_Init(FMC_A12_GPIO_PORT, &GPIO_InitStructure);
  
  
  /*数据信号线 针对引脚配置*/
  GPIO_InitStructure.Pin = FMC_D0_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D0_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D1_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D1_GPIO_PORT, &GPIO_InitStructure);

    
  GPIO_InitStructure.Pin = FMC_D2_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D2_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D3_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D3_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D4_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D4_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D5_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D5_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D6_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D6_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D7_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D7_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D8_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D8_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D9_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D9_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D10_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D10_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D11_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D11_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D12_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D12_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D13_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D13_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D14_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D14_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_D15_GPIO_PIN; 
  HAL_GPIO_Init(FMC_D15_GPIO_PORT, &GPIO_InitStructure);

  
  /*控制信号线*/
  GPIO_InitStructure.Pin = FMC_CS_GPIO_PIN; 
  HAL_GPIO_Init(FMC_CS_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_BA0_GPIO_PIN; 
  HAL_GPIO_Init(FMC_BA0_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_BA1_GPIO_PIN;
  HAL_GPIO_Init(FMC_BA1_GPIO_PORT, &GPIO_InitStructure);

    
  GPIO_InitStructure.Pin = FMC_WE_GPIO_PIN; 
  HAL_GPIO_Init(FMC_WE_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_RAS_GPIO_PIN; 
  HAL_GPIO_Init(FMC_RAS_GPIO_PORT, &GPIO_InitStructure);

    
  GPIO_InitStructure.Pin = FMC_CAS_GPIO_PIN; 
  HAL_GPIO_Init(FMC_CAS_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_CLK_GPIO_PIN; 
  HAL_GPIO_Init(FMC_CLK_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_CKE_GPIO_PIN; 
  HAL_GPIO_Init(FMC_CKE_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_UDQM_GPIO_PIN; 
  HAL_GPIO_Init(FMC_UDQM_GPIO_PORT, &GPIO_InitStructure);

  
  GPIO_InitStructure.Pin = FMC_LDQM_GPIO_PIN; 
  HAL_GPIO_Init(FMC_LDQM_GPIO_PORT, &GPIO_InitStructure);

}

static void sdramInitSequence(void)
{
  uint32_t tmpr = 0;
  
/* Step 3 --------------------------------------------------------------------*/
  /* 配置命令：开启提供给SDRAM的时钟 */
  Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
  Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
  Command.AutoRefreshNumber = 1;
  Command.ModeRegisterDefinition = 0;
/* Send the command */
  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

  /* Step 2: Insert 100 us minimum delay */ 
  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
  SDRAM_delay(1);
    
/* Step 5 --------------------------------------------------------------------*/
  /* 配置命令：对所有的bank预充电 */ 
  Command.CommandMode = FMC_SDRAM_CMD_PALL;
  Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
  Command.AutoRefreshNumber = 1;
  Command.ModeRegisterDefinition = 0;
/* Send the command */
  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);   
  
/* Step 6 --------------------------------------------------------------------*/
  /* 配置命令：自动刷新 */   
  Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
  Command.AutoRefreshNumber = 4;
  Command.ModeRegisterDefinition = 0;
 /* Send the command */
  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);
  
/* Step 7 --------------------------------------------------------------------*/
  /* 设置sdram寄存器配置 */
  tmpr = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
                   SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                   SDRAM_MODEREG_CAS_LATENCY_3           |
                   SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                   SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
  
  /* 配置命令：设置SDRAM寄存器 */
  Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
  Command.AutoRefreshNumber = 1;
  Command.ModeRegisterDefinition = tmpr;
  /* Send the command */
  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);
  
/* Step 8 --------------------------------------------------------------------*/

  /* 设置刷新计数器 */
  /*刷新速率 = (COUNT + 1) x SDRAM 频率时钟
    COUNT =（ SDRAM 刷新周期/行数) - 20*/
  /* 64ms/8192=7.813us  (7.813 us x FSDCLK) - 20 =683 */
  HAL_SDRAM_ProgramRefreshRate(&sdramHandle, 683); 
}

void sdramInit(void)
{
  /* 配置FMC接口相关的 GPIO*/
  sdramFmcGpioInit();
  
  /* 使能 FMC 时钟 */
	__HAL_RCC_FMC_CLK_ENABLE();
 
  FMC_SDRAM_TimingTypeDef SdramTiming;

  /** Perform the SDRAM1 memory initialization sequence
  */
  sdramHandle.Instance = FMC_SDRAM_DEVICE;
  /* sdramHandle.Init */
  sdramHandle.Init.SDBank = FMC_SDRAM_BANK2;
  sdramHandle.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;
  sdramHandle.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;
  sdramHandle.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  sdramHandle.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  sdramHandle.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
  sdramHandle.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  sdramHandle.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
  sdramHandle.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
  sdramHandle.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 2;
  SdramTiming.ExitSelfRefreshDelay = 7;
  SdramTiming.SelfRefreshTime = 4;
  SdramTiming.RowCycleDelay = 7;
  SdramTiming.WriteRecoveryTime = 2;
  SdramTiming.RPDelay = 2;
  SdramTiming.RCDDelay = 2;

  HAL_SDRAM_Init(&sdramHandle, &SdramTiming);  
  /* FMC SDRAM device initialization sequence */
  sdramInitSequence(); 
}

void SDRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize)
{
  __IO uint32_t write_pointer = (uint32_t)uwWriteAddress;

  /* 禁止写保护 */
  HAL_SDRAM_WriteProtection_Disable(&sdramHandle);
  /* 检查SDRAM标志，等待至SDRAM空闲 */ 
  while(HAL_SDRAM_GetState(&sdramHandle) != HAL_SDRAM_STATE_RESET)
  {
  }

  /* 循环写入数据 */
  for (; uwBufferSize != 0; uwBufferSize--) 
  {
    /* 发送数据到SDRAM */
    *(uint32_t *) (SDRAM_BANK_ADDR + write_pointer) = *pBuffer++;

    /* 地址自增*/
    write_pointer += 4;
  }
    
}

void SDRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize)
{
  __IO uint32_t write_pointer = (uint32_t)uwReadAddress;
  
   
  /* 检查SDRAM标志，等待至SDRAM空闲 */  
  while ( HAL_SDRAM_GetState(&sdramHandle) != HAL_SDRAM_STATE_RESET)
  {
  }
  
  /*读取数据 */
  for(; uwBufferSize != 0x00; uwBufferSize--)
  {
   *pBuffer++ = *(__IO uint32_t *)(SDRAM_BANK_ADDR + write_pointer );
    
   /* 地址自增*/
    write_pointer += 4;
  } 
}

uint8_t SDRAM_Test(void)
{
  /*写入数据计数器*/
  uint32_t counter=0;
  
  /* 8位的数据 */
  uint8_t ubWritedata_8b = 0, ubReaddata_8b = 0;  
  
  /* 16位的数据 */
  uint16_t uhWritedata_16b = 0, uhReaddata_16b = 0; 
  
  SDRAM_INFO("SDRAM Test in 8Bit Write\n");


  /*按8位格式读写数据，并校验*/
  
  /* 把SDRAM数据全部重置为0 ，IS42S16400J_SIZE是以8位为单位的 */
  for (counter = 0x00; counter < IS42S16400J_SIZE; counter++)
  {
    *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)0x0;
  }
  
  /* 向整个SDRAM写入数据  8位 */
  for (counter = 0; counter < IS42S16400J_SIZE; counter++)
  {
    *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)(ubWritedata_8b + counter);
  }
  
  /* 读取 SDRAM 数据并检测*/
  for(counter = 0; counter<IS42S16400J_SIZE;counter++ )
  {
    ubReaddata_8b = *(__IO uint8_t*)(SDRAM_BANK_ADDR + counter);  //从该地址读出数据
    
    if(ubReaddata_8b != (uint8_t)(ubWritedata_8b + counter))      //检测数据，若不相等，跳出函数,返回检测失败结果。
    {
      SDRAM_ERROR("8bit data write error\n");
      return 0;
    }
  }
	
  
  /*按16位格式读写数据，并检测*/
  
  /* 把SDRAM数据全部重置为0 */
  for (counter = 0x00; counter < IS42S16400J_SIZE/2; counter++)
  {
    *(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*counter) = (uint16_t)0x00;
  }
  
  /* 向整个SDRAM写入数据  16位 */
  for (counter = 0; counter < IS42S16400J_SIZE/2; counter++)
  {
    *(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*counter) = (uint16_t)(uhWritedata_16b + counter);
  }
  
    /* 读取 SDRAM 数据并检测*/
  for(counter = 0; counter<IS42S16400J_SIZE/2;counter++ )
  {
    uhReaddata_16b = *(__IO uint16_t*)(SDRAM_BANK_ADDR + 2*counter);  //从该地址读出数据
    
    if(uhReaddata_16b != (uint16_t)(uhWritedata_16b + counter))      //检测数据，若不相等，跳出函数,返回检测失败结果。
    {
      SDRAM_ERROR("16bit data write error\n");

      return 0;
    }
  }

  SDRAM_INFO("SDRAM Succeed\n"); 
  /*检测正常，return 1 */
  return 1;

}

#endif




