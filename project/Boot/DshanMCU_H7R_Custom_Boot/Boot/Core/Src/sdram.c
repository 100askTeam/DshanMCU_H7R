/*
 * sdram.c
 *
 *  Created on: Jun 15, 2024
 *      Author: biubiu
 */

#include "sdram.h"

#include "fmc.h"

// 参考：
//	https://www.waveshare.net/study/article-660-1.html
//	https://github.com/floppes/stm32doom/blob/master/src/sdram.h
// sdram内存管理示例（malloc）：https://blog.csdn.net/Ningjianwen/article/details/90940570
/**
  * @brief  Perform the SDRAM exernal memory inialization sequence
  * @param  hsdram: SDRAM handle
  * @param  Command: Pointer to SDRAM command structure
  * @retval None
  */
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command)
{
  __IO uint32_t tmpmrd =0;
  uint32_t commandtarget = 0;


  commandtarget = FMC_SDRAM_CMD_TARGET_BANK1;
  Command->CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
  Command->CommandTarget = commandtarget;
  Command->AutoRefreshNumber = 1;
  Command->ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0xffff);

  /* Step 4: Insert 100 ms delay */
  HAL_Delay(2);

  /* Step 5: Configure a PALL (precharge all) command */
  Command->CommandMode = FMC_SDRAM_CMD_PALL;
  Command->CommandTarget = commandtarget;
  Command->AutoRefreshNumber = 1;
  Command->ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0xffff);

  /* Step 6 : Configure a Auto-Refresh command */
  Command->CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command->CommandTarget = commandtarget;
  Command->AutoRefreshNumber = 8;
  Command->ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0xffff);

  /* Step 7: Program the external memory mode register */
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_3           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  Command->CommandTarget = commandtarget;
  Command->AutoRefreshNumber = 1;
  Command->ModeRegisterDefinition = tmpmrd;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0xffff);


  //hsdram->Instance->SDRTR |=  ((uint32_t)((156)<< 1));
  /*
   	配置SDRAM的刷新率，关于刷新频率的数值是这么得到的。目前公认的标准是SDRAM中电容保存数据的上限是64ms，也就是说每一行刷新的循环周期是64ms。这样刷新速度就是：64ms /行数量。
   	我们在看内存规格时，经常会看到4096 Refresh Cycles/64ms或8192 RefreshCycles/64ms的标识，这里的4096与8192就代表这个芯片中每个L-Bank的行数。
   	刷新命令一次对一行有效，发送间隔也是随总行数而变化，4096行时为15.625μs，8192行时就为7.8125μs。

	使用型号IS42S32800G-6BLI，自刷新规格是4K / 64ms，即4096/64ms。刷新一行需要15.625μs。（0.0156250）
	使用型号IS42S16160G-7TL， 自刷新规格是8K / 64ms，即8192/64ms。刷新一行需要7.8125μs。（0.0078125）

	IS42S32800G-6BLI刷新计数 	 = （SDRAM refresh period / Number of rows）*SDRAM时钟速度 – 20
							 = （64ms / 4096）* 100MHz – 20
							 =  1562.5 – 20
							 =  1542.5 ，取值1543

	IS42S16160G-7TL刷新计数 	 = （SDRAM refresh period / Number of rows）*SDRAM时钟速度 – 20
							 = （64ms / 8192）* 100MHz – 20
							 =  781.25 – 20
							 =  761.25 ，取值762

	实际上这个数值稍差点，在使用SDRAM时，基本都没有影响的。
   */
  HAL_SDRAM_ProgramRefreshRate(hsdram, 762);
  //HAL_SDRAM_ProgramRefreshRate(hsdram, 1524);
}


/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the buffer to fill
  * @param  uwBufferLength: size of the buffer to fill
  * @param  uwOffset: first value to fill on the buffer
  * @retval None
  */
void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLength, uint32_t uwOffset)
{
  uint32_t tmpIndex = 0;

  /* Put in global buffer different values */
  for (tmpIndex = 0; tmpIndex < uwBufferLength; tmpIndex++ )
  {
    pBuffer[tmpIndex] = tmpIndex + uwOffset;
  }
}



/**
  * @brief  Reads data buffer from the SDRAM memory.
  * @param  pBuffer: pointer to buffer.
  * @param  ReadAddress: SDRAM memory internal address from which the data will be
  *         read.
  * @param  uwBufferSize: number of words to write.
  * @retval None.
  */
void SDRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize)
{
  __IO uint32_t write_pointer = (uint32_t)uwReadAddress;


  /* Wait until the SDRAM controller is ready */
//  while(FMC_GetFlagStatus(FMC_SDRAM_BANK1, FMC_SDRAM_FLAG_BUSY) != RESET)
//  {
//  }

  /* Read data */
  for(; uwBufferSize != 0x00; uwBufferSize--)
  {
   *pBuffer++ = *(__IO uint32_t *)(SDRAM_BANK_ADDR + write_pointer );

   /* Increment the address*/
    write_pointer += 4;
  }
}

/**
  * @brief  Writes a Entire-word buffer to the SDRAM memory.
  * @param  pBuffer: pointer to buffer.
  * @param  uwWriteAddress: SDRAM memory internal address from which the data will be
  *         written.
  * @param  uwBufferSize: number of words to write.
  * @retval None.
  */
void SDRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize)
{
  __IO uint32_t write_pointer = (uint32_t)uwWriteAddress;

  /* Disable write protection */
  //FMC_SDRAM_WriteProtection_Disable(&hsdram1, FMC_SDRAM_BANK1);

  /* Wait until the SDRAM controller is ready */
//  while(FMC_GetFlagStatus(FMC_SDRAM_BANK1, FMC_SDRAM_FLAG_BUSY) != RESET)
//  {
//  }

  /* While there is data to write */
  for (; uwBufferSize != 0; uwBufferSize--)
  {
    /* Transfer data to the memory */
    *(uint32_t *) (SDRAM_BANK_ADDR + write_pointer) = *pBuffer++;

    /* Increment the address*/
    write_pointer += 4;
  }

}

