#include "lib.h"
#include "objects.h"

SV_Canvas canvas = {0};
bool update_required = true;

bool isnumber(char *num) {
  if (!num)
    return false;

  while (num && *num != '\0') {
    if (*num < '0' || *num > '9') {
      return false;
    }
    num++;
  }
  return true;
}

void SV_initialize_canvas(size_t width, size_t height, uint32_t fill) {
  canvas.width = width;
  canvas.height = height;
  canvas.pixels = malloc(width * height * sizeof(SV_Color));
  for (size_t i = 0; i < width * height; i++) {
    canvas.pixels[i].color = fill;
  }
}

uint32_t *SV_get_canvas() { return (uint32_t *)canvas.pixels; }
size_t SV_get_width() { return canvas.width; }
size_t SV_get_height() { return canvas.height; }
void SV_delete_canvas() { free(canvas.pixels); }

bool SV_update_required() { return update_required; }


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
