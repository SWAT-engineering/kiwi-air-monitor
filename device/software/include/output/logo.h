#pragma once
#include <Arduino.h>
#include <U8g2lib.h>

#define KIWI_LOGO_WIDTH  113
#define KIWI_LOGO_HEIGHT 32

static const unsigned char KIWI_LOGO[] U8X8_PROGMEM = {
   0x00, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x3f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x7f,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xf8, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0xf8, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x38, 0x80, 0x80,
   0x07, 0x00, 0x00, 0x00, 0xf0, 0x01, 0xfc, 0xff, 0xff, 0xff, 0x0f, 0x00,
   0x38, 0xc0, 0x81, 0x07, 0x00, 0x00, 0x00, 0xf0, 0x01, 0xfe, 0xff, 0xff,
   0xff, 0x3f, 0x00, 0x38, 0xc0, 0x83, 0x07, 0x00, 0x00, 0x00, 0xf0, 0x01,
   0xfe, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x38, 0xe0, 0x01, 0x03, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x00, 0x38, 0xf0, 0x00,
   0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
   0x38, 0xf8, 0x00, 0x00, 0x0e, 0x1c, 0x78, 0x00, 0x00, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x01, 0x38, 0x7c, 0x00, 0x00, 0x0f, 0x1c, 0x78, 0x00, 0x00,
   0xff, 0xff, 0xff, 0xff, 0xfc, 0x01, 0x38, 0x3e, 0x80, 0x07, 0x0f, 0x1c,
   0x78, 0xe0, 0x00, 0xff, 0xff, 0xff, 0x7f, 0xf8, 0x01, 0x38, 0x1f, 0x80,
   0x07, 0x0f, 0x1c, 0x78, 0xe0, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x01,
   0xf8, 0x0f, 0x80, 0x07, 0x0f, 0x1c, 0x78, 0xe0, 0x00, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x01, 0xf8, 0x03, 0x80, 0x07, 0x0f, 0x1c, 0x78, 0xe0, 0x00,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xf8, 0x07, 0x80, 0x07, 0x0f, 0x1c,
   0x78, 0xe0, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x01, 0xf8, 0x0f, 0x80,
   0x07, 0x0f, 0x1c, 0x38, 0xe0, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x01,
   0x78, 0x1e, 0x80, 0x07, 0x0f, 0x1e, 0x38, 0xe0, 0x00, 0xfe, 0xff, 0xff,
   0xff, 0xff, 0x01, 0x78, 0x3c, 0x80, 0x07, 0x0f, 0x1e, 0x38, 0xe0, 0x00,
   0xfc, 0xff, 0xff, 0xff, 0x9f, 0x01, 0x78, 0x3c, 0x80, 0x07, 0x0f, 0x1e,
   0x38, 0xe0, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x8f, 0x01, 0x78, 0x78, 0x80,
   0x07, 0x0f, 0x1e, 0x38, 0xe0, 0x00, 0xf8, 0xff, 0xff, 0x07, 0x9c, 0x01,
   0x78, 0xf0, 0x80, 0x07, 0x0e, 0x1e, 0x3c, 0xf0, 0x00, 0xf0, 0xff, 0xff,
   0x00, 0x98, 0x01, 0x78, 0xf0, 0x80, 0x07, 0x1e, 0x3f, 0x1c, 0xf0, 0x00,
   0xe0, 0xff, 0x3f, 0x00, 0xf8, 0x01, 0x78, 0xe0, 0x81, 0x07, 0xfe, 0x7f,
   0x1e, 0xf0, 0x00, 0x80, 0xff, 0x1f, 0x00, 0xf0, 0x01, 0x78, 0xc0, 0x83,
   0x03, 0xfc, 0xf3, 0x0f, 0xf0, 0x00, 0x80, 0xff, 0x03, 0x00, 0xf0, 0x01,
   0x78, 0xc0, 0x83, 0x03, 0xf8, 0xe1, 0x07, 0xf0, 0x00, 0x80, 0x83, 0x03,
   0x00, 0xe0, 0x01, 0x70, 0x80, 0x80, 0x03, 0xf0, 0xc0, 0x03, 0xf0, 0x00,
   0x80, 0x83, 0x03, 0x00, 0xe0, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x80, 0x83, 0x03, 0x00, 0xc0, 0x01, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x83, 0x03, 0x00, 0xc0, 0x01,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x83, 0x03,
   0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };