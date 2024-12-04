/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ux_device_cdc_acm.c
  * @author  MCD Application Team
  * @brief   USBX Device CDC ACM applicative source file
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

/* Includes ------------------------------------------------------------------*/
#include "ux_device_cdc_acm.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdarg.h>
/// reference: https://github.com/STMicroelectronics/stm32-usbx-examples/tree/main/Projects/NUCLEO-H723ZG/Applications/USBX/Ux_Device_CDC_ACM
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

#define APP_RX_DATA_SIZE                          2048
#define APP_TX_DATA_SIZE                          2048

/* Rx/TX flag */
#define RX_NEW_RECEIVED_DATA                      0x01
#define TX_NEW_TRANSMITTED_DATA                   0x02

/* Data length for vcp */
#define VCP_WORDLENGTH8                           8
#define VCP_WORDLENGTH9                           9

/* the minimum baudrate */
#define MIN_BAUDRATE                              9600

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

//static UX_SLAVE_CLASS_CDC_ACM *cdc_acm = NULL;
static uint8_t g_ux_device_cdc_acm_write_buffer[USBX_DEVICE_CDC_ACM_WRITE_BUFFER_SIZE];
static uint8_t g_ux_device_cdc_acm_read_buffer[USBX_DEVICE_CDC_ACM_READ_BUFFER_SIZE];
static uint8_t g_ux_device_cdc_acm_read_actual_length;
static volatile uint8_t g_ux_device_cdc_acm_write_sta = 0;
static uint8_t g_ux_device_cdc_acm_read_sta = 0;
uint8_t *g_ux_device_cdc_acm_rx_buffer = NULL;
uint16_t g_ux_device_cdc_acm_rx_len = 0;

//static SemaphoreHandle_t g_xUSBUARTSend;
//static QueueHandle_t g_xUSBUART_RX_Queue;

UX_SLAVE_CLASS_CDC_ACM  *cdc_acm;
#if defined ( __ICCARM__ ) /* IAR Compiler */
#pragma location = ".UsbxAppSection"
#elif defined ( __CC_ARM ) || defined(__ARMCC_VERSION) /* ARM Compiler 5/6 */
__attribute__((section(".UsbxAppSection")))
#elif defined ( __GNUC__ ) /* GNU Compiler */
__attribute__((section(".UsbxAppSection")))
#endif
/* Data received over uart are stored in this buffer */
uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

/* Data to send over USB CDC are stored in this buffer   */
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

/* Increment this pointer or roll it back to
start address when data are received over USART */
uint32_t UserTxBufPtrIn;

/* Increment this pointer or roll it back to
start address when data are sent over USB */
uint32_t UserTxBufPtrOut;

/* uart handler */
///UART_HandleTypeDef *uart_handler;
//extern TX_EVENT_FLAGS_GROUP EventFlag;

UX_SLAVE_CLASS_CDC_ACM_LINE_CODING_PARAMETER CDC_VCP_LineCoding =
{
  115200, /* baud rate */
  0x00,   /* stop bits-1 */
  0x00,   /* parity - none */
  0x08    /* nb. of bits 8 */
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
//extern VOID USBX_APP_UART_Init(UART_HandleTypeDef **huart);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

static UINT ux_device_class_cdc_acm_write_callback(struct UX_SLAVE_CLASS_CDC_ACM_STRUCT *cdc_acm, UINT status, ULONG length)
{
	UX_PARAMETER_NOT_USED(cdc_acm);
	UX_PARAMETER_NOT_USED(status);
	UX_PARAMETER_NOT_USED(length);

	g_ux_device_cdc_acm_write_sta = 1;

	return UX_SUCCESS;
}

static UINT ux_device_class_cdc_acm_read_callback(struct UX_SLAVE_CLASS_CDC_ACM_STRUCT *cdc_acm, UINT status, UCHAR *data_pointer, ULONG length)
{
    UX_PARAMETER_NOT_USED(cdc_acm);
    UX_PARAMETER_NOT_USED(status);
    
    g_ux_device_cdc_acm_rx_buffer = (uint8_t *)data_pointer;
    g_ux_device_cdc_acm_rx_len = length;
    g_ux_device_cdc_acm_read_sta = 1;

    /* 重新开始CDC ACM读传输 */
    ux_device_class_cdc_acm_read_run(cdc_acm, (UCHAR *)&g_ux_device_cdc_acm_read_buffer, USBX_DEVICE_CDC_ACM_READ_BUFFER_SIZE, (ULONG *)&g_ux_device_cdc_acm_read_actual_length);

    return UX_SUCCESS;
}


/**
  * @brief  USBD_CDC_ACM_Activate
  *         This function is called when insertion of a CDC ACM device.
  * @param  cdc_acm_instance: Pointer to the cdc acm class instance.
  * @retval none
  */
VOID USBD_CDC_ACM_Activate(VOID *cdc_acm_instance)
{
  /* USER CODE BEGIN USBD_CDC_ACM_Activate */

  UX_SLAVE_CLASS_CDC_ACM_CALLBACK_PARAMETER parameter;

  /* Save the CDC instance */
  cdc_acm = (UX_SLAVE_CLASS_CDC_ACM*) cdc_acm_instance;

  parameter.ux_device_class_cdc_acm_parameter_write_callback = ux_device_class_cdc_acm_write_callback;
  parameter.ux_device_class_cdc_acm_parameter_read_callback = ux_device_class_cdc_acm_read_callback;
  ux_device_class_cdc_acm_ioctl(cdc_acm, UX_SLAVE_CLASS_CDC_ACM_IOCTL_TRANSMISSION_START, (VOID *)&parameter);

  /* 开始CDC ACM读传输 */
  ux_device_class_cdc_acm_read_run(cdc_acm, (UCHAR *)&g_ux_device_cdc_acm_read_buffer, USBX_DEVICE_CDC_ACM_READ_BUFFER_SIZE, (ULONG *)&g_ux_device_cdc_acm_read_actual_length);
  return;
}

/**
  * @brief  USBD_CDC_ACM_Deactivate
  *         This function is called when extraction of a CDC ACM device.
  * @param  cdc_acm_instance: Pointer to the cdc acm class instance.
  * @retval none
  */
VOID USBD_CDC_ACM_Deactivate(VOID *cdc_acm_instance)
{
  /* USER CODE BEGIN USBD_CDC_ACM_Deactivate */
  UX_PARAMETER_NOT_USED(cdc_acm_instance);

  /* Reset the cdc acm instance */
  cdc_acm = UX_NULL;

  /* USER CODE END USBD_CDC_ACM_Deactivate */

  return;
}

/**
  * @brief  USBD_CDC_ACM_ParameterChange
  *         This function is invoked to manage the CDC ACM class requests.
  * @param  cdc_acm_instance: Pointer to the cdc acm class instance.
  * @retval none
  */
VOID USBD_CDC_ACM_ParameterChange(VOID *cdc_acm_instance)
{
  /* USER CODE BEGIN USBD_CDC_ACM_ParameterChange */
  //UX_PARAMETER_NOT_USED(cdc_acm_instance);

  ULONG request;
  UX_SLAVE_TRANSFER *transfer_request;
  UX_SLAVE_DEVICE *device;

  /* Get the pointer to the device.  */
  device = &_ux_system_slave -> ux_system_slave_device;

  /* Get the pointer to the transfer request associated with the control endpoint. */
  transfer_request = &device -> ux_slave_device_control_endpoint.ux_slave_endpoint_transfer_request;

  request = *(transfer_request -> ux_slave_transfer_request_setup + UX_SETUP_REQUEST);


  switch (request)
  {
    case UX_SLAVE_CLASS_CDC_ACM_SET_LINE_CODING :

    	CDC_VCP_LineCoding.ux_slave_class_cdc_acm_parameter_baudrate = ((UX_SLAVE_CLASS_CDC_ACM *)cdc_acm_instance)->ux_slave_class_cdc_acm_baudrate;
		  CDC_VCP_LineCoding.ux_slave_class_cdc_acm_parameter_stop_bit = ((UX_SLAVE_CLASS_CDC_ACM *)cdc_acm_instance)->ux_slave_class_cdc_acm_stop_bit;
		  CDC_VCP_LineCoding.ux_slave_class_cdc_acm_parameter_parity = ((UX_SLAVE_CLASS_CDC_ACM *)cdc_acm_instance)->ux_slave_class_cdc_acm_parity;
		  CDC_VCP_LineCoding.ux_slave_class_cdc_acm_parameter_data_bit = ((UX_SLAVE_CLASS_CDC_ACM *)cdc_acm_instance)->ux_slave_class_cdc_acm_data_bit;
		  //ux_device_class_cdc_acm_ioctl((UX_SLAVE_CLASS_CDC_ACM *)cdc_acm, UX_SLAVE_CLASS_CDC_ACM_IOCTL_SET_LINE_CODING, (VOID *)&line_coding);

		  /* Set the Line Coding parameters */
	    if (ux_device_class_cdc_acm_ioctl((UX_SLAVE_CLASS_CDC_ACM *)cdc_acm_instance, UX_SLAVE_CLASS_CDC_ACM_IOCTL_SET_LINE_CODING, &CDC_VCP_LineCoding) != UX_SUCCESS)
      {
        Error_Handler();
      }
      break;

    case UX_SLAVE_CLASS_CDC_ACM_GET_LINE_CODING :
      break;

    case UX_SLAVE_CLASS_CDC_ACM_SET_CONTROL_LINE_STATE :
    default :
      break;
  }

  /* USER CODE END USBD_CDC_ACM_ParameterChange */

  return;
}

/* USER CODE BEGIN 1 */


static void ux_device_cdc_acm_transmit(uint8_t *data, uint32_t len)
{
    if ((cdc_acm != NULL))
    {
        g_ux_device_cdc_acm_write_sta = 0;
        ux_device_class_cdc_acm_write_with_callback(cdc_acm, (UCHAR *)data, (ULONG)len);

        /* waiting for completion */
#if 1
        volatile uint32_t i = 0;
        while (g_ux_device_cdc_acm_write_sta == 0){
          if(++i >= 50000) break; // 1ms //us: (SystemCoreClock / 8U / 1000000U)
          __NOP();
        }
#else
        uint32_t befor_tick;
        uint32_t after_tick;

        befor_tick = HAL_GetTick();
        while (g_ux_device_cdc_acm_write_sta == 0){
          after_tick = HAL_GetTick();
          if((after_tick - befor_tick) >= 2) break;  // 2ms
        }
#endif
    }
}

uint64_t ux_device_cdc_acm_receive(uint8_t *buffer, uint32_t requested_length)
{
	uint64_t actual_length = 0;

	if ((g_ux_device_cdc_acm_read_sta == 1) && (buffer != NULL))
	{
		if(requested_length > g_ux_device_cdc_acm_rx_len) 		actual_length = g_ux_device_cdc_acm_rx_len;
		else if(requested_length < g_ux_device_cdc_acm_rx_len) 	actual_length = requested_length;

		memcpy(buffer, g_ux_device_cdc_acm_rx_buffer, actual_length);

		g_ux_device_cdc_acm_read_sta = 0;
	}

	return actual_length;
}


void ux_device_cdc_acm_printf(char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vsprintf((char *)g_ux_device_cdc_acm_write_buffer, fmt, ap);
    va_end(ap);
    ux_device_cdc_acm_transmit(g_ux_device_cdc_acm_write_buffer, strlen((const char *)g_ux_device_cdc_acm_write_buffer));
}




/* USER CODE END 1 */
