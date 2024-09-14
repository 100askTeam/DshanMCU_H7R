/*
 * lvgl_port_display.h
 *
 *  Created on: Jun 24, 2024
 *      Author: biubiu
 */

#ifndef INC_LVGL_PORT_DISPLAY_H_
#define INC_LVGL_PORT_DISPLAY_H_


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"

/*********************
 *      DEFINES
 *********************/

#define MY_DISP_HOR_RES    LCD_W
#define MY_DISP_VER_RES    LCD_H

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lvgl_display_init (void);

#ifdef __cplusplus
} /*extern "C"*/
#endif



#endif /* INC_LVGL_PORT_DISPLAY_H_ */
