
// File generated by bin2lvgl
// developed by fbiego. 
// https://github.com/fbiego
// Watchface: 1169

#ifndef _FACE_1169_H
#define _FACE_1169_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "lvgl.h"
#include "app_hal.h"

//#define ENABLE_FACE_1169 // (1169) uncomment to enable or define it elsewhere

#ifdef ENABLE_FACE_1169
    extern lv_obj_t *face_1169;
	extern lv_obj_t *face_1169_0_144;
	extern lv_obj_t *face_1169_1_69774;
	extern lv_obj_t *face_1169_2_69774;
	extern lv_obj_t *face_1169_3_129032;
	extern lv_obj_t *face_1169_4_74398;
	extern lv_obj_t *face_1169_5_74398;
	extern lv_obj_t *face_1169_6_129032;


	LV_IMG_DECLARE(face_1169_dial_img_0_144_0);
	LV_IMG_DECLARE(face_1169_dial_img_1_69774_0);
	LV_IMG_DECLARE(face_1169_dial_img_1_69774_1);
	LV_IMG_DECLARE(face_1169_dial_img_1_69774_2);
	LV_IMG_DECLARE(face_1169_dial_img_1_69774_3);
	LV_IMG_DECLARE(face_1169_dial_img_1_69774_4);
	LV_IMG_DECLARE(face_1169_dial_img_1_69774_5);
	LV_IMG_DECLARE(face_1169_dial_img_1_69774_6);
	LV_IMG_DECLARE(face_1169_dial_img_1_69774_7);
	LV_IMG_DECLARE(face_1169_dial_img_1_69774_8);
	LV_IMG_DECLARE(face_1169_dial_img_1_69774_9);
	LV_IMG_DECLARE(face_1169_dial_img_3_129032_0);
	LV_IMG_DECLARE(face_1169_dial_img_3_129032_1);
	LV_IMG_DECLARE(face_1169_dial_img_3_129032_2);
	LV_IMG_DECLARE(face_1169_dial_img_3_129032_3);
	LV_IMG_DECLARE(face_1169_dial_img_3_129032_4);
	LV_IMG_DECLARE(face_1169_dial_img_3_129032_5);
	LV_IMG_DECLARE(face_1169_dial_img_3_129032_6);
	LV_IMG_DECLARE(face_1169_dial_img_3_129032_7);
	LV_IMG_DECLARE(face_1169_dial_img_3_129032_8);
	LV_IMG_DECLARE(face_1169_dial_img_3_129032_9);
	LV_IMG_DECLARE(face_1169_dial_img_4_74398_0);
	LV_IMG_DECLARE(face_1169_dial_img_4_74398_1);
	LV_IMG_DECLARE(face_1169_dial_img_4_74398_2);
	LV_IMG_DECLARE(face_1169_dial_img_4_74398_3);
	LV_IMG_DECLARE(face_1169_dial_img_4_74398_4);
	LV_IMG_DECLARE(face_1169_dial_img_4_74398_5);
	LV_IMG_DECLARE(face_1169_dial_img_4_74398_6);
	LV_IMG_DECLARE(face_1169_dial_img_4_74398_7);
	LV_IMG_DECLARE(face_1169_dial_img_4_74398_8);
	LV_IMG_DECLARE(face_1169_dial_img_4_74398_9);
	LV_IMG_DECLARE(face_1169_dial_img_preview_0);
	LV_IMG_DECLARE(face_1169_dial_img_preview_0);


#endif
    void onFaceEvent(lv_event_t * e);

    void init_face_1169(void (*callback)(const char*, const lv_img_dsc_t *, lv_obj_t **, lv_obj_t **));
    void update_time_1169(int second, int minute, int hour, bool mode, bool am, int day, int month, int year, int weekday);
    void update_weather_1169(int temp, int icon);
    void update_status_1169(int battery, bool connection);
    void update_activity_1169(int steps, int distance, int kcal);
    void update_health_1169(int bpm, int oxygen);
    void update_all_1169(int second, int minute, int hour, bool mode, bool am, int day, int month, int year, int weekday, 
                int temp, int icon, int battery, bool connection, int steps, int distance, int kcal, int bpm, int oxygen);
    void update_check_1169(lv_obj_t *root, int second, int minute, int hour, bool mode, bool am, int day, int month, int year, int weekday, 
                int temp, int icon, int battery, bool connection, int steps, int distance, int kcal, int bpm, int oxygen);


#ifdef __cplusplus
}
#endif

#endif
