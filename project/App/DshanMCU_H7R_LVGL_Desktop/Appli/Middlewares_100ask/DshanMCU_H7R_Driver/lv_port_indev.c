/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include <string.h>

#include "lv_port_indev.h"

#include "gt9xx.h"

#include "driver_key.h"
#include "driver_rotary_encoder.h"
#include "driver_ir_receiver.h"

#include "driver_passive_buzzer.h"

#include "lv_100ask_generic_ui_conf.h"

#if LV_100ASK_GENERIC_UI_HAS_LOCK_SCREEN
#include "lv_100ask_generic_ui.h"
#endif

/*********************
 *      DEFINES
 *********************/
#define LV_INDEV_TYPE_BUTTON_TEST 					1
#define LV_INDEV_TYPE_BUTTON_TEST_USE_INTERRUPT		1

#define LV_INDEV_TYPE_ENCODER_TEST 					1
#define LV_INDEV_TYPE_KEYPAD_TEST 					1
#define LV_INDEV_TYPE_ENCODER_KEY_SIM_TEST 			1


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void touchpad_init(void);
static void touchpad_read(lv_indev_t * indev, lv_indev_data_t * data);
static bool touchpad_is_pressed(void);
static void touchpad_get_xy(int32_t * x, int32_t * y);

static void mouse_init(void);
static void mouse_read(lv_indev_t * indev, lv_indev_data_t * data);
static bool mouse_is_pressed(void);
static void mouse_get_xy(int32_t * x, int32_t * y);

static void keypad_init(void);
static void keypad_read(lv_indev_t * indev, lv_indev_data_t * data);
static uint32_t keypad_get_key(void);

static void encoder_init(void);
static void encoder_read(lv_indev_t * indev, lv_indev_data_t * data);
static void encoder_handler(void);
static void encoder_key_sim_read(lv_indev_t * indev_drv, lv_indev_data_t * data);

static void button_init(void);
static void button_read(lv_indev_t * indev, lv_indev_data_t * data);
static int8_t button_get_pressed_id(void);
static bool button_is_pressed(uint8_t id);

static void click_check_timer(lv_timer_t * timer);

/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_touchpad;
lv_indev_t * indev_mouse;
lv_indev_t * indev_keypad;
lv_indev_t * indev_encoder;
lv_indev_t * indev_button;

static int32_t encoder_diff;
static lv_indev_state_t encoder_state;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{

    /**
     * Here you will find example implementation of input devices supported by LittelvGL:
     *  - Touchpad
     *  - Mouse (with cursor support)
     *  - Keypad (supports GUI usage only with key)
     *  - Encoder (supports GUI usage only with: left, right, push)
     *  - Button (external buttons to press points on the screen)
     *
     *  The `..._read()` function are only examples.
     *  You should shape them according to your hardware
     */

    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad if you have*/
    touchpad_init();

    /*Register a touchpad input device*/
    indev_touchpad = lv_indev_create();
    lv_indev_set_type(indev_touchpad, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touchpad, touchpad_read);

#if LV_INDEV_TYPE_ENCODER_KEY_SIM_TEST == 0
#if LV_INDEV_TYPE_BUTTON_TEST == 1
    /*------------------
     * Button
     * -----------------*/

    /*Initialize your button if you have*/
    button_init();

    /*Register a button input device*/
    indev_button = lv_indev_create();
    lv_indev_set_type(indev_button, LV_INDEV_TYPE_BUTTON);
    lv_indev_set_read_cb(indev_button, button_read);

    /*Assign buttons to points on the screen*/
    static const lv_point_t btn_points[MY_KEY_SUM + 1] = {
		{80, 10},   /*Button 0 ->  x:80;  y:10*/
		{240, 10},  /*Button 1 ->  x:240; y:10*/
		{400, 10},  /*Button 2 ->  x:400; y:10*/
		{240, 10},  /*Button 3 ->  x:240; y:10*/ // just test
	};
    lv_indev_set_button_points(indev_button, btn_points);
#endif
#endif

#if LV_INDEV_TYPE_ENCODER_KEY_SIM_TEST == 0
#if LV_INDEV_TYPE_ENCODER_TEST == 1
    /*------------------
     * Encoder
     * -----------------*/

    /*Initialize your encoder if you have*/
    encoder_init();

    /*Register a encoder input device*/
    indev_encoder = lv_indev_create();
    lv_indev_set_type(indev_encoder, LV_INDEV_TYPE_ENCODER);
    lv_indev_set_read_cb(indev_encoder, encoder_read);
#endif
#else
    /*------------------
     * Encoder
     * -----------------*/

    /*Initialize your encoder if you have*/
    encoder_init();

    /*Register a encoder input device*/
    indev_encoder = lv_indev_create();
    lv_indev_set_type(indev_encoder, LV_INDEV_TYPE_ENCODER);
    lv_indev_set_read_cb(indev_encoder, encoder_key_sim_read);
#endif

#if LV_INDEV_TYPE_KEYPAD_TEST == 1
    /*------------------
     * Keypad
     * -----------------*/

    /*Initialize your keypad or keyboard if you have*/
    keypad_init();

    /*Register a keypad input device*/
    indev_keypad = lv_indev_create();
    lv_indev_set_type(indev_keypad, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev_keypad, keypad_read);
#endif


#if 0
    /*------------------
     * Mouse
     * -----------------*/

    /*Initialize your mouse if you have*/
    mouse_init();

    /*Register a mouse input device*/
    indev_mouse = lv_indev_create();
    lv_indev_set_type(indev_mouse, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_mouse, mouse_read);

    /*Set cursor. For simplicity set a HOME symbol now.*/
    lv_obj_t * mouse_cursor = lv_image_create(lv_screen_active());
    lv_image_set_src(mouse_cursor, LV_SYMBOL_HOME);
    lv_indev_set_cursor(indev_mouse, mouse_cursor);


    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_keypad, group);`*/

#endif
    // 重要，创建组
	lv_group_t * group = lv_group_create();
	lv_group_set_default(group);

#if LV_INDEV_TYPE_ENCODER_TEST == 1
	lv_indev_set_group(indev_encoder, group);
#endif

#if LV_INDEV_TYPE_KEYPAD_TEST == 1
	lv_indev_set_group(indev_keypad, group);
#endif

	lv_timer_create(click_check_timer, 30, NULL);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Touchpad
 * -----------------*/

/*Initialize your touchpad*/
static void touchpad_init(void)
{
    /*Your code comes here*/
	drv_i2c_touchpad_init();
}

/*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
	HAL_StatusTypeDef err;

    static int32_t last_x = 0;
    static int32_t last_y = 0;


    /*Save the pressed coordinates and the state*/
    err = touchpad_is_touched();
    if(HAL_OK == err) {
    	touchpad_get_pos(&last_x, &last_y, 0);
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else {
        data->state = LV_INDEV_STATE_RELEASED;
    }

    /*Set the last pressed coordinates*/
    data->point.x = last_x;
    data->point.y = last_y;
}

/*Return true is the touchpad is pressed*/
static bool touchpad_is_pressed(void)
{
    /*Your code comes here*/

    return false;
}

/*Get the x and y coordinates if the touchpad is pressed*/
static void touchpad_get_xy(int32_t * x, int32_t * y)
{
    /*Your code comes here*/

    (*x) = 0;
    (*y) = 0;
}

/*------------------
 * Mouse
 * -----------------*/

/*Initialize your mouse*/
static void mouse_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the mouse*/
static void mouse_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
    /*Get the current x and y coordinates*/
    mouse_get_xy(&data->point.x, &data->point.y);

    /*Get whether the mouse button is pressed or released*/
    if(mouse_is_pressed()) {
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

/*Return true is the mouse button is pressed*/
static bool mouse_is_pressed(void)
{
    /*Your code comes here*/

    return false;
}

/*Get the x and y coordinates if the mouse is pressed*/
static void mouse_get_xy(int32_t * x, int32_t * y)
{
    /*Your code comes here*/

    (*x) = 0;
    (*y) = 0;
}

/*------------------
 * Keypad
 * -----------------*/

/*Initialize your keypad*/
static void keypad_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the mouse*/
static void keypad_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
#if 0
    static uint32_t last_key = 0;

    /*Get the current x and y coordinates*/
    mouse_get_xy(&data->point.x, &data->point.y);

    /*Get whether the a key is pressed and save the pressed key*/
    uint32_t act_key = keypad_get_key();
    if(act_key != 0) {
        data->state = LV_INDEV_STATE_PRESSED;

        /*Translate the keys to LVGL control characters according to your key definitions*/
        switch(act_key) {
            case 1:
                act_key = LV_KEY_NEXT;
                break;
            case 2:
                act_key = LV_KEY_PREV;
                break;
            case 3:
                act_key = LV_KEY_LEFT;
                break;
            case 4:
                act_key = LV_KEY_RIGHT;
                break;
            case 5:
                act_key = LV_KEY_ENTER;
                break;
        }

        last_key = act_key;
    }
    else {
        data->state = LV_INDEV_STATE_RELEASED;
    }

    data->key = last_key;
#else
    static uint32_t last_key = 0;
    uint32_t act_key = 0;

    /*Get the current x and y coordinates*/
    //mouse_get_xy(&data->point.x, &data->point.y);

    /*Get whether the a key is pressed and save the pressed key*/
    //uint32_t act_key = keypad_get_key();
    int has_key;
    const char * ir_key_str;
    uint8_t ir_dev, ir_data;
    has_key = IRReceiver_Read(&ir_dev, &ir_data);
    if(has_key == 0) {
        data->state = LV_INDEV_STATE_PRESSED;

        ir_key_str = IRReceiver_CodeToString(ir_data);
        /*Translate the keys to LVGL control characters according to your key definitions*/
        if	   (strcmp(ir_key_str, "+")     == 0)	act_key = LV_KEY_UP;
        else if(strcmp(ir_key_str, "-")     == 0)	act_key = LV_KEY_DOWN;
        else if(strcmp(ir_key_str, "Left")  == 0)	act_key = LV_KEY_PREV;
        else if(strcmp(ir_key_str, "Right") == 0)	act_key = LV_KEY_NEXT;
        else if(strcmp(ir_key_str, "Play")  == 0)	act_key = LV_KEY_ENTER;

        else if(strcmp(ir_key_str, "Power") == 0)	act_key = LV_KEY_ESC;
        else if(strcmp(ir_key_str, "Menu")  == 0)	act_key = LV_KEY_HOME;
        else if(strcmp(ir_key_str, "Test")  == 0)	act_key = LV_KEY_BACKSPACE;
        else if(strcmp(ir_key_str, "Return")== 0)	act_key = LV_KEY_DEL;
        else if(strcmp(ir_key_str, "0")     == 0)	act_key = LV_KEY_LEFT;
        else if(strcmp(ir_key_str, "c")     == 0)	act_key = LV_KEY_RIGHT;
        else if(strcmp(ir_key_str, "1")     == 0)	act_key = LV_KEY_END;

        last_key = act_key;
    }
    else {
        data->state = LV_INDEV_STATE_RELEASED;
    }

    data->key = last_key;
#endif
}

/*Get the currently being pressed key.  0 if no key is pressed*/
static uint32_t keypad_get_key(void)
{
    /*Your code comes here*/

    return 0;
}

/*------------------
 * Encoder
 * -----------------*/

/*Initialize your encoder*/
static void encoder_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the encoder*/
static void encoder_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{

	int32_t diff;
	int32_t key;

	RotaryEncoder_Read(&diff, &key);

	if(diff < 0)
	{
		encoder_diff += 1;
		encoder_state = LV_INDEV_STATE_RELEASED;
	}
	else if(diff > 0)
	{
		encoder_diff -= 1;
		encoder_state = LV_INDEV_STATE_RELEASED;
	}
	else if(key == 0)
	{
		encoder_diff = 0;
		encoder_state = LV_INDEV_STATE_RELEASED;
	}
	else if(key == 1)
	{
		encoder_diff = 0;
		encoder_state = LV_INDEV_STATE_PRESSED;
	}

    data->enc_diff = encoder_diff;
    data->state = encoder_state;
}

/*Call this function in an interrupt to process encoder events (turn, press)*/
static void encoder_handler(void)
{
    /*Your code comes here*/

    encoder_diff += 0;
    encoder_state = LV_INDEV_STATE_RELEASED;
}

static void encoder_key_sim_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
	int8_t btn_act = button_get_pressed_id();

    switch (btn_act)
    {
        case 0:
            encoder_diff -= 1;
            encoder_state = LV_INDEV_STATE_RELEASED;
            break;
        case 1:
            encoder_diff = 0;
		    encoder_state = LV_INDEV_STATE_PRESSED;
            break;
        case 2:
            encoder_diff += 1;
            encoder_state = LV_INDEV_STATE_RELEASED;
            break;
        default:
            encoder_diff = 0;
            encoder_state = LV_INDEV_STATE_RELEASED;
            break;
    }

    data->enc_diff = encoder_diff;
    data->state = encoder_state;
}

/*------------------
 * Button
 * -----------------*/

/*Initialize your buttons*/
static void button_init(void)
{
    /*Your code comes here*/
}

/*Will be called by the library to read the button*/
static void button_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{

    static uint8_t last_btn = 0;

    /*Get the pressed button's ID*/
    int8_t btn_act = button_get_pressed_id();

    if(btn_act >= 0) {
        data->state = LV_INDEV_STATE_PRESSED;
        last_btn = btn_act;
    }
    else {
    	if(HAL_GPIO_ReadPin(USER_KEY4_GPIO_Port, USER_KEY4_Pin) == GPIO_PIN_RESET)
		{
			//data->state = LV_INDEV_STATE_PRESSED;
			//last_btn = MY_KEY_SUM;
		}
		else	data->state = LV_INDEV_STATE_RELEASED;
    }

    /*Save the last pressed button's ID*/
    data->btn_id = last_btn;
}

/*Get ID  (0, 1, 2 ..) of the pressed button*/
static int8_t button_get_pressed_id(void)
{

#if LV_INDEV_TYPE_BUTTON_TEST_USE_INTERRUPT == 1
    int8_t i;

    /*Check to buttons see which is being pressed (assume there are 2 buttons)*/
    for(i = 0; i < MY_KEY_SUM; i++) {
        /*Return the pressed button's ID*/
        if(button_is_pressed(i)) {
            return i;
        }
    }

    /*No button pressed*/
    return -1;
#else
    int8_t res = -1;

    if	   (HAL_GPIO_ReadPin(USER_KEY1_GPIO_Port, USER_KEY1_Pin) == GPIO_PIN_RESET)	res = 0;
    else if(HAL_GPIO_ReadPin(USER_KEY2_GPIO_Port, USER_KEY2_Pin) == GPIO_PIN_RESET)	res = 1;
    else if(HAL_GPIO_ReadPin(USER_KEY3_GPIO_Port, USER_KEY3_Pin) == GPIO_PIN_RESET)	res = 2;
    else if(HAL_GPIO_ReadPin(USER_KEY4_GPIO_Port, USER_KEY4_Pin) == GPIO_PIN_RESET)	res = 3;

	/*No button pressed*/
	return res;
#endif
}

/*Test if `id` button is pressed or not*/
static bool button_is_pressed(uint8_t id)
{

    /*Your code comes here*/

    return key_is_pressed(id);
}


static void click_check_timer(lv_timer_t * timer)
{
    static uint8_t buzzer_state = 0;
    lv_indev_state_t indev_state = LV_INDEV_STATE_RELEASED;

    lv_indev_t * i = lv_indev_get_next(NULL);
    if(i == NULL)  return;

	while(i) {
		indev_state = lv_indev_get_state(i);
		if(indev_state == LV_INDEV_STATE_PRESSED) break;

		if((lv_indev_get_type(i) == LV_INDEV_TYPE_ENCODER) && (encoder_diff != 0))
		{
			indev_state = LV_INDEV_STATE_PRESSED;
			break;
		}

		i = lv_indev_get_next(i);
	}


    if(indev_state == LV_INDEV_STATE_PRESSED)
    {
        if(buzzer_state == 0)
        {
            buzzer_state = 1;
            PassiveBuzzer_Control(1);
        }
        else PassiveBuzzer_Control(0);

#if LV_100ASK_GENERIC_UI_HAS_LOCK_SCREEN
        set_page_lock_screen_reset();
#endif

    }
    else if(indev_state == LV_INDEV_STATE_RELEASED)
    {
        if(buzzer_state)
        {
            buzzer_state = 0;
            PassiveBuzzer_Control(0);
        }
    }
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
