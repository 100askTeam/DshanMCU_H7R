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


#include "driver_lcd_backlight.h"
#include "tim.h"

extern TIM_HandleTypeDef htim12;

void lcd_backlight_init(void)
{
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
}


void lcd_backlight_set_value(uint16_t pwm_value)
{
	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_2, pwm_value);
}

void lcd_backlight_test(void)
{
	lcd_backlight_init();

	uint16_t pwmVal=0;   //PWM占空�?
    while (1)
    {
    	while (pwmVal< 1000)
		{
		  pwmVal++;
		  lcd_backlight_set_value(pwmVal);  // 修改比较值，修改占空比
		  //TIM3->CCR1 = pwmVal;      		// 与上方效果一样
		  HAL_Delay(1);
		}
		while (pwmVal)
		{
		  pwmVal--;
		  lcd_backlight_set_value(pwmVal);  // 修改比较值，修改占空比
		  //TIM3->CCR1 = pwmVal;      		// 与上方效果一样
		  HAL_Delay(1);
		}
		HAL_Delay(200);
    }
}


