// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: C3 Watch Apps

#include "../ui.h"

#ifndef LV_ATTRIBUTE_MEM_ALIGN
    #define LV_ATTRIBUTE_MEM_ALIGN
#endif

// IMAGE DATA: assets/clock.png
const LV_ATTRIBUTE_MEM_ALIGN uint8_t ui_img_clock_png_data[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCD,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0x6E,0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,
0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xAE,0xFA,0xEF,0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4D,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0x30,0xFB,0xB2,0xFB,0x33,0xF4,0x33,0xF4,0xB2,0xFB,0x30,0xFB,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0x4D,0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0x71,0xFB,0x57,0xF5,0xBC,0xEE,0x7F,0xE7,0x7F,0xE7,0x5E,0xE7,0x5E,0xE7,0x7F,0xE7,0x7F,0xE7,0xBC,0xEE,0x37,0xF5,0x71,0xFB,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xAE,0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0x30,0xFB,0xB8,0xED,0x5E,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x57,0x9D,
0x57,0x9D,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x5E,0xE7,0x98,0xED,0x30,0xFB,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEF,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xF2,0xFB,0x1D,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x56,0x95,0x56,0x95,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x1D,0xE7,0x13,0xFC,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x70,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0x74,0xF4,0x5E,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x1D,0xD7,0x1D,0xD7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x5E,0xE7,0x74,0xF4,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xAE,0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xF2,0xFB,0x5E,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,
0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x5E,0xE7,0x13,0xFC,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0x00,0x00,0x00,0x00,0x00,0x00,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0x30,0xFB,0x3E,0xE7,0x7F,0xE7,0x7F,0xE7,0x3E,0xDF,0x5E,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x1D,0xE7,0x30,0xFB,0xCE,0xFA,0xCE,0xFA,0xAE,0xFA,0x00,0x00,
0x00,0x00,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xB8,0xED,0x7F,0xE7,0x7F,0xE7,0x3E,0xDF,0x2E,0x4B,0xD1,0x63,0x1D,0xD7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x98,0xED,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0x00,0x00,0x0E,0xFB,0xCE,0xFA,0xCE,0xFA,0x71,0xFB,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x5E,0xE7,0xD1,0x63,0xCD,0x42,0x6F,0x53,0xDC,0xCE,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,
0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7E,0xE7,0x71,0xFB,0xCE,0xFA,0xCE,0xFA,0x6E,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0x37,0xF5,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x5E,0xDF,0x32,0x74,0xCD,0x42,0x2E,0x4B,0x5A,0xBE,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x5E,0xE7,0x93,0x7C,0xB0,0x5B,0x5E,0xDF,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x17,0xF5,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,
0xAE,0xFA,0xCE,0xFA,0xCE,0xFA,0xDC,0xEE,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7E,0xE7,0xB4,0x84,0xCD,0x42,0xEE,0x42,0xF9,0xAD,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x5E,0xE7,0x73,0x74,0xCD,0x42,0x4F,0x53,0x5E,0xDF,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0xDC,0xEE,0xCE,0xFA,0xCE,0xFA,0xAE,0xFA,0xCE,0xFA,0xCE,0xFA,0x10,0xFB,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x16,0x8D,0xCD,0x42,0xED,0x42,0x77,0xA5,0x7F,0xE7,
0x7E,0xE7,0x73,0x7C,0xCD,0x42,0x4F,0x53,0xDC,0xCE,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x0F,0xFB,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xCE,0xFA,0xD2,0xFB,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x97,0xA5,0xCD,0x3A,0x4B,0x3A,0x13,0xD4,0xD1,0xCB,0x4B,0x32,0x0E,0x4B,0xBC,0xCE,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0xB2,0xFB,0xCE,0xFA,0xCE,0xFA,
0xCE,0xFA,0xCE,0xFA,0x54,0xF4,0x5E,0xE7,0x77,0x9D,0x56,0x9D,0x1D,0xD7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0xB8,0xA5,0x8D,0xA2,0xCE,0xFA,0xCE,0xFA,0xAD,0xAA,0x9B,0xC6,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x1D,0xD7,0x56,0x9D,0x77,0x9D,0x5E,0xE7,0x54,0xF4,0xCE,0xFA,0xAE,0xFA,0xAE,0xFA,0xCE,0xFA,0x34,0xF4,0x5E,0xE7,0x77,0x9D,0x57,0x9D,0x1D,0xD7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x33,0xE4,0x8D,0xEA,
0x8D,0xEA,0x33,0xDC,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x1D,0xD7,0x57,0x9D,0x77,0x9D,0x5E,0xE7,0x33,0xF4,0xCE,0xFA,0xAE,0xFA,0xAE,0xFA,0xCE,0xFA,0xF2,0xF3,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x3E,0xE7,0xB4,0xE4,0xB5,0xDC,0xDE,0x9E,0x3F,0xAF,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0xF2,0xF3,0xCE,0xFA,0xAE,0xFA,
0xAD,0xFA,0xCE,0xFA,0x30,0xFB,0x1D,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xDF,0x1F,0xA7,0x1F,0xA7,0x7F,0xDF,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x1D,0xE7,0x10,0xFB,0xCE,0xFA,0x8D,0xFA,0x8D,0xF2,0xCE,0xFA,0xCE,0xFA,0x5B,0xE6,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,
0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x3F,0xB7,0xFF,0x96,0x7F,0xDF,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x5B,0xE6,0xCE,0xFA,0xCE,0xFA,0x8D,0xF2,0x6C,0xEA,0xAE,0xFA,0xCE,0xFA,0x78,0xED,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x3F,0xBF,0xFF,0x96,0x5F,0xD7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x58,0xED,0xCE,0xFA,0xAE,0xFA,0x6C,0xEA,
0x4B,0xEA,0x8D,0xF2,0xCE,0xFA,0x71,0xFB,0xFD,0xDE,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x5F,0xCF,0xFF,0x8E,0x5F,0xD7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0xFD,0xDE,0x71,0xFB,0xCE,0xFA,0x8D,0xF2,0x4B,0xEA,0x00,0x00,0x6C,0xEA,0xAE,0xFA,0xCE,0xFA,0xFA,0xE5,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,
0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xDF,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x5F,0xE7,0xFA,0xE5,0xCE,0xFA,0xAE,0xFA,0x6C,0xEA,0x00,0x00,0x00,0x00,0x2C,0xE2,0x6C,0xEA,0xCE,0xFA,0x30,0xFB,0xDD,0xDE,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0xDD,0xDE,0x30,0xFB,0xCE,0xFA,0x6C,0xEA,0x6C,0xEA,0x00,0x00,
0x00,0x00,0x00,0x00,0x4C,0xEA,0xAD,0xF2,0xCE,0xFA,0x33,0xF4,0xFD,0xDE,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0xFD,0xDE,0x13,0xF4,0xCE,0xFA,0x8D,0xF2,0x6C,0xEA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0xDA,0x4B,0xEA,0xAE,0xFA,0xCE,0xFA,0xB5,0xEC,0xFE,0xDE,0x5F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x1D,0xD7,
0x1D,0xD7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x5F,0xE7,0xFE,0xDE,0x95,0xEC,0xCE,0xFA,0xAE,0xFA,0x4B,0xEA,0x4D,0xDA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2B,0xEA,0x4B,0xEA,0xAE,0xFA,0xCE,0xFA,0xF2,0xF3,0xDD,0xDE,0x3E,0xDF,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x56,0x95,0x56,0x95,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x7F,0xE7,0x3E,0xDF,0xDD,0xDE,0xF3,0xF3,0xCE,0xFA,0xAE,0xFA,0x4C,0xEA,0x4C,0xEA,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4B,0xE2,0x4B,0xEA,0x8D,0xF2,0xCE,0xFA,0x30,0xFB,0x98,0xE5,0xFD,0xD6,0xFE,0xDE,0x5E,0xDF,0x7F,0xE7,0x7F,0xE7,0x57,0x9D,0x57,0x9D,0x7F,0xE7,0x7F,0xE7,0x5E,0xDF,0xFE,0xDE,0xFD,0xD6,0x98,0xE5,0x30,0xFB,0xCE,0xFA,0x8D,0xF2,0x4B,0xEA,0x4B,0xEA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4C,0xEA,0x4B,0xE2,0x6C,0xEA,0xAE,0xFA,0xCE,0xFA,0x71,0xFB,0xF6,0xEC,0x5B,0xDE,0x1E,0xD7,0xFE,0xD6,0x9C,0xD6,
0x9C,0xD6,0xFE,0xD6,0x1E,0xD7,0x5B,0xDE,0xF6,0xEC,0x51,0xFB,0xCE,0xFA,0xAE,0xFA,0x6C,0xEA,0x4B,0xEA,0x4C,0xEA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4D,0xDA,0x2B,0xE2,0x4B,0xE2,0x6C,0xF2,0xAE,0xFA,0xCE,0xFA,0xCE,0xFA,0x10,0xFB,0x91,0xF3,0x13,0xF4,0x13,0xF4,0x91,0xF3,0x10,0xFB,0xCE,0xFA,0xCE,0xFA,0xAE,0xFA,0x6C,0xEA,0x4B,0xE2,0x4B,0xE2,0x4D,0xDA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4C,0xEA,0x4B,0xE2,0x4B,0xE2,0x4C,0xEA,0x6C,0xF2,0x8D,0xF2,0xAE,0xFA,0xAE,0xFA,0xAE,0xFA,0xAE,0xFA,0x8D,0xF2,0x6D,0xF2,0x4C,0xEA,0x4B,0xE2,0x4B,0xE2,0x4B,0xEA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0A,0xEA,0x4B,0xE2,0x4B,0xE2,0x4B,0xE2,0x4B,0xE2,0x4B,0xE2,
0x4B,0xE2,0x4B,0xE2,0x4B,0xE2,0x4B,0xE2,0x2B,0xE2,0x0A,0xEA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x59,0x9A,0xCA,0xEA,0xFA,0xFA,0xEA,0xCA,0x9A,0x59,0x0D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1A,0x97,0xF6,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF6,0x95,0x19,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x87,0xF5,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF5,0x85,0x07,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1A,0xC7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCC,0x1E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2E,0xE6,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE6,0x2D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x19,0xE1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE4,0x1C,0x00,0x00,0x00,
0x00,0x00,0x0A,0xCE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCB,0x09,0x00,0x00,0x00,0x00,0x81,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7C,0x00,0x00,0x00,0x1C,0xF4,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF5,0x1E,0x00,
0x00,0x9C,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x99,0x00,0x10,0xF5,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0x0D,0x59,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x54,
0x9B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x98,0xCB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC8,0xEA,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE8,
0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xF9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xEC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEA,
0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCD,0xAE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xAF,0x7C,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7B,
0x0E,0xE9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEB,0x0E,0x00,0xBA,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBB,0x00,0x00,0x28,0xEC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xED,0x25,0x00,
0x00,0x00,0x9F,0xFA,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0x9E,0x00,0x00,0x00,0x00,0x08,0xD2,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xD4,0x07,0x00,0x00,0x00,0x00,0x00,0x19,0xDE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE1,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x2E,0xE6,0xF5,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFA,0xE9,0x2D,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0xCE,0xEE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF1,0xD0,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x82,0xF4,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0xF9,0x89,0x07,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x98,0xF8,0xEE,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xEF,0xF8,0x9B,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x57,0x99,0xD2,0xF0,0xFB,0xFB,0xF0,0xD2,0x99,0x56,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

}; // LVGL_9 compatible
const lv_image_dsc_t ui_img_clock_png = {
    .header.magic = LV_IMAGE_HEADER_MAGIC,
    .header.w = 32,
    .header.h = 32,
    .data_size = sizeof(ui_img_clock_png_data),
    .header.cf = LV_COLOR_FORMAT_NATIVE_WITH_ALPHA,
    .data = ui_img_clock_png_data
};

