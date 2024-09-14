/**
  *********************************************************************************************************
  * @file    X25Qx.c
  * @author  www.100ask.net
  * @version V1.0
  * @date    2024-06-18
  * @brief   SPI FLASH X25Qx Device
  *		   SPI FLASH X25Qx Device
  *********************************************************************************************************
  * @attention
  *		   SPI5_MISO  : PF12
  *		   SPI5_NSS  : PF13
  *		   SPI5_MOSI : PF14
  *		   SPI5_SCK : PF15
  *********************************************************************************************************
  */

#include "X25Qx.h"


SPI_HandleTypeDef *X25Qx_SPIFLASH_Handler = &hspi5;

X25Qx_StatusTypeDef X25QStatus = X25QxCSIG_OK;

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_Init(void)
 @Description			X25Qx_SPIFLASH_Init			: X25Q SPIFLASH 初始化
 @Input				void
 @Return				void
**********************************************************************************************************/
void X25Qx_SPIFLASH_Init(void)
{
	uint32_t ReadDeviceID;
	uint32_t ReadManufactureID;
	uint32_t ReadIdentificationID;

	X25Qx_SPIFLASH_WakeUp();

	ReadDeviceID = X25Qx_SPIFLASH_ReadDeviceID();
	ReadManufactureID = X25Qx_SPIFLASH_ReadManufactureID();
	ReadIdentificationID = X25Qx_SPIFLASH_ReadIdentificationID();
	if((ReadDeviceID != X25QxCSIGDeviceID) ||\
	   (ReadManufactureID != X25QxCSIGManufactureID) ||\
	   (ReadIdentificationID != X25QxCSIGIdentificationID)) {
		X25QStatus = X25QxCSIG_ERROR;
	}
}

/**********************************************************************************************************
 @Function			X25Qx_StatusTypeDef X25Qx_SPIFLASH_Get_Status(void)
 @Description			X25Qx_SPIFLASH_Get_Status	: X25Q SPIFLASH 状态
 @Input				void
 @Return				X25Qx_StatusTypeDef
**********************************************************************************************************/
X25Qx_StatusTypeDef X25Qx_SPIFLASH_Get_Status(void)
{
#if	USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	return X25QStatus;
#else
	return X25QxCSIG_ERROR;
#endif
}

/**********************************************************************************************************
 @Function			uint8_t X25Qx_SPI_FLASH_ReadByte(void)
 @Description			X25Qx_SPI_FLASH_ReadByte		: SPI FLASH 读取一个字节数据
 @Input				void
 @Return				readByte					: 读取到的数据
**********************************************************************************************************/
uint8_t X25Qx_SPI_FLASH_ReadByte(void)
{
	uint8_t readByte, sendByte = X25Qx_Dummy_Byte;

	if (HAL_SPI_TransmitReceive(X25Qx_SPIFLASH_Handler, &sendByte, &readByte, 1, 500) != HAL_OK) {
		readByte = X25Qx_Dummy_Byte;
	}
	return readByte;
}

/**********************************************************************************************************
 @Function			uint8_t X25Qx_SPI_FLASH_SendByte(uint8_t byte)
 @Description			X25Qx_SPI_FLASH_SendByte		: SPI FLASH 发送一个字节数据
 @Input				byte						: 发送的数据
 @Return				void
**********************************************************************************************************/
uint8_t X25Qx_SPI_FLASH_SendByte(uint8_t byte)
{
	uint8_t readByte = 0x00, sendByte = byte;

	if (HAL_SPI_TransmitReceive(X25Qx_SPIFLASH_Handler, &sendByte, &readByte, 1, 500) != HAL_OK) {
		readByte = X25Qx_Dummy_Byte;
	}
	return readByte;
}

/**********************************************************************************************************
 @Function			uint32_t X25Qx_SPIFLASH_ReadDeviceID(void)
 @Description			X25Qx_SPIFLASH_ReadDeviceID			: X25Q SPIFLASH 读取设备ID
 @Input				void
 @Return				设备ID
**********************************************************************************************************/
uint32_t X25Qx_SPIFLASH_ReadDeviceID(void)
{
	uint32_t deviceID = 0;

	/* 选择SPI FLASH, NSS使能 */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	X25Qx_SPI_FLASH_SendByte(X25Qx_DeviceID);
	X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte);
	X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte);
	X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte);

	deviceID = X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte);

	/* 禁用SPI FLASH, NSS失能 */
	X25Qx_FLASH_SPIx_NSS_DISABLE();

	return deviceID;
}

/**********************************************************************************************************
 @Function			uint32_t X25Qx_SPIFLASH_ReadManufactureID(void)
 @Description			X25Qx_SPIFLASH_ReadManufactureID		: X25Q SPIFLASH 读取厂商ID
 @Input				void
 @Return				厂商ID
**********************************************************************************************************/
uint32_t X25Qx_SPIFLASH_ReadManufactureID(void)
{
	uint32_t manufactureID = 0;

	/* 选择SPI FLASH, NSS使能 */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	X25Qx_SPI_FLASH_SendByte(X25Qx_ManufactDeviceID);
	X25Qx_SPI_FLASH_SendByte(0x00);
	X25Qx_SPI_FLASH_SendByte(0x00);
	X25Qx_SPI_FLASH_SendByte(0x00);
	manufactureID |= X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte) << 8;
	manufactureID |= X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte);

	/* 禁用SPI FLASH, NSS失能 */
	X25Qx_FLASH_SPIx_NSS_DISABLE();

	return manufactureID;
}

/**********************************************************************************************************
 @Function			uint32_t X25Qx_SPIFLASH_ReadIdentificationID(void)
 @Description			X25Qx_SPIFLASH_ReadIdentificationID	: X25Q SPIFLASH 读取型号ID
 @Input				void
 @Return				型号ID
**********************************************************************************************************/
uint32_t X25Qx_SPIFLASH_ReadIdentificationID(void)
{
	uint32_t identificationID = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

	/* 选择SPI FLASH, NSS使能 */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	X25Qx_SPI_FLASH_SendByte(X25Qx_JedecDeviceID);
	Temp0 = X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte);
	Temp1 = X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte);
	Temp2 = X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte);

	/* 禁用SPI FLASH, NSS失能 */
	X25Qx_FLASH_SPIx_NSS_DISABLE();

	identificationID = (Temp0 << 16) | (Temp1 << 8) | Temp2;

	return identificationID;
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_WriteEnable(void)
 @Description			X25Qx_SPIFLASH_WriteEnable	: X25Q SPIFLASH 写使能
 @Input				void
 @Return				void
 @attention			WEL置位
**********************************************************************************************************/
void X25Qx_SPIFLASH_WriteEnable(void)
{
	/* 选择SPI FLASH, NSS使能 */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	X25Qx_SPI_FLASH_SendByte(X25Qx_WriteEnable);

	/* 禁用SPI FLASH, NSS失能 */
	X25Qx_FLASH_SPIx_NSS_DISABLE();
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_WriteDisable(void)
 @Description			X25Qx_SPIFLASH_WriteDisable	: X25Q SPIFLASH 写禁止
 @Input				void
 @Return				void
 @attention			WEL清零
**********************************************************************************************************/
void X25Qx_SPIFLASH_WriteDisable(void)
{
	/* 选择SPI FLASH, NSS使能 */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	X25Qx_SPI_FLASH_SendByte(X25Qx_WriteDisable);

	/* 禁用SPI FLASH, NSS失能 */
	X25Qx_FLASH_SPIx_NSS_DISABLE();
}

/**********************************************************************************************************
 @Function			uint8_t X25Qx_SPIFLASH_ReadStatusRegister(uint8_t statusRegister)
 @Description			X25Qx_SPIFLASH_ReadStatusRegister	: X25Q SPIFLASH 读状态寄存器
 @Input				状态寄存器地址
 @Return				状态寄存器值
**********************************************************************************************************/
uint8_t X25Qx_SPIFLASH_ReadStatusRegister(uint8_t statusRegister)
{
	uint8_t readByte = 0;

	/* 选择SPI FLASH, NSS使能 */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	X25Qx_SPI_FLASH_SendByte(statusRegister);
	readByte = X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte);

	/* 禁用SPI FLASH, NSS失能 */
	X25Qx_FLASH_SPIx_NSS_DISABLE();

	return readByte;
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_WriteStatusRegister(uint8_t srLow, uint8_t srHigh)
 @Description			X25Qx_SPIFLASH_WriteStatusRegister	: X25Q SPIFLASH 写状态寄存器
 @Input				srLow						: 状态寄存器低字节
					srHigh						: 状态寄存器高字节
 @Return				void
**********************************************************************************************************/
void X25Qx_SPIFLASH_WriteStatusRegister(uint8_t srLow, uint8_t srHigh)
{
	/* 选择SPI FLASH, NSS使能 */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	X25Qx_SPI_FLASH_SendByte(X25Qx_WriteStatusReg);
	X25Qx_SPI_FLASH_SendByte(srLow);
	X25Qx_SPI_FLASH_SendByte(srHigh);

	/* 禁用SPI FLASH, NSS失能 */
	X25Qx_FLASH_SPIx_NSS_DISABLE();
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_WaitForBusy(void)
 @Description			X25Qx_SPIFLASH_WaitForBusy		: X25Q SPIFLASH 等待设备空闲
 @Input				void
 @Return				void
**********************************************************************************************************/
void X25Qx_SPIFLASH_WaitForBusy(void)
{
	uint8_t flashStatus = 0;

	/* 选择SPI FLASH, NSS使能 */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	/* Send "Read Status Register" instruction */
	X25Qx_SPI_FLASH_SendByte(X25Qx_ReadStatusReg1);

	/* Loop as long as the memory is busy with a write cycle */
	do {
		flashStatus = X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte);
	}
	while ((flashStatus & 0x01) == 0x01);

	/* 禁用SPI FLASH, NSS失能 */
	X25Qx_FLASH_SPIx_NSS_DISABLE();
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_PowerDown(void)
 @Description			X25Qx_SPIFLASH_PowerDown			: X25Q SPIFLASH 进入掉电模式
 @Input				void
 @Return				void
**********************************************************************************************************/
void X25Qx_SPIFLASH_PowerDown(void)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	if (X25QxCSIG_OK != X25Qx_SPIFLASH_Get_Status()) {
		return;
	}

	/* Select the FLASH: Chip Select low */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	/* Send "Power Down" instruction */
	X25Qx_SPI_FLASH_SendByte(X25Qx_PowerDown);

	/* Deselect the FLASH: Chip Select high */
	X25Qx_FLASH_SPIx_NSS_DISABLE();

	/* Wait for TDP */
	HAL_Delay(3);
#endif
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_WakeUp(void)
 @Description			X25Qx_SPIFLASH_WakeUp			: X25Q SPIFLASH 唤醒
 @Input				void
 @Return				void
**********************************************************************************************************/
void X25Qx_SPIFLASH_WakeUp(void)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	if (X25QxCSIG_OK != X25Qx_SPIFLASH_Get_Status()) {
		return;
	}

	/* Select the FLASH: Chip Select low */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	/* Send "Release Power Down" instruction */
	X25Qx_SPI_FLASH_SendByte(X25Qx_ReleasePowerDown);

	/* Deselect the FLASH: Chip Select high */
	X25Qx_FLASH_SPIx_NSS_DISABLE();

	/* Wait for TRES1 */
	HAL_Delay(5);
#endif
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_EraseChip(void)
 @Description			X25Qx_SPIFLASH_EraseChip			: X25Q SPIFLASH 擦除Chip
 @Input				void
 @Return				void
 @attention			800MS
**********************************************************************************************************/
void X25Qx_SPIFLASH_EraseChip(void)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	if (X25QxCSIG_OK != X25Qx_SPIFLASH_Get_Status()) {
		return;
	}

	/* 发送FLASH写使能命令 */
	X25Qx_SPIFLASH_WriteEnable();

	/* 等待FLASH空闲 */
	X25Qx_SPIFLASH_WaitForBusy();

	/* Select the FLASH: Chip Select low */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	/* 发送片擦除命令 */
	X25Qx_SPI_FLASH_SendByte(X25Qx_ChipErase);

	/* Deselect the FLASH: Chip Select high */
	X25Qx_FLASH_SPIx_NSS_DISABLE();

	/* 等待擦除完毕 */
	X25Qx_SPIFLASH_WaitForBusy();
#endif
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_EraseBlock(uint32_t BlockAddr)
 @Description			X25Qx_SPIFLASH_EraseBlock		: X25Q SPIFLASH 擦除Block
 @Input				BlockAddr						: 块地址(0x10000倍数)
 @Return				void
 @attention			X25QxCSIG SPI FLASH 擦除块大小为64KB(65536Byte),即一个块区大小,在写入数据之前要求先擦除空间
					50MS
**********************************************************************************************************/
void X25Qx_SPIFLASH_EraseBlock(uint32_t BlockAddr)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	if (X25QxCSIG_OK != X25Qx_SPIFLASH_Get_Status()) {
		return;
	}

	/* 发送FLASH写使能命令 */
	X25Qx_SPIFLASH_WriteEnable();

	/* 等待FLASH空闲 */
	X25Qx_SPIFLASH_WaitForBusy();

	/* Select the FLASH: Chip Select low */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	/* 发送块区擦除命令 */
	X25Qx_SPI_FLASH_SendByte(X25Qx_BlockErase);

	/* 发送块区擦除地址高位 */
	X25Qx_SPI_FLASH_SendByte((BlockAddr & 0xFF0000) >> 16);

	/* 发送块区擦除地址中位 */
	X25Qx_SPI_FLASH_SendByte((BlockAddr & 0xFF00) >> 8);

	/* 发送块区擦除地址低位 */
	X25Qx_SPI_FLASH_SendByte(BlockAddr & 0xFF);

	/* Deselect the FLASH: Chip Select high */
	X25Qx_FLASH_SPIx_NSS_DISABLE();

	/* 等待擦除完毕 */
	X25Qx_SPIFLASH_WaitForBusy();
#endif
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_EraseSector(uint32_t SectorAddr)
 @Description			X25Qx_SPIFLASH_EraseSector		: X25Q SPIFLASH 擦除Sector
 @Input				SectorAddr					: 扇区地址(0x1000倍数)
 @Return				void
 @attention			X25QxCSIG SPI FLASH 最小擦除块大小为4KB(4096Byte),即一个扇区大小,在写入数据之前要求先擦除空间
					20MS
**********************************************************************************************************/
void X25Qx_SPIFLASH_EraseSector(uint32_t SectorAddr)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	if (X25QxCSIG_OK != X25Qx_SPIFLASH_Get_Status()) {
		return;
	}

	/* 发送FLASH写使能命令 */
	X25Qx_SPIFLASH_WriteEnable();

	/* 等待FLASH空闲 */
	X25Qx_SPIFLASH_WaitForBusy();

	/* Select the FLASH: Chip Select low */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	/* 发送扇区擦除命令 */
	X25Qx_SPI_FLASH_SendByte(X25Qx_SectorErase);

	/* 发送扇区擦除地址高位 */
	X25Qx_SPI_FLASH_SendByte((SectorAddr & 0xFF0000) >> 16);

	/* 发送扇区擦除地址中位 */
	X25Qx_SPI_FLASH_SendByte((SectorAddr & 0xFF00) >> 8);

	/* 发送扇区擦除地址低位 */
	X25Qx_SPI_FLASH_SendByte(SectorAddr & 0xFF);

	/* Deselect the FLASH: Chip Select high */
	X25Qx_FLASH_SPIx_NSS_DISABLE();

	/* 等待擦除完毕 */
	X25Qx_SPIFLASH_WaitForBusy();
#endif
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
 @Description			X25Qx_SPIFLASH_ReadBuffer		: X25Q SPIFLASH 读取SPI FLASH数据
 @Input				pBuffer						: 数据存储区
					ReadAddr						: 数据读取地址
					NumByteToRead					: 读取数据长度
 @Return				void
**********************************************************************************************************/
void X25Qx_SPIFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	if (X25QxCSIG_OK != X25Qx_SPIFLASH_Get_Status()) {
		return;
	}

	/* Select the FLASH: Chip Select low */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	/* 发送读指令 */
	X25Qx_SPI_FLASH_SendByte(X25Qx_ReadData);

	/* 发送读地址高位 */
	X25Qx_SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);

	/* 发送读地址中位 */
	X25Qx_SPI_FLASH_SendByte((ReadAddr & 0xFF00) >> 8);

	/* 发送读地址低位 */
	X25Qx_SPI_FLASH_SendByte(ReadAddr & 0xFF);

	/* 读取数据 */
	while (NumByteToRead--) {
		*pBuffer = X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte);
		pBuffer++;
	}

	/* Deselect the FLASH: Chip Select high */
	X25Qx_FLASH_SPIx_NSS_DISABLE();
#endif
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
 @Description			X25Qx_SPIFLASH_WritePage			: X25Q SPIFLASH 写入SPI FLASH数据Page
 @Input				pBuffer						: 数据存储区
					WriteAddr						: 数据写入地址
					NumByteToWrite					: 写入数据长度
 @Return				void
 @attention			写入字节数不得超过该页写入剩余字节数
**********************************************************************************************************/
void X25Qx_SPIFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	if (X25QxCSIG_OK != X25Qx_SPIFLASH_Get_Status()) {
		return;
	}

	/* 发送FLASH写使能命令 */
	X25Qx_SPIFLASH_WriteEnable();

	/* 等待FLASH空闲 */
	X25Qx_SPIFLASH_WaitForBusy();

	/* Select the FLASH: Chip Select low */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	/* 发送页写命令 */
	X25Qx_SPI_FLASH_SendByte(X25Qx_PageProgram);

	/* 发送写地址高位 */
	X25Qx_SPI_FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);

	/* 发送写地址中位 */
	X25Qx_SPI_FLASH_SendByte((WriteAddr & 0xFF00) >> 8);

	/* 发送写地址低位 */
	X25Qx_SPI_FLASH_SendByte(WriteAddr & 0xFF);

	/* 写入数据 */
	while (NumByteToWrite--) {
		X25Qx_SPI_FLASH_SendByte(*pBuffer);
		pBuffer++;
	}

	/* Deselect the FLASH: Chip Select high */
	X25Qx_FLASH_SPIx_NSS_DISABLE();

	/* 等待写入完毕 */
	X25Qx_SPIFLASH_WaitForBusy();
#endif
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
 @Description			X25Qx_SPIFLASH_WriteBuffer		: X25Q SPIFLASH 写入SPI FLASH数据
 @Input				pBuffer						: 数据存储区
					WriteAddr						: 数据写入地址
					NumByteToWrite					: 写入数据长度
 @Return				void
 @attention			具有自动换页功能
**********************************************************************************************************/
void X25Qx_SPIFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	uint32_t pagereMain;

	if (X25QxCSIG_OK != X25Qx_SPIFLASH_Get_Status()) {
		return;
	}

	pagereMain = X25Qx_PAGE_BYTE_SIZE - WriteAddr % X25Qx_PAGE_BYTE_SIZE;
	if (NumByteToWrite <= pagereMain) pagereMain = NumByteToWrite;

	while (1) {
		X25Qx_SPIFLASH_WritePage(pBuffer, WriteAddr, pagereMain);
		if (NumByteToWrite == pagereMain) break;
		else {
			pBuffer += pagereMain;
			WriteAddr += pagereMain;

			NumByteToWrite -= pagereMain;
			if (NumByteToWrite > X25Qx_PAGE_BYTE_SIZE) pagereMain = X25Qx_PAGE_BYTE_SIZE;
			else pagereMain = NumByteToWrite;
		}
	}
#endif
}

/**********************************************************************************************************
 @Function			unsigned char X25Qx_SPIFLASH_GetByte(uint32_t ReadAddr)
 @Description			X25Qx_SPIFLASH_GetByte						: X25Q SPIFLASH 读取1个Byte
 @Input				void
 @Return				val
**********************************************************************************************************/
unsigned char X25Qx_SPIFLASH_GetByte(uint32_t ReadAddr)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	unsigned char val = 0;

	X25Qx_SPIFLASH_ReadBuffer(&val, ReadAddr, 1);

	return val;
#endif

	return 0;
}

/**********************************************************************************************************
 @Function			unsigned short X25Qx_SPIFLASH_GetHalfWord(uint32_t ReadAddr)
 @Description			X25Qx_SPIFLASH_GetHalfWord					: X25Q SPIFLASH 读取2个Byte
 @Input				void
 @Return				val
**********************************************************************************************************/
unsigned short X25Qx_SPIFLASH_GetHalfWord(uint32_t ReadAddr)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	unsigned short val = 0;
	unsigned char tmpval[2];

	X25Qx_SPIFLASH_ReadBuffer(tmpval, ReadAddr, 2);

	val |= tmpval[0];
	val |= tmpval[1] << 8;

	return val;
#endif

	return 0;
}

/**********************************************************************************************************
 @Function			unsigned int X25Qx_SPIFLASH_GetWord(uint32_t ReadAddr)
 @Description			X25Qx_SPIFLASH_GetWord						: X25Q SPIFLASH 读取4个Byte
 @Input				void
 @Return				val
**********************************************************************************************************/
unsigned int X25Qx_SPIFLASH_GetWord(uint32_t ReadAddr)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	unsigned int val = 0;
	unsigned char tmpval[4];

	X25Qx_SPIFLASH_ReadBuffer(tmpval, ReadAddr, 4);

	val |= tmpval[0];
	val |= tmpval[1] << 8;
	val |= tmpval[2] << 16;
	val |= tmpval[3] << 24;

	return val;
#endif

	return 0;
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_SetByte(uint32_t WriteAddr, unsigned char val)
 @Description			X25Qx_SPIFLASH_SetByte						: X25Q SPIFLASH 写入1个Byte
 @Input				val
 @Return				void
**********************************************************************************************************/
void X25Qx_SPIFLASH_SetByte(uint32_t WriteAddr, unsigned char val)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	X25Qx_SPIFLASH_WriteBuffer(&val, WriteAddr, 1);
#endif
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_SetHalfWord(uint32_t WriteAddr, unsigned short val)
 @Description			X25Qx_SPIFLASH_SetHalfWord					: X25Q SPIFLASH 写入2个Byte
 @Input				val
 @Return				void
**********************************************************************************************************/
void X25Qx_SPIFLASH_SetHalfWord(uint32_t WriteAddr, unsigned short val)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	unsigned char tmpval[2];

	tmpval[0] = val & 0xFF;
	tmpval[1] = (val >> 8) & 0xFF;

	X25Qx_SPIFLASH_WriteBuffer(tmpval, WriteAddr, 2);
#endif
}

/**********************************************************************************************************
 @Function			void X25Qx_SPIFLASH_SetWord(uint32_t WriteAddr, unsigned int val)
 @Description			X25Qx_SPIFLASH_SetWord						: X25Q SPIFLASH 写入4个Byte
 @Input				val
 @Return				void
**********************************************************************************************************/
void X25Qx_SPIFLASH_SetWord(uint32_t WriteAddr, unsigned int val)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	unsigned char tmpval[4];

	tmpval[0] = val & 0xFF;
	tmpval[1] = (val >> 8) & 0xFF;
	tmpval[2] = (val >> 16) & 0xFF;
	tmpval[3] = (val >> 24) & 0xFF;

	X25Qx_SPIFLASH_WriteBuffer(tmpval, WriteAddr, 4);
#endif
}

/**********************************************************************************************************
 @Function			unsigned int X25Qx_SPIFLASH_GetNumofByte(uint32_t ReadAddr, uint16_t AllNum, uint8_t ByteVal)
 @Description			X25Qx_SPIFLASH_GetNumofByte					: X25Q SPIFLASH 读取指定地址中指定字节中有该值的个数
 @Input				ReadAddr									: 读取地址
					AllNum									: 读取字节数
					ByteVal									: 匹配值
 @Return				val
**********************************************************************************************************/
unsigned int X25Qx_SPIFLASH_GetNumofByte(uint32_t ReadAddr, uint16_t AllNum, uint8_t ByteVal)
{
#if USE_GD25Q_80E || USE_GD25Q_256E || USE_W25Q_128J
	unsigned int ReadByteval = 0;

	if (X25QxCSIG_OK != X25Qx_SPIFLASH_Get_Status()) {
		return 0;
	}

	/* Select the FLASH: Chip Select low */
	X25Qx_FLASH_SPIx_NSS_ENABLE();

	/* 发送读指令 */
	X25Qx_SPI_FLASH_SendByte(X25Qx_ReadData);

	/* 发送读地址高位 */
	X25Qx_SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);

	/* 发送读地址中位 */
	X25Qx_SPI_FLASH_SendByte((ReadAddr & 0xFF00) >> 8);

	/* 发送读地址低位 */
	X25Qx_SPI_FLASH_SendByte(ReadAddr & 0xFF);

	/* 读取数据 */
	while (AllNum--) {
		if (ByteVal == X25Qx_SPI_FLASH_SendByte(X25Qx_Dummy_Byte)) {
			ReadByteval++;
		}
	}

	/* Deselect the FLASH: Chip Select high */
	X25Qx_FLASH_SPIx_NSS_DISABLE();

	return ReadByteval;
#endif
}

/********************************************** END OF FLEE **********************************************/
