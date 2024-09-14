/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lvgl.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* Initialize TIMx peripheral as follows:
   + Prescaler = (SystemCoreClock/2 / 1000000) - 1
   + Period = (40 - 1)
   + ClockDivision = 0
   + Counter direction = Up
*/
#define  PRESCALER_VALUE     (uint32_t)(((SystemCoreClock/2) / 1000000) - 1)
#define  PERIOD_VALUE        (uint32_t)(1000 - 1)              /* Period Value  */
#define  PULSE1_VALUE        (uint32_t)(1000 / 2)              /* Capture Compare 1 Value  */

#define WS28XX_TIMER_FREQUENCY_MHZ	(SystemCoreClock/1000000)

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_H 480
#define LCD_W 480
#define W800_RESET_Pin GPIO_PIN_6
#define W800_RESET_GPIO_Port GPIOM
#define GTP_RST_Pin GPIO_PIN_8
#define GTP_RST_GPIO_Port GPIOB
#define W800_WKUP_Pin GPIO_PIN_5
#define W800_WKUP_GPIO_Port GPIOM
#define GTP_INT_Pin GPIO_PIN_9
#define GTP_INT_GPIO_Port GPIOB
#define W800_BOOT_Pin GPIO_PIN_13
#define W800_BOOT_GPIO_Port GPIOM
#define GTP_SDA_Pin GPIO_PIN_7
#define GTP_SDA_GPIO_Port GPIOB
#define GTP_SCL_Pin GPIO_PIN_6
#define GTP_SCL_GPIO_Port GPIOB
#define RGB_LCD_INIT_RESET_PIN_Pin GPIO_PIN_12
#define RGB_LCD_INIT_RESET_PIN_GPIO_Port GPIOG
#define RGB_LCD_INIT_CS_PIN_Pin GPIO_PIN_6
#define RGB_LCD_INIT_CS_PIN_GPIO_Port GPIOF
#define IR_REC_Pin GPIO_PIN_4
#define IR_REC_GPIO_Port GPIOA
#define IR_REC_EXTI_IRQn EXTI4_IRQn
#define RGB_LCD_INIT_SCK_PIN_Pin GPIO_PIN_15
#define RGB_LCD_INIT_SCK_PIN_GPIO_Port GPIOF
#define USER_KEY3_Pin GPIO_PIN_2
#define USER_KEY3_GPIO_Port GPIOP
#define USER_KEY4_Pin GPIO_PIN_3
#define USER_KEY4_GPIO_Port GPIOP
#define USER_KEY1_Pin GPIO_PIN_0
#define USER_KEY1_GPIO_Port GPIOP
#define RGB_LCD_INIT_SDA_PIN_Pin GPIO_PIN_14
#define RGB_LCD_INIT_SDA_PIN_GPIO_Port GPIOF
#define EC11_A_Pin GPIO_PIN_5
#define EC11_A_GPIO_Port GPIOP
#define USER_KEY2_Pin GPIO_PIN_1
#define USER_KEY2_GPIO_Port GPIOP
#define PASSIVE_BUZZER_Pin GPIO_PIN_13
#define PASSIVE_BUZZER_GPIO_Port GPIOD
#define WS2812B_LED_Pin GPIO_PIN_1
#define WS2812B_LED_GPIO_Port GPIOB
#define EC11_D_Pin GPIO_PIN_4
#define EC11_D_GPIO_Port GPIOP
#define EC11_B_Pin GPIO_PIN_6
#define EC11_B_GPIO_Port GPIOP

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
