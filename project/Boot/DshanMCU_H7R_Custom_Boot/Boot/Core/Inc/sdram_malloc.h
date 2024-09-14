/*
 * sdram_malloc.h
 *
 *  Created on: Jun 15, 2024
 *      Author: biubiu
 */

#ifndef INC_SDRAM_MALLOC_H_
#define INC_SDRAM_MALLOC_H_

#include "stdint.h"
#include "string.h"

#ifndef NULL
#define NULL 0
#endif

//SDRAM内存参数设定
#define MEM_MAX_SIZE			32*1024*1024  					//最大管理内存32M
#define MEM_BLOCK_SIZE			64  	  						//内存块大小为64字节
#define MEM_MAP_SIZE        	(MEM_MAX_SIZE / MEM_BLOCK_SIZE)   //内存表大小


//用户调用函数
void mem_free(void *ptr)  ;  			//内存释放(外部调用)
void *mem_malloc(uint32_t size);			//内存分配(外部调用)

#endif /* INC_SDRAM_MALLOC_H_ */
