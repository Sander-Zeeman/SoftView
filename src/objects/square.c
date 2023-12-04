#include "square.h"

bool parse_Square(SV_Object_Square *obj) {
  char *x = strtok(NULL, " ");
  if (!isnumber(x)) {
    return false;
  }
  obj->x = atoi(x);

  char *y = strtok(NULL, " ");
  if (!isnumber(y)) {
    return false;
  }
  obj->y = atoi(y);

  char *w = strtok(NULL, " ");
  if (!isnumber(w)) {
    return false;
  }
  obj->w = atoi(w);

  return strtok(NULL, " ") == NULL;
}

void draw_Square(SV_Canvas *canvas, const SV_Object_Square *square) {
  size_t x = MAX(square->x, 0);
  size_t y = MAX(square->y, 0);
  size_t w = MIN(MIN(square->w, canvas->width - x), canvas->height - y);

  for (size_t cy = y; cy < y + w; cy++) {
    for (size_t cx = x; cx < x + w; cx++) {
      canvas->pixels[cy * canvas->width + cx] = (SV_Color){.color = 0xFFFFFFFF};
    }
  }
}
