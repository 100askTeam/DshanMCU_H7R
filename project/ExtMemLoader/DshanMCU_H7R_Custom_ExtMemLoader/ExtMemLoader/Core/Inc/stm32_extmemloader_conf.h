
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32_extmemloader_conf.h
  * @author  MCD Application Team
  * @brief   This file contains the device information.
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
/*
#if USE_100ASK_SPI_FLASH
#define        STM32EXTLOADER_DEVICE_MEMORY_ID           EXTMEMORY_1
#define        STM32EXTLOADER_DEVICE_NAME                "DshanMCU_H7R_SPI_FLASH_Memory_Loader"
#define        STM32EXTLOADER_DEVICE_TYPE                SPI_FLASH
#define        STM32EXTLOADER_DEVICE_ADDR                0x00000000
#define        STM32EXTLOADER_DEVICE_SIZE                0x01000000
#define        STM32EXTLOADER_DEVICE_SECTOR_NUMBERS      0x00001000
#define        STM32EXTLOADER_DEVICE_SECTOR_SIZE         0x00001000
#define        STM32EXTLOADER_DEVICE_PAGE_SIZE           0x100
#define        STM32EXTLOADER_DEVICE_INITIAL_CONTENT     0xFF
#define        STM32EXTLOADER_DEVICE_PAGE_TIMEOUT        10000
#define        STM32EXTLOADER_DEVICE_SECTOR_TIMEOUT      6000
#elif USE_100ASK_SDRAM
#define        STM32EXTLOADER_DEVICE_MEMORY_ID           EXTMEMORY_1
#define        STM32EXTLOADER_DEVICE_NAME                "DshanMCU_H7R_SDRAM_Memory_Loader"
#define        STM32EXTLOADER_DEVICE_TYPE                SDRAM
#define        STM32EXTLOADER_DEVICE_ADDR                0xC1000000
#define        STM32EXTLOADER_DEVICE_SIZE                0x00800000
#define        STM32EXTLOADER_DEVICE_SECTOR_NUMBERS      0x00000080
#define        STM32EXTLOADER_DEVICE_SECTOR_SIZE         0x00010000
#define        STM32EXTLOADER_DEVICE_PAGE_SIZE           0x100
#define        STM32EXTLOADER_DEVICE_INITIAL_CONTENT     0xFF
#define        STM32EXTLOADER_DEVICE_PAGE_TIMEOUT        10000
#define        STM32EXTLOADER_DEVICE_SECTOR_TIMEOUT      6000
#endif
 */
/* USER CODE END Header */

#ifndef __EXTMEMLOADER_CONF_H_
#define __EXTMEMLOADER_CONF_H_

#include "extmemloader_init.h"
#include "stm32_extmem_conf.h"

#if USE_100ASK_SPI_FLASH
#define        STM32EXTLOADER_DEVICE_MEMORY_ID           EXTMEMORY_1
#define        STM32EXTLOADER_DEVICE_NAME                "DshanMCU_H7R_SPI_FLASH_Memory_Loader"
#define        STM32EXTLOADER_DEVICE_TYPE                SPI_FLASH
#define        STM32EXTLOADER_DEVICE_ADDR                0x00000000
#define        STM32EXTLOADER_DEVICE_SIZE                0x01000000
#define        STM32EXTLOADER_DEVICE_SECTOR_NUMBERS      0x00001000
#define        STM32EXTLOADER_DEVICE_SECTOR_SIZE         0x00001000
#define        STM32EXTLOADER_DEVICE_PAGE_SIZE           0x100
#define        STM32EXTLOADER_DEVICE_INITIAL_CONTENT     0xFF
#define        STM32EXTLOADER_DEVICE_PAGE_TIMEOUT        10000
#define        STM32EXTLOADER_DEVICE_SECTOR_TIMEOUT      6000
#elif USE_100ASK_SDRAM
#define        STM32EXTLOADER_DEVICE_MEMORY_ID           EXTMEMORY_1
#define        STM32EXTLOADER_DEVICE_NAME                "DshanMCU_H7R_SDRAM_Memory_Loader"
#define        STM32EXTLOADER_DEVICE_TYPE                SDRAM
#define        STM32EXTLOADER_DEVICE_ADDR                0xC1000000
#define        STM32EXTLOADER_DEVICE_SIZE                0x00800000
#define        STM32EXTLOADER_DEVICE_SECTOR_NUMBERS      0x00000080
#define        STM32EXTLOADER_DEVICE_SECTOR_SIZE         0x00010000
#define        STM32EXTLOADER_DEVICE_PAGE_SIZE           0x100
#define        STM32EXTLOADER_DEVICE_INITIAL_CONTENT     0xFF
#define        STM32EXTLOADER_DEVICE_PAGE_TIMEOUT        10000
#define        STM32EXTLOADER_DEVICE_SECTOR_TIMEOUT      6000
#endif

#endif /* __EXTMEMLOADER_CONF_H_ */
