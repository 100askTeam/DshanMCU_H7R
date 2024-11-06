/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_usbx_device.c
  * @author  MCD Application Team
  * @brief   USBX Device applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "app_usbx_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define UX_DEVICE_APP_MEM_POOL_SIZE              17 * 1024
__ALIGN_BEGIN static UCHAR ux_device_byte_pool_buffer[UX_DEVICE_APP_MEM_POOL_SIZE] __ALIGN_END;

static ULONG cdc_acm_interface_number;
static ULONG cdc_acm_configuration_number;
static UX_SLAVE_CLASS_CDC_ACM_PARAMETER cdc_acm_parameter;

ALIGN_TYPE _ux_utility_interrupt_disable(VOID)
{
    uint32_t saved_flags;
    
    saved_flags = __get_PRIMASK();
    __disable_irq();
    
    return (ALIGN_TYPE)saved_flags;
}


VOID _ux_utility_interrupt_restore(ALIGN_TYPE saved_flags)
{
    __set_PRIMASK(saved_flags);
}


/**
  * @brief  Application USBX Device Initialization.
  * @param  memory_ptr: memory pointer
  * @retval status
  */
UINT MX_USBX_Device_Init(void)
{
  UINT ret = UX_SUCCESS;
  UCHAR *device_framework_high_speed;
  UCHAR *device_framework_full_speed;
  ULONG device_framework_hs_length;
  ULONG device_framework_fs_length;
  ULONG string_framework_length;
  ULONG language_id_framework_length;
  UCHAR *string_framework;
  UCHAR *language_id_framework;
  UCHAR *pointer;

  VOID *memory_ptr = ux_device_byte_pool_buffer;

  /* USER CODE BEGIN MX_USBX_Device_Init0 */

  /* USER CODE END MX_USBX_Device_Init0 */

  pointer = memory_ptr;
  /* Initialize USBX Memory */
  if (ux_system_initialize(pointer, UX_DEVICE_APP_MEM_POOL_SIZE, UX_NULL, 0) != UX_SUCCESS)
  {
    /* USER CODE BEGIN USBX_SYSTEM_INITIALIZE_ERORR */
    return UX_ERROR;
    /* USER CODE END USBX_SYSTEM_INITIALIZE_ERORR */
  }

  /* Get Device Framework High Speed and get the length */
  device_framework_high_speed = USBD_Get_Device_Framework_Speed(USBD_HIGH_SPEED,
                                                                &device_framework_hs_length);

  /* Get Device Framework Full Speed and get the length */
  device_framework_full_speed = USBD_Get_Device_Framework_Speed(USBD_FULL_SPEED,
                                                                &device_framework_fs_length);

  /* Get String Framework and get the length */
  string_framework = USBD_Get_String_Framework(&string_framework_length);

  /* Get Language Id Framework and get the length */
  language_id_framework = USBD_Get_Language_Id_Framework(&language_id_framework_length);

  /* Install the device portion of USBX */
  if (ux_device_stack_initialize(device_framework_high_speed,
                                 device_framework_hs_length,
                                 device_framework_full_speed,
                                 device_framework_fs_length,
                                 string_framework,
                                 string_framework_length,
                                 language_id_framework,
                                 language_id_framework_length,
                                 UX_NULL) != UX_SUCCESS)
  {
    /* USER CODE BEGIN USBX_DEVICE_INITIALIZE_ERORR */
    return UX_ERROR;
    /* USER CODE END USBX_DEVICE_INITIALIZE_ERORR */
  }


  /* Initialize the cdc acm class parameters for the device */
  cdc_acm_parameter.ux_slave_class_cdc_acm_instance_activate   = USBD_CDC_ACM_Activate;
  cdc_acm_parameter.ux_slave_class_cdc_acm_instance_deactivate = USBD_CDC_ACM_Deactivate;
  cdc_acm_parameter.ux_slave_class_cdc_acm_parameter_change    = USBD_CDC_ACM_ParameterChange;

  /* USER CODE BEGIN CDC_ACM_PARAMETER */

  /* USER CODE END CDC_ACM_PARAMETER */

  /* Get cdc acm configuration number */
  cdc_acm_configuration_number = USBD_Get_Configuration_Number(CLASS_TYPE_CDC_ACM, 0);

  /* Find cdc acm interface number */
  cdc_acm_interface_number = USBD_Get_Interface_Number(CLASS_TYPE_CDC_ACM, 0);

  /* Initialize the device cdc acm class */
  if (ux_device_stack_class_register(_ux_system_slave_class_cdc_acm_name,
                                     ux_device_class_cdc_acm_entry,
                                     cdc_acm_configuration_number,
                                     cdc_acm_interface_number,
                                     &cdc_acm_parameter) != UX_SUCCESS)
  {
    /* USER CODE BEGIN USBX_DEVICE_CDC_ACM_REGISTER_ERORR */
    return UX_ERROR;
    /* USER CODE END USBX_DEVICE_CDC_ACM_REGISTER_ERORR */
  }

  return ret;
}


