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


/*********************
 *      INCLUDES
 *********************/

#include <stdbool.h>

#include "main.h"
#include "driver_irq.h"
#include "driver_rotary_encoder.h"
#include "driver_ir_receiver.h"
#include "driver_key.h"

/*********************
 *      DEFINES
 *********************/


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/


/**********************
 *      MACROS
 **********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**********************************************************************
 * 函数名称： HAL_GPIO_EXTI_Callback
 * 功能描述： 外部中断的中断回调函数
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期：      版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2023/08/04	     V1.0	  韦东山	      创建
 ***********************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin)
    {
        case USER_KEY1_Pin:
        case USER_KEY2_Pin:
        case USER_KEY3_Pin:
        	Key_IRQ_Callback(GPIO_Pin);
            break;
        case ENCODER_S1_Pin:
        	RotaryEncoder_IRQ_Callback();
			break;
        case IR_REC_Pin:
        	IRReceiver_IRQ_Callback();
			break;

        default:
        	break;
    }
}


/**********************
 *   STATIC FUNCTIONS
 **********************/




