
#ifdef BOARD_MKS_ROBIN_NANO_V3_INI

#include "hal_robin_nano_v3_system.h"
#include "../bsp_tim.h"

void Bsp_RobinNanoV3_SystemInit(void) {

  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  Bsp_RobinNanoV3_ClkInit();
}

void Bsp_RobinNanoV3_ClkInit(void) {

  HAL_RCC_GPIO_ENABLE(A);
  HAL_RCC_GPIO_ENABLE(B);
  HAL_RCC_GPIO_ENABLE(C);
  HAL_RCC_GPIO_ENABLE(D);
  HAL_RCC_GPIO_ENABLE(E);
}


uint8_t BspGetEepromAddress(uint32_t addr) {
  if(addr<ADDR_FLASH_SECTOR_0)return FLASH_SECTOR_0;
  else if(addr<ADDR_FLASH_SECTOR_1)return FLASH_SECTOR_1;
  else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_SECTOR_2;
  else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_SECTOR_3;
  else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_SECTOR_4;
  else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_SECTOR_5;
  else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_SECTOR_6;
  else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_SECTOR_7;
  else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_SECTOR_8;
  else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_SECTOR_9;
  else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_SECTOR_10;
  else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_SECTOR_11;
  return FLASH_SECTOR_11;
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#endif
