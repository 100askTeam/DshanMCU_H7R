// SPDX-License-Identifier: GPL-3.0-only
/*
 * Copyright (c) 2008-2023 100askTeam : Dongshan WEI <weidongshan@qq.com> 
 * Discourse:  https://forums.100ask.net
 */

 
/*  Copyright (C) 2008-2023 深圳百问网科技有限公司
 *  All rights reserved
 *
 *
 * 免责声明: 百问网编写的文档，仅供学员学习使用，可以转发或引用(请保留作者信息)，禁止用于商业用途！
 * 免责声明: 百问网编写的程序，可以用于商业用途，但百问网不承担任何后果！
 * 
 * 
 * 本程序遵循GPL V3协议，使用请遵循协议许可
 * 本程序所用的开发板：	DShanMCU-F103
 * 百问网嵌入式学习平台：https://www.100ask.net
 * 百问网技术交流社区：	https://forums.100ask.net
 * 百问网官方B站：				https://space.bilibili.com/275908810
 * 百问网官方淘宝：			https://100ask.taobao.com
 * 联系我们(E-mail)：	  weidongshan@qq.com
 *
 * 版权所有，盗版必究。
 *  
 * 修改历史     版本号           作者        修改内容
 *-----------------------------------------------------
 * 2023.08.04      v01         百问科技      创建文件
 *-----------------------------------------------------
 */


#include "driver_ws28xx.h"

#include "tim.h"


WS28XX_HandleTypeDef WS28xx_Handle;

void ws28xx_init(void)
{
	WS28XX_Init(&WS28xx_Handle, &htim3, WS28XX_TIMER_FREQUENCY_MHZ, TIM_CHANNEL_4, WS28XX_PIXEL_MAX);
	//WS28XX_Init(&WS28xx_Handle, &htim3, 72, TIM_CHANNEL_4, WS28XX_PIXEL_MAX);
	HAL_Delay(10);

	WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 0, 0x0000);
	WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 1, 0x0000);
	WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 2, 0x0000);
	WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 3, 0x0000);
	WS28XX_Update(&WS28xx_Handle);
	HAL_Delay(10);
}


void ws28xx_all_opt(uint16_t pwm_value)
{
	if(pwm_value)
	{
		WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 0, 0xf800);
		WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 1, 0x7e0);
		WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 2, 0x1f);
		WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 3, 0xffff);
	}
	else
	{
		WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 0, 0x0000);
		WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 1, 0x0000);
		WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 2, 0x0000);
		WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 3, 0x0000);
	}

	WS28XX_Update(&WS28xx_Handle);
	//HAL_Delay(100);
}

void ws28xx_test(void)
{
	ws28xx_init();
	lcd_backlight_init();

	uint8_t flag = 0;
	uint16_t color_arry[13][4] = {
			{0x0000, 0x0000, 0x0000, 0x0000},
			{0xf800, 0x0000, 0x0000, 0x0000},
			{0x0000, 0x7e0, 0x0000, 0x0000},
			{0x0000, 0x0000, 0x1f, 0x0000},
			{0x0000, 0x0000, 0x0000, 0xffff},

			{0xf800, 0x7e0,  0x1f,   0xffff},
			{0x0000, 0x0000, 0x0000, 0x0000},
			{0xffff, 0xffff, 0xffff, 0xffff},
			{0xf800, 0x7e0,  0x1f,   0xffff},
			{0x0000, 0x0000, 0x0000, 0x0000},
			{0xf800, 0x7e0,  0x1f,   0xffff},
			{0x0000, 0x0000, 0x0000, 0x0000},
			{0xf800, 0x7e0,  0x1f,   0xffff},
		};

    while (1)
    {
    	for(int i = 0; i < 2; i++)
    	{
    		WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 0, color_arry[i][0]);
    		WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 1, color_arry[i][1]);
    		WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 2, color_arry[i][2]);
    		WS28XX_SetPixel_RGB_565(&WS28xx_Handle, 3, color_arry[i][3]);
    		WS28XX_Update(&WS28xx_Handle);
    		HAL_Delay(500);
    	}

    	if(flag == 0)
    	{
    		lcd_backlight_set_value(1000);
    		flag = 1;
    	}
    	else
    	{
			lcd_backlight_set_value(0);
			flag = 0;
    	}
		HAL_Delay(1000);
    }
}


