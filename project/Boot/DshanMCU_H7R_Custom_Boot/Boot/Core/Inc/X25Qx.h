/*
 * X25Qx.h
 *
 *  Created on: Jun 18, 2024
 *      Author: zhouyuebiao
 */

#ifndef INC_X25Qx_H_
#define INC_X25Qx_H_

/* Includes ------------------------------------------------------------------*/

#include "stm32h7rsxx_hal.h"
#include "spi.h"

/* Important! */
/* Choose the chip */
#define USE_W25Q_128J	1
#define USE_GD25Q_80E	1
#define USE_GD25Q_256E	1

#if USE_W25Q_128J
#define X25QxCSIGDeviceID						0x17
#define X25QxCSIGManufactureID					0xef17
#define X25QxCSIGIdentificationID				0xef4018
#endif

#if USE_GD25Q_80E
#define GD25Q_80E_DeviceID						0x13
#define GD25Q_80E_ManufactureID					0xC813
#define GD25Q_80E_IdentificationID				0xC84014
#endif

#if USE_GD25Q_256E
#define GD25Q_256E_DeviceID						0x18
#define GD25Q_256E_ManufactureID				0xC818
#define GD25Q_256E_IdentificationID				0xC84019
#endif


#define X25Qx_BASE_ADDR							0x000000U
#define X25Qx_CHIP_BYTE_SIZE					0x100000U													// 1 M
#define X25Qx_BLOCK_BYTE_SIZE					0x010000U													//64 K
#define X25Qx_SECTOR_BYTE_SIZE					0x001000U													// 4 K
#define X25Qx_PAGE_BYTE_SIZE					0x000100U													//256Byte

#define X25Qx_BLOCK_ADDRESS0					0x000000U
#define X25Qx_BLOCK_ADDRESS1					0x010000U
#define X25Qx_BLOCK_ADDRESS2					0x020000U
#define X25Qx_BLOCK_ADDRESS3					0x030000U
#define X25Qx_BLOCK_ADDRESS4					0x040000U
#define X25Qx_BLOCK_ADDRESS5					0x050000U
#define X25Qx_BLOCK_ADDRESS6					0x060000U
#define X25Qx_BLOCK_ADDRESS7					0x070000U
#define X25Qx_BLOCK_ADDRESS8					0x080000U
#define X25Qx_BLOCK_ADDRESS9					0x090000U
#define X25Qx_BLOCK_ADDRESS10					0x0A0000U
#define X25Qx_BLOCK_ADDRESS11					0x0B0000U
#define X25Qx_BLOCK_ADDRESS12					0x0C0000U
#define X25Qx_BLOCK_ADDRESS13					0x0D0000U
#define X25Qx_BLOCK_ADDRESS14					0x0E0000U
#define X25Qx_BLOCK_ADDRESS15					0x0F0000U

#define X25Qx_SECTOR_ADDRESS(nSector)			(X25Qx_BASE_ADDR + (X25Qx_SECTOR_BYTE_SIZE * nSector))
#define X25Qx_PAGE_ADDRESS(nPage)				(X25Qx_BASE_ADDR + (X25Qx_PAGE_BYTE_SIZE * nPage))

#define X25Qx_SECTOR_NUM						256
#define X25Qx_PAGE_NUM							4096

#define APP_PACKSLICE_NUM						300														//升级APP分片最大分片数

/* APP1 FLASH ADDRESS TABLE */
#define APP1_BASE_ADDR							0x000000U
#define APP1_BYTE_SIZE							0x040000U
#define APP1_INFORMATION_ADDR					APP1_BASE_ADDR
#define APP1_INFORMATION_SIZE					0x1000
#define APP1_DATA_ADDR							APP1_BASE_ADDR + APP1_INFORMATION_SIZE
#define APP1_DATA_SIZE							APP1_BYTE_SIZE - APP1_INFORMATION_SIZE
#define APP1_INFO_UPGRADE_STATUS_OFFSET			APP1_INFORMATION_ADDR
#define APP1_INFO_UPGRADE_STATUS_LENGTH			1														//升级标志 高4位0x5(0101)有升级包 低4位0x5(0101)可升级
#define APP1_INFO_UPGRADE_BASEADDR_OFFSET		APP1_INFO_UPGRADE_STATUS_OFFSET + APP1_INFO_UPGRADE_STATUS_LENGTH
#define APP1_INFO_UPGRADE_BASEADDR_LENGTH		4														//升级APP起始地址
#define APP1_INFO_UPGRADE_BLOCKNUM_OFFSET		APP1_INFO_UPGRADE_BASEADDR_OFFSET + APP1_INFO_UPGRADE_BASEADDR_LENGTH
#define APP1_INFO_UPGRADE_BLOCKNUM_LENGTH		2														//升级APP存放块数
#define APP1_INFO_UPGRADE_BLOCKLEN_OFFSET		APP1_INFO_UPGRADE_BLOCKNUM_OFFSET + APP1_INFO_UPGRADE_BLOCKNUM_LENGTH
#define APP1_INFO_UPGRADE_BLOCKLEN_LENGTH		2														//升级APP块长度
#define APP1_INFO_UPGRADE_DATALEN_OFFSET		APP1_INFO_UPGRADE_BLOCKLEN_OFFSET + APP1_INFO_UPGRADE_BLOCKLEN_LENGTH
#define APP1_INFO_UPGRADE_DATALEN_LENGTH		2														//升级APP块有效长度
#define APP1_INFO_UPGRADE_INDEX_OFFSET			APP1_INFO_UPGRADE_DATALEN_OFFSET + APP1_INFO_UPGRADE_DATALEN_LENGTH
#define APP1_INFO_UPGRADE_INDEX_LENGTH			4														//升级APP序号
#define APP1_INFO_UPGRADE_SOFTVER_OFFSET		APP1_INFO_UPGRADE_INDEX_OFFSET + APP1_INFO_UPGRADE_INDEX_LENGTH
#define APP1_INFO_UPGRADE_SOFTVER_LENGTH		4														//升级包版本号 高2字节主版本号 低2字节从版本号
#define APP1_INFO_DOWNLOAD_TIME_OFFSET			APP1_INFO_UPGRADE_SOFTVER_OFFSET + APP1_INFO_UPGRADE_SOFTVER_LENGTH
#define APP1_INFO_DOWNLOAD_TIME_LENGTH			4														//升级包下载时间
#define APP1_DATA_CHECK_CODE_OFFSET				APP1_INFO_DOWNLOAD_TIME_OFFSET + APP1_INFO_DOWNLOAD_TIME_LENGTH
#define APP1_DATA_CHECK_CODE_LENGTH				4														//升级包校验码
#define APP1_PACKSLICE_STATUS_OFFSET			APP1_DATA_CHECK_CODE_OFFSET + APP1_DATA_CHECK_CODE_LENGTH
#define APP1_PACKSLICE_STATUS_LENGTH			APP_PACKSLICE_NUM											//升级包分片下载状态(0x00有 0xFF无)
/* END APP1 ADDRESS TABLE */

/* APP2 FLASH ADDRESS TABLE */
#define APP2_BASE_ADDR							0x040000U
#define APP2_BYTE_SIZE							0x040000U
#define APP2_INFORMATION_ADDR					APP2_BASE_ADDR
#define APP2_INFORMATION_SIZE					0x1000
#define APP2_DATA_ADDR							APP2_BASE_ADDR + APP2_INFORMATION_SIZE
#define APP2_DATA_SIZE							APP2_BYTE_SIZE - APP2_INFORMATION_SIZE
#define APP2_INFO_UPGRADE_STATUS_OFFSET			APP2_INFORMATION_ADDR
#define APP2_INFO_UPGRADE_STATUS_LENGTH			1														//升级标志 高4位0x5(0101)有升级包 低4位0x5(0101)可升级
#define APP2_INFO_UPGRADE_BASEADDR_OFFSET		APP2_INFO_UPGRADE_STATUS_OFFSET + APP2_INFO_UPGRADE_STATUS_LENGTH
#define APP2_INFO_UPGRADE_BASEADDR_LENGTH		4														//升级APP起始地址
#define APP2_INFO_UPGRADE_BLOCKNUM_OFFSET		APP2_INFO_UPGRADE_BASEADDR_OFFSET + APP2_INFO_UPGRADE_BASEADDR_LENGTH
#define APP2_INFO_UPGRADE_BLOCKNUM_LENGTH		2														//升级APP存放块数
#define APP2_INFO_UPGRADE_BLOCKLEN_OFFSET		APP2_INFO_UPGRADE_BLOCKNUM_OFFSET + APP2_INFO_UPGRADE_BLOCKNUM_LENGTH
#define APP2_INFO_UPGRADE_BLOCKLEN_LENGTH		2														//升级APP块长度
#define APP2_INFO_UPGRADE_DATALEN_OFFSET		APP2_INFO_UPGRADE_BLOCKLEN_OFFSET + APP2_INFO_UPGRADE_BLOCKLEN_LENGTH
#define APP2_INFO_UPGRADE_DATALEN_LENGTH		2														//升级APP块有效长度
#define APP2_INFO_UPGRADE_INDEX_OFFSET			APP2_INFO_UPGRADE_DATALEN_OFFSET + APP2_INFO_UPGRADE_DATALEN_LENGTH
#define APP2_INFO_UPGRADE_INDEX_LENGTH			4														//升级APP序号
#define APP2_INFO_UPGRADE_SOFTVER_OFFSET		APP2_INFO_UPGRADE_INDEX_OFFSET + APP2_INFO_UPGRADE_INDEX_LENGTH
#define APP2_INFO_UPGRADE_SOFTVER_LENGTH		4														//升级包版本号 高2字节主版本号 低2字节从版本号
#define APP2_INFO_DOWNLOAD_TIME_OFFSET			APP2_INFO_UPGRADE_SOFTVER_OFFSET + APP2_INFO_UPGRADE_SOFTVER_LENGTH
#define APP2_INFO_DOWNLOAD_TIME_LENGTH			4														//升级包下载时间
#define APP2_DATA_CHECK_CODE_OFFSET				APP2_INFO_DOWNLOAD_TIME_OFFSET + APP2_INFO_DOWNLOAD_TIME_LENGTH
#define APP2_DATA_CHECK_CODE_LENGTH				4														//升级包校验码
#define APP2_PACKSLICE_STATUS_OFFSET			APP2_DATA_CHECK_CODE_OFFSET + APP2_DATA_CHECK_CODE_LENGTH
#define APP2_PACKSLICE_STATUS_LENGTH			APP_PACKSLICE_NUM											//升级包分片下载状态(0x00有 0xFF无)
/* END APP2 ADDRESS TABLE */

/* Definition for SPIx clock resources */
#define X25Qx_FLASH_SPIx							SPI1
#define X25Qx_FLASH_SPIx_RCC_CLK_ENABLE()			__HAL_RCC_SPI1_CLK_ENABLE()
#define X25Qx_FLASH_SPIx_RCC_CLK_DISABLE()			__HAL_RCC_SPI1_CLK_DISABLE()

#define X25Qx_FLASH_SPIx_FORCE_RESET()				__HAL_RCC_SPI1_FORCE_RESET()
#define X25Qx_FLASH_SPIx_RELEASE_RESET()			__HAL_RCC_SPI1_RELEASE_RESET()

/* Definition for SPIx GPIO resources */
#define X25Qx_FLASH_SPIx_NSS_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define X25Qx_FLASH_SPIx_NSS_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()
#define X25Qx_FLASH_SPIx_SCK_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define X25Qx_FLASH_SPIx_SCK_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOA_CLK_DISABLE()
#define X25Qx_FLASH_SPIx_MOSI_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define X25Qx_FLASH_SPIx_MOSI_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOA_CLK_DISABLE()
#define X25Qx_FLASH_SPIx_MISO_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define X25Qx_FLASH_SPIx_MISO_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOA_CLK_DISABLE()

/* Definition for SPIx Pins */
#define X25Qx_FLASH_SPIx_NSS_GPIO_PORT				GPIOF
#define X25Qx_FLASH_SPIx_NSS_PIN					GPIO_PIN_13
#define X25Qx_FLASH_SPIx_SCK_GPIO_PORT				GPIOF
#define X25Qx_FLASH_SPIx_SCK_PIN					GPIO_PIN_15
#define X25Qx_FLASH_SPIx_SCK_AF						GPIO_AF5_SPI1
#define X25Qx_FLASH_SPIx_MOSI_GPIO_PORT				GPIOF
#define X25Qx_FLASH_SPIx_MOSI_PIN					GPIO_PIN_14
#define X25Qx_FLASH_SPIx_MOSI_AF					GPIO_AF5_SPI1
#define X25Qx_FLASH_SPIx_MISO_GPIO_PORT				GPIOF
#define X25Qx_FLASH_SPIx_MISO_PIN					GPIO_PIN_12
#define X25Qx_FLASH_SPIx_MISO_AF					GPIO_AF5_SPI1

#define X25Qx_FLASH_SPIx_NSS_ENABLE()				HAL_GPIO_WritePin(X25Qx_FLASH_SPIx_NSS_GPIO_PORT, X25Qx_FLASH_SPIx_NSS_PIN, GPIO_PIN_RESET)
#define X25Qx_FLASH_SPIx_NSS_DISABLE()				HAL_GPIO_WritePin(X25Qx_FLASH_SPIx_NSS_GPIO_PORT, X25Qx_FLASH_SPIx_NSS_PIN, GPIO_PIN_SET)

#define X25Qx_Dummy_Byte							0xFF

/* X25QxCSIG 指令表 */
#define X25Qx_WriteEnable							0x06
#define X25Qx_WriteDisable							0x04

#define X25Qx_ReadStatusReg1						0x05
#define X25Qx_ReadStatusReg2						0x35
#define X25Qx_WriteStatusReg						0x01

#define X25Qx_ReadData								0x03
#define X25Qx_FastReadData							0x0B
#define X25Qx_FastReadDual							0x3B
#define X25Qx_PageProgram							0x02

#define X25Qx_SectorErase							0x20
#define X25Qx_BlockErase							0xD8
#define X25Qx_ChipErase								0xC7

#define X25Qx_PowerDown								0xB9
#define X25Qx_ReleasePowerDown						0xAB
#define X25Qx_DeviceID								0xAB
#define X25Qx_ManufactDeviceID						0x90
#define X25Qx_JedecDeviceID							0x9F
/* X25QxCSIG End Command */

typedef enum
{
	X25QxCSIG_OK		= 0x00,
	X25QxCSIG_ERROR		= 0x01
}X25Qx_StatusTypeDef;


void X25Qx_SPIFLASH_Init(void);														//X25Q SPIFLASH 初始化
X25Qx_StatusTypeDef X25Qx_SPIFLASH_Get_Status(void);										//X25Q SPIFLASH 状态

uint8_t X25Qx_SPI_FLASH_ReadByte(void);														//SPI FLASH 读取一个字节数据
uint8_t X25Qx_SPI_FLASH_SendByte(uint8_t byte);													//SPI FLASH 发送一个字节数据

uint32_t X25Qx_SPIFLASH_ReadDeviceID(void);													//X25Q SPIFLASH 读取设备ID
uint32_t X25Qx_SPIFLASH_ReadManufactureID(void);												//X25Q SPIFLASH 读取厂商ID
uint32_t X25Qx_SPIFLASH_ReadIdentificationID(void);											//X25Q SPIFLASH 读取型号ID

void X25Qx_SPIFLASH_WriteEnable(void);													//X25Q SPIFLASH 写使能
void X25Qx_SPIFLASH_WriteDisable(void);													//X25Q SPIFLASH 写禁止

uint8_t X25Qx_SPIFLASH_ReadStatusRegister(uint8_t statusRegister);									//X25Q SPIFLASH 读状态寄存器
void X25Qx_SPIFLASH_WriteStatusRegister(uint8_t srLow, uint8_t srHigh);								//X25Q SPIFLASH 写状态寄存器

void X25Qx_SPIFLASH_WaitForBusy(void);													//X25Q SPIFLASH 等待设备空闲
void X25Qx_SPIFLASH_PowerDown(void);													//X25Q SPIFLASH 进入掉电模式
void X25Qx_SPIFLASH_WakeUp(void);														//X25Q SPIFLASH 唤醒

void X25Qx_SPIFLASH_EraseChip(void);													//X25Q SPIFLASH 擦除Chip
void X25Qx_SPIFLASH_EraseBlock(uint32_t BlockAddr);											//X25Q SPIFLASH 擦除Block
void X25Qx_SPIFLASH_EraseSector(uint32_t SectorAddr);											//X25Q SPIFLASH 擦除Sector

void X25Qx_SPIFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);					//X25Q SPIFLASH 读取SPI FLASH数据
void X25Qx_SPIFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);					//X25Q SPIFLASH 写入SPI FLASH数据Page
void X25Qx_SPIFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);				//X25Q SPIFLASH 写入SPI FLASH数据

unsigned char X25Qx_SPIFLASH_GetByte(uint32_t ReadAddr);										//X25Q SPIFLASH 读取1个Byte
unsigned short X25Qx_SPIFLASH_GetHalfWord(uint32_t ReadAddr);									//X25Q SPIFLASH 读取2个Byte
unsigned int X25Qx_SPIFLASH_GetWord(uint32_t ReadAddr);										//X25Q SPIFLASH 读取4个Byte

void X25Qx_SPIFLASH_SetByte(uint32_t WriteAddr, unsigned char val);								//X25Q SPIFLASH 写入1个Byte
void X25Qx_SPIFLASH_SetHalfWord(uint32_t WriteAddr, unsigned short val);							//X25Q SPIFLASH 写入2个Byte
void X25Qx_SPIFLASH_SetWord(uint32_t WriteAddr, unsigned int val);								//X25Q SPIFLASH 写入4个Byte

unsigned int X25Qx_SPIFLASH_GetNumofByte(uint32_t ReadAddr, uint16_t AllNum, uint8_t ByteVal);					//X25Q SPIFLASH 读取指定地址中指定字节中有该值的个数

#endif /* __HAL_SPI_FLASH_H */
