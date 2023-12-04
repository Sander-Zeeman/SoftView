#include "rectangle.h"

bool parse_Rectangle(SV_Object_Rectangle *obj) {
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

  char *h = strtok(NULL, " ");
  if (!isnumber(h)) {
    return false;
  }
  obj->h = atoi(h);

  return strtok(NULL, " ") == NULL;
}

void draw_Rectangle(SV_Canvas *canvas, const SV_Object_Rectangle *rect) {
  size_t x = MAX(rect->x, 0);
  size_t y = MAX(rect->y, 0);
  size_t w = MIN(rect->w, canvas->width - x);
  size_t h = MIN(rect->h, canvas->height - y);

  for (size_t cy = y; cy < y + h; cy++) {
    for (size_t cx = x; cx < x + w; cx++) {
      canvas->pixels[cy * canvas->width + cx] = (SV_Color){.color = 0xFFFFFFFF};
    }
  }
}
