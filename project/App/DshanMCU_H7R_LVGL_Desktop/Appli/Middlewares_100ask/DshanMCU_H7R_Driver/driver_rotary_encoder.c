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
 * 2024.11.11      v02         周岳标       修改
 *-----------------------------------------------------
 */

#include "main.h"
#include "driver_timer.h"
#include "driver_rotary_encoder.h"


#define ROTARY_ENCODER_S1_GPIO_GROUP 	ENCODER_S1_GPIO_Port
#define ROTARY_ENCODER_S1_GPIO_PIN   	ENCODER_S1_Pin

#define ROTARY_ENCODER_S2_GPIO_GROUP 	ENCODER_S2_GPIO_Port
#define ROTARY_ENCODER_S2_GPIO_PIN   	ENCODER_S2_Pin

#define ROTARY_ENCODER_KEY_GPIO_GROUP 	ENCODER_KEY_GPIO_Port
#define ROTARY_ENCODER_KEY_GPIO_PIN   	ENCODER_KEY_Pin

static int32_t g_count = 0;

/**********************************************************************
 * 函数名称： RotaryEncoder_Get_Key
 * 功能描述： 读取旋转编码器Key引脚电平
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 1-按键被按下, 0-按键被松开
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/04	     V1.0	  韦东山	      创建
 ***********************************************************************/
static int RotaryEncoder_Get_Key(void)
{
    if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(ROTARY_ENCODER_KEY_GPIO_GROUP, ROTARY_ENCODER_KEY_GPIO_PIN))
        return 1;
    else
        return 0;
}

/**********************************************************************
 * 函数名称： RotaryEncoder_Get_S1
 * 功能描述： 读取旋转编码器S1引脚电平
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/04	     V1.0	  韦东山	      创建
 ***********************************************************************/
static int RotaryEncoder_Get_S1(void)
{
    if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(ROTARY_ENCODER_S1_GPIO_GROUP, ROTARY_ENCODER_S1_GPIO_PIN))
        return 0;
    else
        return 1;
}

/**********************************************************************
 * 函数名称： RotaryEncoder_Get_S2
 * 功能描述： 读取旋转编码器S2引脚电平
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/04	     V1.0	  韦东山	      创建
 ***********************************************************************/
static int RotaryEncoder_Get_S2(void)
{
    if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(ROTARY_ENCODER_S2_GPIO_GROUP, ROTARY_ENCODER_S2_GPIO_PIN))
        return 0;
    else
        return 1;
}


/**********************************************************************
 * 函数名称： RotaryEncoder_IRQ_Callback
 * 功能描述： 旋转编码器的中断回调函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/04	     V1.0	  韦东山	      创建
 * -----------------------------------------------
 * 2024.11.11      v02         周岳标       修改
 * -----------------------------------------------
 ***********************************************************************/
void RotaryEncoder_IRQ_Callback(void)
{
    uint64_t time;
    static uint64_t pre_time = 0;
        
	/* 1. 记录中断发生的时刻 */	
	time = system_get_ns();

	/* 上升沿触发: 必定是高电平
	 * 防抖
	 */
	if (time - pre_time < 2000000) /* 如果当前中断的时间与上次中断的时间对比 < 2ms，则认为是抖动 */
	{
		pre_time = time;
		return;
	}
	pre_time = time;

    if (!RotaryEncoder_Get_S1())
        return;

    /* S1上升沿触发中断
     * S2为0表示逆时针转, 为1表示顺时针转
     */
    if (RotaryEncoder_Get_S2())
    {
        g_count++;
    }
    else
    {
        g_count--;
    }
}


/**********************************************************************
 * 函数名称： RotaryEncoder_Init
 * 功能描述： 旋转编码器的初始化函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/05	     V1.0	  韦东山	      创建
 ***********************************************************************/
void RotaryEncoder_Init(void)
{
    /* S2,KEY在MX_GPIO_Init中被配置为输入引脚 */
    /* S1在MX_GPIO_Init中被配置为中断引脚,上升沿触发 */
}

/**********************************************************************
 * 函数名称： RotaryEncoder_Write
 * 功能描述： 旋转编码器的读取函数
 * 输入参数： 无
 * 输出参数：     pCnt   - 用于保存计数值
 *            pKey   - 用于保存按键状态(1-按键被按下, 0-按键被松开)
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/05	     V1.0	  韦东山	      创建
 ***********************************************************************/
void RotaryEncoder_Read(int32_t *pDiff, int32_t *pKey)
{
    *pDiff = g_count;
    g_count = 0;

    
    *pKey = RotaryEncoder_Get_Key();
}


