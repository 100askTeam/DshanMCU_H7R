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

#include "driver_aht20.h"

extern I2C_HandleTypeDef hi2c1;

static uint32_t g_temp, g_humi;

//CRC校验类型： CRC8
//多项式： X8+X5+X4+1
//Poly:0011 0001 0x31
static unsigned char Calc_CRC8(unsigned char *message,unsigned char Num)
{
    unsigned char i;
    unsigned char byte;
    unsigned char crc =0xFF;
    for (byte = 0;byte<Num;byte++)
    {
        crc^=(message[byte]);
        for(i=8;i>0;--i)
        {
            if(crc&0x80)
                crc=(crc<<1)^0x31;
            else
                crc=(crc<<1);
        }
    }
    return crc;
}


void aht20_update(void)
{
	uint8_t cmd[] = { 0xAC, 0x33, 0x00};
	uint8_t datas[7];
	uint8_t crc;

	if (HAL_OK == HAL_I2C_Master_Transmit(&hi2c1, 0x70, cmd, 3, 100))
	{
		HAL_Delay(70); /* wait for ready */
		if (HAL_OK == HAL_I2C_Master_Receive(&hi2c1, 0x70, datas, 7, 100))
		{
			/* cal crc */
			crc = Calc_CRC8(datas, 6);
			if (crc == datas[6])
			{
				/* ok */
				g_humi = ((uint32_t)datas[1] << 12) | ((uint32_t)datas[2] << 4) | ((uint32_t)datas[3] >> 4);
				g_temp = (((uint32_t)datas[3] & 0x0f) << 16) | ((uint32_t)datas[4] << 8) | ((uint32_t)datas[5]);

				g_humi = g_humi * 100 * 10/ 0x100000; /* 0.1% */
				g_temp = g_temp * 200 * 10/ 0x100000 - 500; /* 0.1C */
			}
		}
	}
}


void aht20_get_datas(uint32_t *temp, uint32_t *humi)
{
	*temp = g_temp;
	*humi = g_humi;
}
