/*
 * sdram.h
 *
 *  Created on: Jun 15, 2024
 *      Author: biubiu
 */

#ifndef INC_SDRAM_H_
#define INC_SDRAM_H_

#include "stm32h7rsxx_hal.h"

//#define StartAddresse 			0xC1000000
#define SDRAM_BANK_ADDR			((uint32_t)0xC1000000)

#define SDRAM_TIMEOUT                            ((uint32_t)0xFFFF)

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0003)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

#define BUFFER_SIZE         ((uint32_t)10)
#define WRITE_READ_ADDR     ((uint32_t)0x0800)

/* Exported types ------------------------------------------------------------*/
typedef enum {PASSED = 0, FAILED = !PASSED} TestStatus_t;

void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);
void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLength, uint32_t uwOffset);

void SDRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize);
void SDRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize);

#endif /* INC_SDRAM_H_ */
