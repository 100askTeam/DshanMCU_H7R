/*
 * lvgl_port_display.c
 *
 *  Created on: Jun 24, 2024
 *      Author: biubiu
 */

/*********************
 *      INCLUDES
 *********************/

#include "lvgl_port_display.h"
#include "main.h"
#include "ltdc.h"
#include "dma2d.h"

//#define DIRECT_MODE

#ifdef DIRECT_MODE
#define LVGL_BUFFER_1_ADDR_AT_SDRAM	(0xC0000000)
#define LVGL_BUFFER_2_ADDR_AT_SDRAM	(0xC0100000)
#endif

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void disp_flush (lv_display_t *, const lv_area_t *, uint8_t *);

#ifndef DIRECT_MODE
static void disp_flush_complete (DMA2D_HandleTypeDef*);
#endif

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_display_t * disp;
static lv_thread_sync_t sync;
static uint8_t * buf_rotation = (uint8_t *)(uint32_t) 0xC0200000;



/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lvgl_display_init (void)
{
	/* display initialization */

	disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
	//lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);

#ifdef DIRECT_MODE
	lv_display_set_buffers(disp, (void*) LVGL_BUFFER_1_ADDR_AT_SDRAM, (void*) LVGL_BUFFER_2_ADDR_AT_SDRAM, (uint32_t)(MY_DISP_HOR_RES * MY_DISP_VER_RES * 2), LV_DISPLAY_RENDER_MODE_DIRECT);
	HAL_LTDC_SetAddress(&hltdc, (uint32_t)LVGL_BUFFER_2_ADDR_AT_SDRAM, LTDC_LAYER_1);	// start with the second buffer: LVGL will render into the first buffer
#else
	//__attribute__((section(".sdram"))) static uint8_t buf1[600*1024*2];
	__attribute__((section(".lv_ram"))) static uint8_t buf1[256*1024];

	lv_display_set_buffers(disp, (void*) buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

	/* interrupt callback for DMA2D transfer */
	hdma2d.XferCpltCallback = disp_flush_complete;
//	lv_display_set_flush_wait_cb(disp, disp_flush_wait);
//	lv_thread_sync_init(&sync);
#endif

	lv_display_set_flush_cb(disp, disp_flush);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void disp_flush (lv_display_t * display,
            const lv_area_t * area,
            uint8_t * px_map)
{
#if 0
	static int g_sync_time;
	static int g_sync_time_pre;
	static int g_sync_time_delta;
	g_sync_time = HAL_GetTick();
	g_sync_time_delta = g_sync_time - g_sync_time_pre;
	g_sync_time_pre = g_sync_time;
	lv_display_flush_ready(disp);
	return;
#endif

#ifdef DIRECT_MODE
	if (lv_display_flush_is_last(disp)) {
		SCB_CleanInvalidateDCache();
		// wait for VSYNC to avoid tearing

		while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
		// swap framebuffers (NOTE: LVGL will swap the buffers in the background, so here we can set the LCD framebuffer to the current LVGL buffer, which has been just completed)
		HAL_LTDC_SetAddress(&hltdc, (uint32_t)(lv_display_get_buf_active(disp)->data), LTDC_LAYER_1);
		//HAL_DMA2D_Start_IT(&hdma2d,\
						  (uint32_t)(lv_display_get_buf_active(disp)->data), /* Color value in Register to Memory DMA2D mode */\
						  0xC0000000,  /* DMA2D output buffer */\
						  1024, /* width of buffer in pixels */\
						  600); /* height of buffer in lines */

	}
	lv_display_flush_ready(disp);
#else

#if 0
	/* Not support rotation */
	lv_coord_t width = lv_area_get_width(area);
	lv_coord_t height = lv_area_get_height(area);

	SCB_CleanInvalidateDCache();

	DMA2D->CR = 0x0U << DMA2D_CR_MODE_Pos;
	DMA2D->FGPFCCR = DMA2D_INPUT_RGB565;	// 设置前景色颜色格式
	DMA2D->FGMAR = (uint32_t)px_map;		// 设置前景数据内存地址
	DMA2D->FGOR = 0;						// 设置前景数据传输偏移
	DMA2D->OPFCCR = DMA2D_OUTPUT_RGB565;	// 设置颜色格式
	DMA2D->OMAR = hltdc.LayerCfg[0].FBStartAdress + 2 * \
				(area->y1 * MY_DISP_HOR_RES + area->x1); // 填充区域的起始内存地址
	DMA2D->OOR = MY_DISP_HOR_RES - width;	// 行偏移，即每行多少像素（以像素为单位）
	DMA2D->NLR = (width << DMA2D_NLR_PL_Pos) | (height << DMA2D_NLR_NL_Pos); // 设置填充区域的宽和高（单位：像素）
	DMA2D->IFCR = 0x3FU;		 /* 设置DMA2D中断标志清除寄存器 */
	DMA2D->CR |= DMA2D_CR_TCIE;
	DMA2D->CR |= DMA2D_CR_START; /* 启动传输 */

#else
	/* Support rotation */
	lv_display_rotation_t rotation = lv_display_get_rotation(lv_display_get_default());

	lv_area_t my_area;
	memcpy(&my_area, area, sizeof(lv_area_t));
	lv_display_rotate_area(lv_display_get_default(), &my_area);

	lv_coord_t width = lv_area_get_width(area);
	lv_coord_t height = lv_area_get_height(area);

	if((rotation == LV_DISPLAY_ROTATION_90) ||\
	   (rotation == LV_DISPLAY_ROTATION_270))
	{
		lv_draw_sw_rotate(px_map, buf_rotation, \
						  width, height, width * 2,  height * 2, \
						  rotation, LV_COLOR_FORMAT_RGB565);
	}
	else
	{
		lv_draw_sw_rotate(px_map, buf_rotation, \
						  width, height, width * 2,  width * 2, \
						  rotation, LV_COLOR_FORMAT_RGB565);
	}

	width = lv_area_get_width(&my_area);
	height = lv_area_get_height(&my_area);

	SCB_CleanInvalidateDCache();

	DMA2D->CR = 0x0U << DMA2D_CR_MODE_Pos;
	DMA2D->FGPFCCR = DMA2D_INPUT_RGB565;	// 设置前景色颜色格式

	DMA2D->FGMAR = (uint32_t)px_map;		// 设置前景数据内存地址
	if((rotation == LV_DISPLAY_ROTATION_90)  ||\
	   (rotation == LV_DISPLAY_ROTATION_180) ||\
	   (rotation == LV_DISPLAY_ROTATION_270))
	{
		DMA2D->FGMAR = (uint32_t)buf_rotation;		// 设置前景数据内存地址
	}

	DMA2D->FGOR = 0;						// 设置前景数据传输偏移
	DMA2D->OPFCCR = DMA2D_OUTPUT_RGB565;	// 设置颜色格式
	DMA2D->OMAR = hltdc.LayerCfg[0].FBStartAdress + 2 * \
				(my_area.y1 * MY_DISP_HOR_RES + my_area.x1); // 填充区域的起始内存地址
	DMA2D->OOR = MY_DISP_HOR_RES - width;	// 行偏移，即每行多少像素（以像素为单位）
	DMA2D->NLR = (width << DMA2D_NLR_PL_Pos) | (height << DMA2D_NLR_NL_Pos); // 设置填充区域的宽和高（单位：像素）
	DMA2D->IFCR = 0x3FU;		 /* 设置DMA2D中断标志清除寄存器 */
	DMA2D->CR |= DMA2D_CR_TCIE;
	DMA2D->CR |= DMA2D_CR_START; /* 启动传输 */

#endif
#endif
}

#ifndef DIRECT_MODE

static void
disp_flush_complete (DMA2D_HandleTypeDef *hdma2d)
{
//	lv_thread_sync_signal_isr(&sync);

  lv_display_flush_ready(disp);
}

#endif
