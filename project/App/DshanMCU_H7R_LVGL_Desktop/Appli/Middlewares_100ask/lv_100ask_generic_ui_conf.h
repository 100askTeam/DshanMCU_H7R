/**
 * @file lv_100ask_generic_ui_conf.h
 * Configuration file for v9.2.0
 *
 */
/*
 * COPY THIS FILE AS lv_100ask_generic_ui_conf.h
 */

/* clang-format off */
#if 1 /*Set it to "1" to enable the content*/

#ifndef LV_100ASK_GENERIC_UI_CONF_H
#define LV_100ASK_GENERIC_UI_CONF_H

#include "lv_lib_100ask/lv_lib_100ask.h"

/*******************
 * GENERAL SETTING
 *******************/
/* platform */
#define LV_100ASK_GENERIC_UI_USE_SIMULATOR           0
#define LV_100ASK_GENERIC_UI_DshanMCUH7R_NoRTOS      1

/* screen size */
#define LV_100ASK_GENERIC_UI_SCREEN_SIZE_320X480     0
#define LV_100ASK_GENERIC_UI_SCREEN_SIZE_480X480     1
#define LV_100ASK_GENERIC_UI_SCREEN_SIZE_1024X600    0

/* app */
#define LV_100ASK_GENERIC_UI_NO_BUILTIN_APP          1

#if LV_100ASK_GENERIC_UI_NO_BUILTIN_APP == 1
#define LV_100ASK_GENERIC_UI_USE_APP_2048            1
#define LV_100ASK_GENERIC_UI_USE_APP_CALC            1

/*Requires: LV_USE_FILE_EXPLORER*/
#define LV_100ASK_GENERIC_UI_USE_APP_FILE_EXPLORER   1
#if LV_100ASK_GENERIC_UI_USE_APP_FILE_EXPLORER == 1
#define LV_100ASK_GENERIC_UI_USE_APP_FILE_EXPLORER_DIR "0:" /* 注意 LV_FS_FATFS_LETTER 的配置是否一致 */
#endif

#define LV_100ASK_GENERIC_UI_USE_APP_HARDWARE_TEST   1
#define LV_100ASK_GENERIC_UI_USE_APP_MEMORY_GAME     1
#define LV_100ASK_GENERIC_UI_USE_APP_SETTING         1
#define LV_100ASK_GENERIC_UI_USE_APP_SKETCHPAD       1
#define LV_100ASK_GENERIC_UI_USE_APP_SNAKE           1
#endif

/* other */
#define LV_100ASK_GENERIC_UI_HAS_DESKTOP_BG          1
#if LV_100ASK_GENERIC_UI_HAS_DESKTOP_BG
#define LV_100ASK_GENERIC_UI_LIMIT_DESKTOP_BG_PIC    0
#endif

#define LV_100ASK_GENERIC_UI_HAS_LOCK_SCREEN         1
#if LV_100ASK_GENERIC_UI_HAS_LOCK_SCREEN
#define LV_100ASK_GENERIC_UI_LIMIT_LOCK_SCREEN_PIC   0
#endif

#define LV_100ASK_GENERIC_UI_HAS_SCREEN_ROTATION     1

#define LV_100ASK_GENERIC_UI_LCD_MAX_BACKLIGHT              1000
#define LV_100ASK_GENERIC_UI_LCD_MIN_BACKLIGHT              200
#define LV_100ASK_GENERIC_UI_LCD_LOCK_SCREEN_BACKLIGHT      500

#endif /*LV_100ASK_GENERIC_UI_CONF_H*/

#endif /*End of "Content enable"*/

