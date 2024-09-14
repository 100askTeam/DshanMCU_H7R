/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    Loader_Src.c
  * @author  MCD Application Team
  * @brief   This file defines the operations of the external memory loader.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "extmemloader_init.h"
#include <string.h>
#include <stdio.h>
#include "extmem_manager.h"
#include "sdmmc.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#if USE_100ASK_SPI_FLASH
#include "spi.h"
#include "X25Qx.h"
#elif USE_100ASK_SDRAM
#include "fmc.h"
#include "sdram.h"
#endif

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void MPU_Config(void)
{
#if USE_100ASK_SPI_FLASH
#if 1
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
#endif
#elif USE_100ASK_SDRAM
#if 1
  MPU_Region_InitTypeDef MPU_InitStruct;

    /* 禁止 MPU */
    HAL_MPU_Disable();

    /** Initializes and configures the Region and the memory to be protected
    */
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER0;
    MPU_InitStruct.BaseAddress = 0x0;
    MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
    MPU_InitStruct.SubRegionDisable = 0xA7;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /** Initializes and configures the Region and the memory to be protected
  	*/
  	MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  	MPU_InitStruct.BaseAddress = 0x20000000;
  	MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
  	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  	HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /* 配置AXI SRAM的MPU属性为Write back, Read allocate，Write allocate */
    MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress      = 0x24000000;
    MPU_InitStruct.Size             = MPU_REGION_SIZE_512KB;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable     = MPU_ACCESS_BUFFERABLE;
    MPU_InitStruct.IsCacheable      = MPU_ACCESS_CACHEABLE;
    MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.Number           = MPU_REGION_NUMBER2;
    MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL1;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /** Initializes and configures the Region and the memory to be protected
  	*/
  	MPU_InitStruct.Number = MPU_REGION_NUMBER3;
  	MPU_InitStruct.BaseAddress = 0x24020000;

  	HAL_MPU_ConfigRegion(&MPU_InitStruct);

  	/** Initializes and configures the Region and the memory to be protected
  	*/
  	MPU_InitStruct.Number = MPU_REGION_NUMBER4;
  	MPU_InitStruct.BaseAddress = 0x24040000;

  	HAL_MPU_ConfigRegion(&MPU_InitStruct);

  	/** Initializes and configures the Region and the memory to be protected
  	*/
  	MPU_InitStruct.Number = MPU_REGION_NUMBER5;
  	MPU_InitStruct.BaseAddress = 0x24060000;
  	MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
  	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;

  	HAL_MPU_ConfigRegion(&MPU_InitStruct);

  	/** Initializes and configures the Region and the memory to be protected
  	*/
  	MPU_InitStruct.Number = MPU_REGION_NUMBER6;
  	MPU_InitStruct.BaseAddress = 0x24070000;
  	MPU_InitStruct.Size = MPU_REGION_SIZE_8KB;

  	HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /* 配置FMC扩展IO的MPU属性为Device或者Strongly Ordered */
    MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress      = 0x60000000;
    MPU_InitStruct.Size             = ARM_MPU_REGION_SIZE_64KB;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable     = MPU_ACCESS_BUFFERABLE;
    MPU_InitStruct.IsCacheable      = MPU_ACCESS_NOT_CACHEABLE;
    MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.Number           = MPU_REGION_NUMBER7;
    MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL0;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /* 配置SDRAM的MPU属性为Write back, Read allocate，Write allocate */
    MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress      = 0xC0000000;
    MPU_InitStruct.Size             = MPU_REGION_SIZE_32MB;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable     = MPU_ACCESS_BUFFERABLE;
    MPU_InitStruct.IsCacheable      = MPU_ACCESS_CACHEABLE;
    MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.Number           = MPU_REGION_NUMBER8;
    MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL1;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /*使能 MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
#else
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* 禁止 MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
	*/
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.BaseAddress = 0x20000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* 配置AXI SRAM的MPU属�?�为Write back, Read allocate，Write allocate */
  MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress      = 0x24000000;
  MPU_InitStruct.Size             = MPU_REGION_SIZE_512KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable     = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable      = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number           = MPU_REGION_NUMBER1;
  MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL1;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
	*/
	MPU_InitStruct.Number = MPU_REGION_NUMBER2;
	MPU_InitStruct.BaseAddress = 0x24020000;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/** Initializes and configures the Region and the memory to be protected
	*/
	MPU_InitStruct.Number = MPU_REGION_NUMBER3;
	MPU_InitStruct.BaseAddress = 0x24040000;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/** Initializes and configures the Region and the memory to be protected
	*/
	MPU_InitStruct.Number = MPU_REGION_NUMBER4;
	MPU_InitStruct.BaseAddress = 0x24060000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/** Initializes and configures the Region and the memory to be protected
	*/
	MPU_InitStruct.Number = MPU_REGION_NUMBER5;
	MPU_InitStruct.BaseAddress = 0x24070000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_8KB;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* 配置FMC扩展IO的MPU属�?�为Device或�?�Strongly Ordered */
  MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress      = 0x60000000;
  MPU_InitStruct.Size             = ARM_MPU_REGION_SIZE_64KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable     = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable      = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number           = MPU_REGION_NUMBER6;
  MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* 配置SDRAM的MPU属�?�为Write back, Read allocate，Write allocate */
  MPU_InitStruct.Enable           = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress      = 0xC0000000;
  MPU_InitStruct.Size             = MPU_REGION_SIZE_32MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable     = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable      = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable      = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number           = MPU_REGION_NUMBER7;
  MPU_InitStruct.TypeExtField     = MPU_TEX_LEVEL1;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec      = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /*使能 MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
#endif
#endif

}
/* USER CODE END 0 */

/**
  * @brief  main entry of the external flash loader initialization.
  * @param  None
  * @retval  0 : operation is ok else operation is failed

  */
uint32_t extmemloader_Init()
{
  uint32_t retr = 0;
  /* USER CODE BEGIN 1 */
  MPU_Config();
  //Comment out: HAL_MPU_Disable(); MX_SDMMC1_SD_Init(); MX_FMC_Init();
  /* USER CODE END 1 */

  /* Init system */
  SystemInit();

  /* disable all the IRQ */
  __disable_irq();

  /* MCU Configuration--------------------------------------------------------*/
  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* MPU Configuration--------------------------------------------------------*/
  //HAL_MPU_Disable();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock  */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  MX_GPIO_Init();

  //MX_SDMMC1_SD_Init();

  //MX_FMC_Init();

  MX_EXTMEM_MANAGER_Init();

  /* USER CODE BEGIN 2 */

#if USE_100ASK_SPI_FLASH
  MX_SPI5_Init();
  X25Qx_SPIFLASH_Init();
#elif USE_100ASK_SDRAM
  MX_FMC_Init();

  //char  * const p_reg = (char *) StartAddresse;
  //*p_reg = 0x12;
#endif
  /* USER CODE END 2 */

  return retr;
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL1.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL1.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL1.PLLM = 4;
  RCC_OscInitStruct.PLL1.PLLN = 25;
  RCC_OscInitStruct.PLL1.PLLP = 1;
  RCC_OscInitStruct.PLL1.PLLQ = 2;
  RCC_OscInitStruct.PLL1.PLLR = 2;
  RCC_OscInitStruct.PLL1.PLLS = 2;
  RCC_OscInitStruct.PLL1.PLLT = 2;
  RCC_OscInitStruct.PLL1.PLLFractional = 0;
  RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL3.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL3.PLLM = 4;
  RCC_OscInitStruct.PLL3.PLLN = 28;
  RCC_OscInitStruct.PLL3.PLLP = 2;
  RCC_OscInitStruct.PLL3.PLLQ = 2;
  RCC_OscInitStruct.PLL3.PLLR = 10;
  RCC_OscInitStruct.PLL3.PLLS = 2;
  RCC_OscInitStruct.PLL3.PLLT = 2;
  RCC_OscInitStruct.PLL3.PLLFractional = 1024;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK4|RCC_CLOCKTYPE_PCLK5;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
  RCC_ClkInitStruct.APB5CLKDivider = RCC_APB5_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

