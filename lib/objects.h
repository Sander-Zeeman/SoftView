#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

typedef struct {
  size_t x;
  size_t y;
  size_t w;
  size_t h;
} SV_Object_Rectangle;
bool parse_Rectangle(SV_Object_Rectangle *obj);
void draw_Rectangle(SV_Canvas *canvas, const SV_Object_Rectangle *rect);

typedef struct {
  size_t x;
  size_t y;
  size_t w;
} SV_Object_Square;
bool parse_Square(SV_Object_Square *obj);
void draw_Square(SV_Canvas *canvas, const SV_Object_Square *rect);

typedef enum {
  SV_Rectangle,
  SV_Square,
  SV_EXIT,
  SV_INVALID,
} SV_Object_Type;

typedef union {
  SV_Object_Rectangle Rectangle;
  SV_Object_Square Square;
} SV_Object_Params;

typedef struct {
  SV_Object_Type type;
  SV_Object_Params params;
} SV_Object;
