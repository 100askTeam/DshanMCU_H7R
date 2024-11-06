/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usb_otg.c
  * @brief   This file provides code for the configuration
  *          of the USB_OTG instances.
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
#include "usb_otg.h"

/* USER CODE BEGIN 0 */
#include "ux_port.h"
#include "ux_device_descriptors.h"
#include "ux_dcd_stm32.h"

/* USER CODE END 0 */

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USB_OTG_FS init function */

void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */
  UINT MX_USBX_Device_Init(void);
  MX_USBX_Device_Init();
  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.Sof_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.battery_charging_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */
  //HAL_PWREx_EnableVddUSB();
  HAL_PWREx_EnableUSBVoltageDetector();

  //HAL_PCDEx_PMAConfig(&hpcd_USB_OTG_FS, 0x00, PCD_SNG_BUF, 0x14);
  //HAL_PCDEx_PMAConfig(&hpcd_USB_OTG_FS, 0x80, PCD_SNG_BUF, 0x54);
  //HAL_PCDEx_PMAConfig(&hpcd_USB_OTG_FS, USBD_CDCACM_EPINCMD_ADDR, PCD_SNG_BUF, 0x94);
  //HAL_PCDEx_PMAConfig(&hpcd_USB_OTG_FS, USBD_CDCACM_EPOUT_ADDR, PCD_SNG_BUF, 0xD4);
  //HAL_PCDEx_PMAConfig(&hpcd_USB_OTG_FS, USBD_CDCACM_EPIN_ADDR, PCD_SNG_BUF, 0x114);

  /* Set Rx FIFO */
  HAL_PCDEx_SetRxFiFo(&hpcd_USB_OTG_FS, 0x200);

  /* Set Tx FIFO 0 */
  HAL_PCDEx_SetTxFiFo(&hpcd_USB_OTG_FS, 0, 0x10);

  /* Set Tx FIFO 2 */
  HAL_PCDEx_SetTxFiFo(&hpcd_USB_OTG_FS, 1, 0x10);

  /* Set Tx FIFO 3 */
  HAL_PCDEx_SetTxFiFo(&hpcd_USB_OTG_FS, 2, 0x20);
  /* USER CODE END USB_Device_Init_PreTreatment_1 */

  ux_dcd_stm32_initialize((ULONG) USB_OTG_FS, (ULONG) &hpcd_USB_OTG_FS);

  HAL_PCD_Start(&hpcd_USB_OTG_FS);
  /* USER CODE END USB_OTG_FS_Init 2 */

}

void HAL_PCD_MspInit(PCD_HandleTypeDef* pcdHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(pcdHandle->Instance==USB_OTG_FS)
  {
  /* USER CODE BEGIN USB_OTG_FS_MspInit 0 */

  /* USER CODE END USB_OTG_FS_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USBOTGFS;
    PeriphClkInit.UsbOtgFsClockSelection = RCC_USBOTGFSCLKSOURCE_HSI48;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

  /** Enable USB Voltage detector
  */
    HAL_PWREx_EnableUSBVoltageDetector();

    /* USB_OTG_FS clock enable */
    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
    __HAL_RCC_USBPHYC_CLK_ENABLE();

    /* USB_OTG_FS interrupt Init */
    HAL_NVIC_SetPriority(OTG_FS_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
  /* USER CODE BEGIN USB_OTG_FS_MspInit 1 */

  /* USER CODE END USB_OTG_FS_MspInit 1 */
  }
}

void HAL_PCD_MspDeInit(PCD_HandleTypeDef* pcdHandle)
{

  if(pcdHandle->Instance==USB_OTG_FS)
  {
  /* USER CODE BEGIN USB_OTG_FS_MspDeInit 0 */

  /* USER CODE END USB_OTG_FS_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USB_OTG_FS_CLK_DISABLE();
    __HAL_RCC_USBPHYC_CLK_DISABLE();

    /* USB_OTG_FS interrupt Deinit */
    HAL_NVIC_DisableIRQ(OTG_FS_IRQn);
  /* USER CODE BEGIN USB_OTG_FS_MspDeInit 1 */

  /* USER CODE END USB_OTG_FS_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
