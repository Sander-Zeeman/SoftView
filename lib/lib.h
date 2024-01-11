#pragma once

#include "../modifier.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define MAX(a, b) (a) > (b) ? (a) : (b)

typedef union {
  uint32_t color;
  uint8_t rgba[4];
} SV_Color;

typedef struct SV_Canvas {
  SV_Color *pixels;
  size_t width;
  size_t height;
} SV_Canvas;

bool isnumber(char *num);

SOV_FUNCTION void SV_initialize_canvas(size_t width, size_t height, uint32_t fill);
SOV_FUNCTION uint32_t *SV_get_canvas();
SOV_FUNCTION size_t SV_get_width();
SOV_FUNCTION size_t SV_get_height();
SOV_FUNCTION void SV_delete_canvas();
SOV_FUNCTION bool SV_update_required();
SOV_FUNCTION bool SV_handle_command(char command[], char response[], bool *exit);