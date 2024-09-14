/*
 * copy_flash_to_sdram.c
 *
 *  Created on: Jun 22, 2024
 *      Author: biubiu
 */


#include "X25Qx.h"
#include "sdram.h"
#include "copy_flash_to_sdram.h"

#define IMAGE_BUFFER	(0x2800)
#define IMAGE_HEADER_SIZE	((uint32_t)0x00001000)

#define IH_NMLEN 	32
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

#define DIRECT_COPY 1

#if (DIRECT_COPY == 0)
//__attribute__((section(".sdram"))) static uint8_t Data[IMAGE_BUFFER];
static uint8_t Data[IMAGE_BUFFER];
#endif

int copy_flash_to_sdram(void)
{
#if (DIRECT_COPY == 0)
	uint32_t index = 0;
	uint32_t sector_sum = 0x01000000/IMAGE_BUFFER;
	uint32_t copy_buff_size = 0;
	uint32_t last_size = 0;

	image_header_t image_header;

	image_header.ih_size = 0;
	X25Qx_SPIFLASH_ReadBuffer((uint8_t *)&image_header, (uint32_t)(0x00000000), (uint32_t)(sizeof(image_header)));
	if(image_header.ih_size > 0) {
		sector_sum = (image_header.ih_size) / IMAGE_BUFFER;
		last_size = (image_header.ih_size) % IMAGE_BUFFER;
	}

	copy_buff_size = IMAGE_BUFFER;
	for(index = 0; index <= sector_sum; index++)
	{
		if(index == sector_sum)	copy_buff_size = last_size;
		X25Qx_SPIFLASH_ReadBuffer(Data, (index * copy_buff_size)+IMAGE_HEADER_SIZE, copy_buff_size);

		//SDRAM_WriteBuffer((uint32_t*)Data, (StartAddresse + (index * 0x1000)), 0x1000/4);
		SDRAM_WriteBuffer((uint32_t*)Data, ((index * copy_buff_size)), copy_buff_size/4);
	}
#else
	uint8_t *Data;
	Data = (uint8_t*) (SDRAM_BANK_ADDR);

	image_header_t image_header;

	image_header.ih_size = 0;
	X25Qx_SPIFLASH_ReadBuffer((uint8_t *)&image_header, (uint32_t)(0x00000000), (uint32_t)(sizeof(image_header)));

	if(image_header.ih_size == 0)	image_header.ih_size = 0x01000000;

	X25Qx_SPIFLASH_ReadBuffer(Data, IMAGE_HEADER_SIZE, image_header.ih_size);
#endif
	return 0;
}
