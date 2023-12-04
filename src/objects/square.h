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
} SV_Object_Square;

bool parse_Square(SV_Object_Square *obj);
void draw_Square(SV_Canvas *canvas, const SV_Object_Square *rect);
