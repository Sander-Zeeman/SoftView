#include "../modifier.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


SOV_FUNCTION void SV_initialize_canvas(size_t, size_t, uint32_t);
SOV_FUNCTION uint32_t *SV_get_canvas();
SOV_FUNCTION size_t SV_get_width();
SOV_FUNCTION size_t SV_get_height();
SOV_FUNCTION void SV_delete_canvas();
SOV_FUNCTION bool SV_update_required();
SOV_FUNCTION bool SV_handle_command(char[], char[], bool*);

#define COMMAND_SIZE 1024

void pre_command(void) { printf("> "); }

void read_command(char command[]) {
  size_t idx = 0;
  for (char c = getchar(); c != '\n'; c = getchar()) {
    command[idx++] = c;
  }
}

int main(int argc, char *argv[]) {
  char out[1024];
  strcpy(out, argc > 1 ? argv[1] : "test.png");

  SV_initialize_canvas(800, 600, 0xFF333333);
  bool exit = false;
  char command[COMMAND_SIZE] = {0};
  char response[COMMAND_SIZE] = {0};
  memset(command, '\0', COMMAND_SIZE);
  memset(response, '\0', COMMAND_SIZE);

  while (!exit) {
    pre_command();
    read_command(command);
    SV_handle_command(command, response, &exit);
    printf("%s", response);
    memset(command, '\0', COMMAND_SIZE);
    memset(response, '\0', COMMAND_SIZE);

    if (SV_update_required()) {
      uint32_t *data = SV_get_canvas();
      size_t width = SV_get_width();
      size_t height = SV_get_height();
      (void)stbi_write_png(out, width, height, 4, data,
                           width * sizeof(uint32_t));
    }
  }

  SV_delete_canvas();
  return 0;
}
