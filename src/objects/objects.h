#pragma once
#include "rectangle.h"
#include "square.h"

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
