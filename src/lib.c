#include "../include/SoftView.h"

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "canvas.h"
#include "objects/objects.h"

SV_Canvas canvas = {0};
bool update_required = true;

#define PARSE_SHAPE(shape) \
  else if (strcmp(command, #shape) == 0) { \
    obj.type = SV_##shape; \
    if (!parse_##shape(&obj.params.shape)) \
      goto error; \
  }


SV_Object parse_command(char *input) {
  SV_Object obj = {0};

  char *command = strtok(input, " ");
  if (strcmp(command, "exit") == 0) {
    obj.type = SV_EXIT;
  }
  PARSE_SHAPE(Rectangle)
  PARSE_SHAPE(Square)
  else {
error:
    obj.type = SV_INVALID;
  }
  return obj;
}


#define HANDLE_SHAPE(shape) \
  case SV_##shape: { \
    draw_##shape(&canvas, &obj.params.shape); \
    break; \
  }

bool SV_handle_command(char command[], char response[], bool *exit) {
  SV_Object obj = parse_command(command);

  switch (obj.type) {
  case SV_EXIT: {
    *exit = true;
    strcpy(response, "Goodbye.\n");
    break;
  }
  HANDLE_SHAPE(Rectangle)
  HANDLE_SHAPE(Square)
  case SV_INVALID: {
    strcpy(response, "Invalid syntax.\n");
    return false;
  }
  default: {
  }
  }

  return true;
}