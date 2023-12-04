#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void SV_initialize_canvas(size_t width, size_t height, uint32_t fill);
bool SV_handle_command(char command[], char response[], bool *exit);
bool SV_update_required();
uint32_t *SV_get_canvas();
size_t SV_get_width();
size_t SV_get_height();
void SV_delete_canvas();
