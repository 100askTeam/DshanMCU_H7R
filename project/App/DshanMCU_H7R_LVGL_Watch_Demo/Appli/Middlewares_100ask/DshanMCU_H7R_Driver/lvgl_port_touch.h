/*
 * lvgl_port_touch.h
 *
 *  Created on: Jul 2, 2024
 *      Author: biubiu
 */

#ifndef INC_LVGL_PORT_TOUCH_H_
#define INC_LVGL_PORT_TOUCH_H_

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lvgl.h"

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void
lvgl_touchscreen_init (void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* INC_LVGL_PORT_TOUCH_H_ */
