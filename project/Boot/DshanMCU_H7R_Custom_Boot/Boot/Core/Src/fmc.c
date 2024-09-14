/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : FMC.c
  * Description        : This file provides code for the configuration
  *                      of the FMC peripheral.
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
#include "fmc.h"

/* USER CODE BEGIN 0 */
#include "sdram.h"
/* USER CODE END 0 */

SDRAM_HandleTypeDef hsdram1;

/* FMC initialization function */
void MX_FMC_Init(void)
{
  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_SDRAM_TimingTypeDef SdramTiming = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the SDRAM1 memory initialization sequence
  */
  hsdram1.Instance = FMC_SDRAM_DEVICE;
  /* hsdram1.Init */
  hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 2;
  SdramTiming.ExitSelfRefreshDelay = 8;
  SdramTiming.SelfRefreshTime = 6;
  SdramTiming.RowCycleDelay = 6;
  SdramTiming.WriteRecoveryTime = 2;
  SdramTiming.RPDelay = 2;
  SdramTiming.RCDDelay = 6;

  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FMC_Init 2 */
  FMC_SDRAM_CommandTypeDef command;
  SDRAM_Initialization_Sequence(&hsdram1, &command);
  /* USER CODE END FMC_Init 2 */
}

static uint32_t FMC_Initialized = 0;

static void HAL_FMC_MspInit(void){
  /* USER CODE BEGIN FMC_MspInit 0 */

  /* USER CODE END FMC_MspInit 0 */
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (FMC_Initialized) {
    return;
  }
  FMC_Initialized = 1;
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_FMC;
    PeriphClkInit.FmcClockSelection = RCC_FMCCLKSOURCE_HCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

  /* Peripheral clock enable */
  __HAL_RCC_FMC_CLK_ENABLE();

  /** FMC GPIO Configuration
  PE0   ------> FMC_D9
  PF3   ------> FMC_A11
  PF2   ------> FMC_A10
  PE14   ------> FMC_SDNE0
  PE2   ------> FMC_D11
  PF0   ------> FMC_A8
  PD7   ------> FMC_D8
  PE13   ------> FMC_SDNCAS
  PD1   ------> FMC_A7
  PE1   ------> FMC_D10
  PF1   ------> FMC_A9
  PE11   ------> FMC_SDNWE
  PD0   ------> FMC_A6
  PE15   ------> FMC_SDCKE0
  PE6   ------> FMC_D15
  PE4   ------> FMC_D13
  PE12   ------> FMC_SDNRAS
  PE5   ------> FMC_D14
  PE3   ------> FMC_D12
  PN3   ------> FMC_D1
  PN11   ------> FMC_D7
  PN10   ------> FMC_D6
  PN9   ------> FMC_D5
  PN2   ------> FMC_D0
  PC0   ------> FMC_NBL1
  PN8   ------> FMC_D4
  PN4   ------> FMC_D2
  PN5   ------> FMC_D3
  PC1   ------> FMC_A0
  PC2   ------> FMC_A1
  PC3   ------> FMC_A2
  PC4   ------> FMC_A3
  PE7   ------> FMC_A4
  PD8   ------> FMC_NBL0
  PC5   ------> FMC_A5
  PE9   ------> FMC_BA0
  PD9   ------> FMC_SDCLK
  PE8   ------> FMC_A12
  PE10   ------> FMC_BA1
  */
  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_14|GPIO_PIN_2|GPIO_PIN_13
                          |GPIO_PIN_1|GPIO_PIN_11|GPIO_PIN_15|GPIO_PIN_6
                          |GPIO_PIN_4|GPIO_PIN_12|GPIO_PIN_5|GPIO_PIN_3
                          |GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_8
                          |GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9
                          |GPIO_PIN_2|GPIO_PIN_8|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

  HAL_GPIO_Init(GPION, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;

  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF14_FMC;

  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* USER CODE BEGIN FMC_MspInit 1 */

  /* USER CODE END FMC_MspInit 1 */
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* sdramHandle){
  /* USER CODE BEGIN SDRAM_MspInit 0 */

  /* USER CODE END SDRAM_MspInit 0 */
  HAL_FMC_MspInit();
  /* USER CODE BEGIN SDRAM_MspInit 1 */

  /* USER CODE END SDRAM_MspInit 1 */
}

static uint32_t FMC_DeInitialized = 0;

static void HAL_FMC_MspDeInit(void){
  /* USER CODE BEGIN FMC_MspDeInit 0 */

  /* USER CODE END FMC_MspDeInit 0 */
  if (FMC_DeInitialized) {
    return;
  }
  FMC_DeInitialized = 1;
  /* Peripheral clock enable */
  __HAL_RCC_FMC_CLK_DISABLE();

  /** FMC GPIO Configuration
  PE0   ------> FMC_D9
  PF3   ------> FMC_A11
  PF2   ------> FMC_A10
  PE14   ------> FMC_SDNE0
  PE2   ------> FMC_D11
  PF0   ------> FMC_A8
  PD7   ------> FMC_D8
  PE13   ------> FMC_SDNCAS
  PD1   ------> FMC_A7
  PE1   ------> FMC_D10
  PF1   ------> FMC_A9
  PE11   ------> FMC_SDNWE
  PD0   ------> FMC_A6
  PE15   ------> FMC_SDCKE0
  PE6   ------> FMC_D15
  PE4   ------> FMC_D13
  PE12   ------> FMC_SDNRAS
  PE5   ------> FMC_D14
  PE3   ------> FMC_D12
  PN3   ------> FMC_D1
  PN11   ------> FMC_D7
  PN10   ------> FMC_D6
  PN9   ------> FMC_D5
  PN2   ------> FMC_D0
  PC0   ------> FMC_NBL1
  PN8   ------> FMC_D4
  PN4   ------> FMC_D2
  PN5   ------> FMC_D3
  PC1   ------> FMC_A0
  PC2   ------> FMC_A1
  PC3   ------> FMC_A2
  PC4   ------> FMC_A3
  PE7   ------> FMC_A4
  PD8   ------> FMC_NBL0
  PC5   ------> FMC_A5
  PE9   ------> FMC_BA0
  PD9   ------> FMC_SDCLK
  PE8   ------> FMC_A12
  PE10   ------> FMC_BA1
  */

  HAL_GPIO_DeInit(GPIOE, GPIO_PIN_0|GPIO_PIN_14|GPIO_PIN_2|GPIO_PIN_13
                          |GPIO_PIN_1|GPIO_PIN_11|GPIO_PIN_15|GPIO_PIN_6
                          |GPIO_PIN_4|GPIO_PIN_12|GPIO_PIN_5|GPIO_PIN_3
                          |GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_8|GPIO_PIN_10);

  HAL_GPIO_DeInit(GPIOF, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_0|GPIO_PIN_1);

  HAL_GPIO_DeInit(GPIOD, GPIO_PIN_7|GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_8
                          |GPIO_PIN_9);

  HAL_GPIO_DeInit(GPION, GPIO_PIN_3|GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9
                          |GPIO_PIN_2|GPIO_PIN_8|GPIO_PIN_4|GPIO_PIN_5);

  HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5);

  /* USER CODE BEGIN FMC_MspDeInit 1 */

  /* USER CODE END FMC_MspDeInit 1 */
}

void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* sdramHandle){
  /* USER CODE BEGIN SDRAM_MspDeInit 0 */

  /* USER CODE END SDRAM_MspDeInit 0 */
  HAL_FMC_MspDeInit();
  /* USER CODE BEGIN SDRAM_MspDeInit 1 */

  /* USER CODE END SDRAM_MspDeInit 1 */
}
/**
  * @}
  */

/**
  * @}
  */
