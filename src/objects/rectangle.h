#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../canvas.h"
#include "../helper.h"

typedef struct {
  size_t x;
  size_t y;
  size_t w;
  size_t h;
} SV_Object_Rectangle;

bool parse_Rectangle(SV_Object_Rectangle *obj);
void draw_Rectangle(SV_Canvas *canvas, const SV_Object_Rectangle *rect);
