/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ux_device_cdc_acm.h
  * @author  MCD Application Team
  * @brief   USBX Device CDC ACM applicative header file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UX_DEVICE_CDC_ACM_H__
#define __UX_DEVICE_CDC_ACM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ux_api.h"
#include "ux_device_class_cdc_acm.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define USBX_DEVICE_CDC_ACM_WRITE_BUFFER_SIZE   512 /* CDC ACMд�������ݻ�������С */
#define USBX_DEVICE_CDC_ACM_READ_BUFFER_SIZE    256 /* CDC ACM���������ݻ�������С */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
VOID USBD_CDC_ACM_Activate(VOID *cdc_acm_instance);
VOID USBD_CDC_ACM_Deactivate(VOID *cdc_acm_instance);
VOID USBD_CDC_ACM_ParameterChange(VOID *cdc_acm_instance);

/* USER CODE BEGIN EFP */

VOID usbx_cdc_acm_read_thread_entry(ULONG thread_input);
VOID usbx_cdc_acm_write_thread_entry(ULONG thread_input);

uint64_t ux_device_cdc_acm_receive(uint8_t *buffer, uint32_t requested_length);
void ux_device_cdc_acm_printf(char *fmt, ...);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif  /* __UX_DEVICE_CDC_ACM_H__ */
