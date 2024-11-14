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
 * 2024.11.11      v01      周岳标       创建文件
 *-----------------------------------------------------
 */

#include "main.h"
#include "tim.h"
#include "driver_key.h"


static uint8_t my_key_points[MY_KEY_SUM];


void Key_IRQ_Callback(uint16_t GPIO_Pin)
{
    static uint64_t pre_time = 0;

    // 消抖
#if 1
    uint64_t time = 0;

	/* 1. 记录中断发生的时刻 */
	time = system_get_ns();

	/* 上升沿触发: 必定是高电平
	 * 防抖
	 */
	if (time - pre_time < 2000000) /* 当前中断的时间 跟 上次中断的时间 < 2ms的话,认为是抖动 */
	{
		pre_time = time;
		return;
	}
	pre_time = time;
#endif

	switch (GPIO_Pin)
	{
		case USER_KEY1_Pin:
			my_key_points[0] = 1;
			break;
		case USER_KEY2_Pin:
			my_key_points[1] = 1;
			break;
		case USER_KEY3_Pin:
			my_key_points[2] = 1;
			break;
		default:
			break;
	}
}



bool key_is_pressed(uint8_t id)
{

    /*Your code comes here*/
    if(id >= MY_KEY_SUM) return false;

    uint8_t key_points = my_key_points[id];

    my_key_points[id] = 0;

    return key_points;
}



