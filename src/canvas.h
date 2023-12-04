#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "../include/SoftView.h"

typedef union {
  uint32_t color;
  uint8_t rgba[4];
} SV_Color;

typedef struct SV_Canvas {
  SV_Color *pixels;
  size_t width;
  size_t height;
} SV_Canvas;

extern SV_Canvas canvas;
extern bool update_required;

uint32_t *SV_get_canvas();
size_t SV_get_width();
size_t SV_get_height();
void SV_delete_canvas();
