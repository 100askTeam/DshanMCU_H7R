/*
 * rgb_lcd_init.c
 *
 *  Created on: Jul 5, 2024
 *      Author: biubiu
 */

#include "rgb_lcd_init.h"
#include "main.h"


#define spi_scl_1 HAL_GPIO_WritePin(RGB_LCD_INIT_SCK_PIN_GPIO_Port, RGB_LCD_INIT_SCK_PIN_Pin, GPIO_PIN_SET)
#define spi_scl_0 HAL_GPIO_WritePin(RGB_LCD_INIT_SCK_PIN_GPIO_Port, RGB_LCD_INIT_SCK_PIN_Pin, GPIO_PIN_RESET)
#define spi_sdi_1 HAL_GPIO_WritePin(RGB_LCD_INIT_SDA_PIN_GPIO_Port, RGB_LCD_INIT_SDA_PIN_Pin, GPIO_PIN_SET)
#define spi_sdi_0 HAL_GPIO_WritePin(RGB_LCD_INIT_SDA_PIN_GPIO_Port, RGB_LCD_INIT_SDA_PIN_Pin, GPIO_PIN_RESET)
#define spi_cs_1  HAL_GPIO_WritePin(RGB_LCD_INIT_CS_PIN_GPIO_Port,  RGB_LCD_INIT_CS_PIN_Pin, GPIO_PIN_SET)
#define spi_cs_0  HAL_GPIO_WritePin(RGB_LCD_INIT_CS_PIN_GPIO_Port,  RGB_LCD_INIT_CS_PIN_Pin, GPIO_PIN_RESET)
#define spi_rst_1 HAL_GPIO_WritePin(RGB_LCD_INIT_RESET_PIN_GPIO_Port, RGB_LCD_INIT_RESET_PIN_Pin, GPIO_PIN_SET)
#define spi_rst_0 HAL_GPIO_WritePin(RGB_LCD_INIT_RESET_PIN_GPIO_Port, RGB_LCD_INIT_RESET_PIN_Pin, GPIO_PIN_RESET)



static void rgb_lcd_init_delay_us(uint32_t udelay)
{
  __IO uint32_t Delay = udelay * 400 / 8;//(SystemCoreClock / 8U / 1000000U)

  do
  {
    __NOP();
  }
  while (Delay --);
}





static void rgb_lcd_init_3spi_write_cmd(uint32_t value)
{
	uint32_t i;
	spi_cs_0;
	spi_sdi_0;
	spi_scl_0;
	rgb_lcd_init_delay_us(10);
	spi_scl_1;
	for (i = 0; i < 8; i++) {
		rgb_lcd_init_delay_us(10);
		if (value & 0x80)
			spi_sdi_1;
		else
			spi_sdi_0;
		spi_scl_0;
		rgb_lcd_init_delay_us(10);
		spi_scl_1;
		value <<= 1;
	}
	rgb_lcd_init_delay_us(10);
	spi_cs_1;
}

static void rgb_lcd_init_3spi_write_data(uint32_t value)
{
	uint32_t i;
	spi_cs_0;
	spi_sdi_1;
	spi_scl_0;
	rgb_lcd_init_delay_us(10);
	spi_scl_1;
	for (i = 0; i < 8; i++) {
		rgb_lcd_init_delay_us(10);
		if (value & 0x80)
			spi_sdi_1;
		else
			spi_sdi_0;
		value <<= 1;
		spi_scl_0;
		rgb_lcd_init_delay_us(10);
		spi_scl_1;
	}
	rgb_lcd_init_delay_us(10);
	spi_cs_1;
}

void rgb_lcd_init(void)
{
	/* Reset Panel */
	spi_rst_0;
	HAL_Delay(120);
	spi_rst_1;
	HAL_Delay(120);

	rgb_lcd_init_3spi_write_cmd(0x11);
	HAL_Delay(20);

	/* Write init code */
	rgb_lcd_init_3spi_write_cmd(0xFF);
	rgb_lcd_init_3spi_write_data(0x77);
	rgb_lcd_init_3spi_write_data(0x01);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x10);

	rgb_lcd_init_3spi_write_cmd(0xC0);
	rgb_lcd_init_3spi_write_data(0x3B);
	rgb_lcd_init_3spi_write_data(0x00);

	rgb_lcd_init_3spi_write_cmd(0xC1);
	rgb_lcd_init_3spi_write_data(0x0D);
	rgb_lcd_init_3spi_write_data(0x02);

	rgb_lcd_init_3spi_write_cmd(0xC2);
	rgb_lcd_init_3spi_write_data(0x21);
	rgb_lcd_init_3spi_write_data(0x08);

	rgb_lcd_init_3spi_write_cmd(0xCD);
	rgb_lcd_init_3spi_write_data(0x18);

	rgb_lcd_init_3spi_write_cmd(0xB0);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x11);
	rgb_lcd_init_3spi_write_data(0x18);
	rgb_lcd_init_3spi_write_data(0x0E);
	rgb_lcd_init_3spi_write_data(0x11);
	rgb_lcd_init_3spi_write_data(0x06);
	rgb_lcd_init_3spi_write_data(0x07);
	rgb_lcd_init_3spi_write_data(0x08);
	rgb_lcd_init_3spi_write_data(0x07);
	rgb_lcd_init_3spi_write_data(0x22);
	rgb_lcd_init_3spi_write_data(0x04);
	rgb_lcd_init_3spi_write_data(0x12);
	rgb_lcd_init_3spi_write_data(0x0F);
	rgb_lcd_init_3spi_write_data(0xAA);
	rgb_lcd_init_3spi_write_data(0x31);
	rgb_lcd_init_3spi_write_data(0x18);

	rgb_lcd_init_3spi_write_cmd(0xB1);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x11);
	rgb_lcd_init_3spi_write_data(0x19);
	rgb_lcd_init_3spi_write_data(0x0E);
	rgb_lcd_init_3spi_write_data(0x12);
	rgb_lcd_init_3spi_write_data(0x07);
	rgb_lcd_init_3spi_write_data(0x08);
	rgb_lcd_init_3spi_write_data(0x08);
	rgb_lcd_init_3spi_write_data(0x08);
	rgb_lcd_init_3spi_write_data(0x22);
	rgb_lcd_init_3spi_write_data(0x04);
	rgb_lcd_init_3spi_write_data(0x11);
	rgb_lcd_init_3spi_write_data(0x11);
	rgb_lcd_init_3spi_write_data(0xA9);
	rgb_lcd_init_3spi_write_data(0x32);
	rgb_lcd_init_3spi_write_data(0x18);

	rgb_lcd_init_3spi_write_cmd(0xFF);
	rgb_lcd_init_3spi_write_data(0x77);
	rgb_lcd_init_3spi_write_data(0x01);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x11);

	rgb_lcd_init_3spi_write_cmd(0xB0);
	rgb_lcd_init_3spi_write_data(0x60);

	rgb_lcd_init_3spi_write_cmd(0xB1);
	rgb_lcd_init_3spi_write_data(0x30);

	rgb_lcd_init_3spi_write_cmd(0xB2);
	rgb_lcd_init_3spi_write_data(0x87);

	rgb_lcd_init_3spi_write_cmd(0xB3);
	rgb_lcd_init_3spi_write_data(0x80);

	rgb_lcd_init_3spi_write_cmd(0xB5);
	rgb_lcd_init_3spi_write_data(0x49);

	rgb_lcd_init_3spi_write_cmd(0xB7);
	rgb_lcd_init_3spi_write_data(0x85);

	rgb_lcd_init_3spi_write_cmd(0xB8);
	rgb_lcd_init_3spi_write_data(0x21);

	rgb_lcd_init_3spi_write_cmd(0xC1);
	rgb_lcd_init_3spi_write_data(0x78);

	rgb_lcd_init_3spi_write_cmd(0xC2);
	rgb_lcd_init_3spi_write_data(0x78);
	HAL_Delay(20);

	rgb_lcd_init_3spi_write_cmd(0xE0);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x1B);
	rgb_lcd_init_3spi_write_data(0x02);

	rgb_lcd_init_3spi_write_cmd(0xE1);
	rgb_lcd_init_3spi_write_data(0x08);
	rgb_lcd_init_3spi_write_data(0xA0);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x07);
	rgb_lcd_init_3spi_write_data(0xA0);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x44);
	rgb_lcd_init_3spi_write_data(0x44);

	rgb_lcd_init_3spi_write_cmd(0xE2);
	rgb_lcd_init_3spi_write_data(0x11);
	rgb_lcd_init_3spi_write_data(0x11);
	rgb_lcd_init_3spi_write_data(0x44);
	rgb_lcd_init_3spi_write_data(0x44);
	rgb_lcd_init_3spi_write_data(0xED);
	rgb_lcd_init_3spi_write_data(0xA0);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0xEC);
	rgb_lcd_init_3spi_write_data(0xA0);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x00);

	rgb_lcd_init_3spi_write_cmd(0xE3);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x11);
	rgb_lcd_init_3spi_write_data(0x11);

	rgb_lcd_init_3spi_write_cmd(0xE4);
	rgb_lcd_init_3spi_write_data(0x44);
	rgb_lcd_init_3spi_write_data(0x44);

	rgb_lcd_init_3spi_write_cmd(0xE5);
	rgb_lcd_init_3spi_write_data(0x0A);
	rgb_lcd_init_3spi_write_data(0xE9);
	rgb_lcd_init_3spi_write_data(0xD8);
	rgb_lcd_init_3spi_write_data(0xA0);
	rgb_lcd_init_3spi_write_data(0x0C);
	rgb_lcd_init_3spi_write_data(0xEB);
	rgb_lcd_init_3spi_write_data(0xD8);
	rgb_lcd_init_3spi_write_data(0xA0);
	rgb_lcd_init_3spi_write_data(0x0E);
	rgb_lcd_init_3spi_write_data(0xED);
	rgb_lcd_init_3spi_write_data(0xD8);
	rgb_lcd_init_3spi_write_data(0xA0);
	rgb_lcd_init_3spi_write_data(0x10);
	rgb_lcd_init_3spi_write_data(0xEF);
	rgb_lcd_init_3spi_write_data(0xD8);
	rgb_lcd_init_3spi_write_data(0xA0);

	rgb_lcd_init_3spi_write_cmd(0xE6);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x11);
	rgb_lcd_init_3spi_write_data(0x11);

	rgb_lcd_init_3spi_write_cmd(0xE7);
	rgb_lcd_init_3spi_write_data(0x44);
	rgb_lcd_init_3spi_write_data(0x44);

	rgb_lcd_init_3spi_write_cmd(0xE8);
	rgb_lcd_init_3spi_write_data(0x09);
	rgb_lcd_init_3spi_write_data(0xE8);
	rgb_lcd_init_3spi_write_data(0xD8);
	rgb_lcd_init_3spi_write_data(0xA0);
	rgb_lcd_init_3spi_write_data(0x0B);
	rgb_lcd_init_3spi_write_data(0xEA);
	rgb_lcd_init_3spi_write_data(0xD8);
	rgb_lcd_init_3spi_write_data(0xA0);
	rgb_lcd_init_3spi_write_data(0x0D);
	rgb_lcd_init_3spi_write_data(0xEC);
	rgb_lcd_init_3spi_write_data(0xD8);
	rgb_lcd_init_3spi_write_data(0xA0);
	rgb_lcd_init_3spi_write_data(0x0F);
	rgb_lcd_init_3spi_write_data(0xEE);
	rgb_lcd_init_3spi_write_data(0xD8);
	rgb_lcd_init_3spi_write_data(0xA0);

	rgb_lcd_init_3spi_write_cmd(0xEB);
	rgb_lcd_init_3spi_write_data(0x02);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0xE4);
	rgb_lcd_init_3spi_write_data(0xE4);
	rgb_lcd_init_3spi_write_data(0x88);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x40);

	rgb_lcd_init_3spi_write_cmd(0xEC);
	rgb_lcd_init_3spi_write_data(0x3C);
	rgb_lcd_init_3spi_write_data(0x00);

	rgb_lcd_init_3spi_write_cmd(0xED);
	rgb_lcd_init_3spi_write_data(0xAB);
	rgb_lcd_init_3spi_write_data(0x89);
	rgb_lcd_init_3spi_write_data(0x76);
	rgb_lcd_init_3spi_write_data(0x54);
	rgb_lcd_init_3spi_write_data(0x02);
	rgb_lcd_init_3spi_write_data(0xFF);
	rgb_lcd_init_3spi_write_data(0xFF);
	rgb_lcd_init_3spi_write_data(0xFF);
	rgb_lcd_init_3spi_write_data(0xFF);
	rgb_lcd_init_3spi_write_data(0xFF);
	rgb_lcd_init_3spi_write_data(0xFF);
	rgb_lcd_init_3spi_write_data(0x20);
	rgb_lcd_init_3spi_write_data(0x45);
	rgb_lcd_init_3spi_write_data(0x67);
	rgb_lcd_init_3spi_write_data(0x98);
	rgb_lcd_init_3spi_write_data(0xBA);

	rgb_lcd_init_3spi_write_cmd(0xFF);
	rgb_lcd_init_3spi_write_data(0x77);
	rgb_lcd_init_3spi_write_data(0x01);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x00);
	rgb_lcd_init_3spi_write_data(0x00);

	rgb_lcd_init_3spi_write_cmd(0x3A);  // Interface Pixel Format
	//rgb_lcd_init_3spi_write_data(0x56); // RGB565
	rgb_lcd_init_3spi_write_data(0x66); // RGB666
	//rgb_lcd_init_3spi_write_data(0x76); // RGB888

	rgb_lcd_init_3spi_write_cmd(0x36);
	rgb_lcd_init_3spi_write_data(0x00);

	rgb_lcd_init_3spi_write_cmd(0x21);

	rgb_lcd_init_3spi_write_cmd(0x11);
	HAL_Delay(120);

	rgb_lcd_init_3spi_write_cmd(0x29);
	HAL_Delay(20);
}


