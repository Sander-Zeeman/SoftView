#include "canvas.h"

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
