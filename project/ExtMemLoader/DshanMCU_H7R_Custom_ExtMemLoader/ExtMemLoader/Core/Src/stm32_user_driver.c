/**
  ******************************************************************************
  * @file    stm32_user_driver.c
  * @author  MCD Application Team
  * @brief   This file includes a driver for user support
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_extmem.h"
#include "stm32_extmem_conf.h"
#if EXTMEM_DRIVER_USER == 1
#include "stm32_user_driver_api.h"
#include "stm32_user_driver_type.h"


#if USE_100ASK_SPI_FLASH
#include "X25Qx.h"
#elif USE_100ASK_SDRAM
#include "sdram.h"
//#include <string.h>
#endif


#define IMAGE_HEADER_SIZE	((uint32_t)0x00001000)
#define IH_NMLEN 	120
typedef struct image_header {
	uint32_t ih_magic;  			/* Image Header Magic Number */
	uint32_t ih_hcrc;				/* Image Header CRC Checksum */
	uint32_t ih_time;				/* Image Creation Timerstamp */
	uint32_t ih_size;				/* Image Data Size */
	uint32_t ih_load;				/* Data Load Address */
	uint32_t ih_ep;					/* Entry Point Address */
	uint32_t ih_dcrc;				/* Image Data CRC Checksum */
	uint8_t  ih_os;					/* Operating System */
	uint8_t  ih_arch;				/* CPU architecture */
	uint8_t  ih_type;				/* Image Type */
	uint8_t  ih_comp;				/* Compression Type */
	uint8_t  ih_name[IH_NMLEN];		/* Image Nmae */
} image_header_t;

/** @defgroup USER USER driver
  * @ingroup EXTMEM_DRIVER
  * @{
  */

/* Private Macro ------------------------------------------------------------*/
/** @defgroup USER_Private_Macro Private Macro
  * @{
  */

/**
  * @}
  */
/* Private typedefs ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup USER_Exported_Functions Exported Functions
  * @{
  */

EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_Init(uint32_t MemoryId,
                                                         EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject)
{
  EXTMEM_DRIVER_USER_StatusTypeDef retr = EXTMEM_DRIVER_USER_NOTSUPPORTED;
  UserObject->MemID = MemoryId;     /* Keep the memory id, could be used to control more than one user memory */
  UserObject->PtrUserDriver = NULL; /* could be used to link data with the memory id */

  //image_header.ih_size = 0;

  retr = EXTMEM_DRIVER_USER_OK;
  return retr;
}

EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_DeInit(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject)
{
  EXTMEM_DRIVER_USER_StatusTypeDef retr = EXTMEM_DRIVER_USER_NOTSUPPORTED;
  (void)UserObject;

  retr = EXTMEM_DRIVER_USER_OK;
  return retr;
}

EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_Read(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject,
                                                         uint32_t Address, uint8_t* Data, uint32_t Size)
{
  EXTMEM_DRIVER_USER_StatusTypeDef retr = EXTMEM_DRIVER_USER_NOTSUPPORTED;
  (void)*UserObject;
  (void)Address;
  (void)Data;
  (void)Size;

#if USE_100ASK_SPI_FLASH
  X25Qx_SPIFLASH_ReadBuffer(Data, Address, Size);
#elif USE_100ASK_SDRAM
  //memcpy(Data, (uint32_t*) (APP_SDRAM_BANK_ADDR), Size);
  //memcpy(Data, Address, Size);

  //SDRAM_ReadBuffer((uint32_t *)Data, (Address - SDRAM_BANK_ADDR), Size/4);
  SDRAM_ReadBuffer((uint32_t *)Data, (Address), Size/4);
#endif

  retr = EXTMEM_DRIVER_USER_OK;
  return retr;
}

EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_Write(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject,
                                                          uint32_t Address, const uint8_t* Data, uint32_t Size)
{
  EXTMEM_DRIVER_USER_StatusTypeDef retr = EXTMEM_DRIVER_USER_NOTSUPPORTED;
  (void)*UserObject;
  //(void)Address;
  //(void)Data;
  //(void)Size;

#if USE_100ASK_SPI_FLASH
  image_header_t image_header = {0};

  X25Qx_SPIFLASH_ReadBuffer((uint8_t *)&image_header, (uint32_t)(0x00000000), (uint32_t)(sizeof(image_header)));
  image_header.ih_size += Size;
  X25Qx_SPIFLASH_EraseSector(0x0);
  X25Qx_SPIFLASH_WriteBuffer((uint8_t *)&image_header, ((uint32_t)0x00000000), (uint32_t)(sizeof(image_header)));

  X25Qx_SPIFLASH_WriteBuffer((uint8_t *)Data, Address+IMAGE_HEADER_SIZE, Size);
#elif USE_100ASK_SDRAM
  //memcpy((uint32_t*) (APP_SDRAM_BANK_ADDR), Data, Size);
  //memcpy(Address, Data, Size);
  //SDRAM_WriteBuffer((uint32_t *)Data, (Address - SDRAM_BANK_ADDR), Size/4);
  SDRAM_WriteBuffer((uint32_t *)Data, (uint32_t)Address, (uint32_t)(Size/4));
#endif

  retr = EXTMEM_DRIVER_USER_OK;
  return retr;
}

EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_EraseSector(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject,
                                                                uint32_t Address, uint32_t Size)
{
  EXTMEM_DRIVER_USER_StatusTypeDef retr = EXTMEM_DRIVER_USER_NOTSUPPORTED;
  (void)*UserObject;
  (void)Address;
  (void)Size;

#if USE_100ASK_SPI_FLASH
  X25Qx_SPIFLASH_EraseSector(0x0);
  X25Qx_SPIFLASH_EraseSector(Address+IMAGE_HEADER_SIZE);
#elif USE_100ASK_SDRAM
  //memset((uint32_t*) (APP_SDRAM_BANK_ADDR), 0xFF, Size);
  //memset((__IO uint32_t*)Address, 0x00, Size);

  uint32_t uwIndex = 0;
  for (uwIndex = 0; uwIndex < Size;  uwIndex++)
	{
	  *(__IO uint32_t*) (SDRAM_BANK_ADDR + 4*uwIndex) = 0x00000000;
	}
#endif

  retr = EXTMEM_DRIVER_USER_OK;
  return retr;
}

EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_MassErase(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject)
{
  EXTMEM_DRIVER_USER_StatusTypeDef retr = EXTMEM_DRIVER_USER_NOTSUPPORTED;
  (void)*UserObject;

#if USE_100ASK_SPI_FLASH
  X25Qx_SPIFLASH_EraseChip();
#elif USE_100ASK_SDRAM
  //memset((uint32_t*) (APP_SDRAM_BANK_ADDR), 0x00, APP_SDRAM_BANK_SIZE);

  uint32_t uwIndex = 0;
  for (uwIndex = 0; uwIndex < 0x00800000;  uwIndex++)
  	{
  	  *(__IO uint32_t*) (SDRAM_BANK_ADDR + 4*uwIndex) = 0x00000000;
  	}
#endif

  retr = EXTMEM_DRIVER_USER_OK;
  return retr;
}

EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_Enable_MemoryMappedMode(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject)
{
  EXTMEM_DRIVER_USER_StatusTypeDef retr = EXTMEM_DRIVER_USER_NOTSUPPORTED;
  (void)*UserObject;

  retr = EXTMEM_DRIVER_USER_OK;
  return retr;
}

EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_Disable_MemoryMappedMode(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject)
{
  EXTMEM_DRIVER_USER_StatusTypeDef retr = EXTMEM_DRIVER_USER_NOTSUPPORTED;
  (void)*UserObject;

  retr = EXTMEM_DRIVER_USER_OK;
  return retr;
}

EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_GetMapAddress(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject, uint32_t* BaseAddress)
{
  EXTMEM_DRIVER_USER_StatusTypeDef retr = EXTMEM_DRIVER_USER_NOTSUPPORTED;
  (void)*UserObject;
  (void)BaseAddress;

  retr = EXTMEM_DRIVER_USER_OK;
  return retr;
}

EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_GetInfo(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject, EXTMEM_USER_MemInfoTypeDef* MemInfo)
{
  EXTMEM_DRIVER_USER_StatusTypeDef retr = EXTMEM_DRIVER_USER_NOTSUPPORTED;
  (void)*UserObject;
  (void)MemInfo;

  retr = EXTMEM_DRIVER_USER_OK;
  return retr;
}

/**
  * @}
  */

/** @addtogroup USER_Private_Functions
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* EXTMEM_DRIVER_USER == 1 */
