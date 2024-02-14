#include "SoftView.h"

static Canvas canvas = {0};

#define SZ_STRING_IMPLEMENTATION
#include "sz_string.h"

void SoftView_init(uint32_t width, uint32_t height) {
	canvas.width = width;
	canvas.height = height;
	canvas.bg = 0xFFCCCCCC;
	canvas.fg = 0xFF333333;
	canvas.pixels = MALLOC(width * height * sizeof(Color));
	for (size_t i = 0; i < width * height; i++) canvas.pixels[i] = canvas.bg;
}

void SoftView_canvas_clear() {
	for (size_t i = 0; i < canvas.width * canvas.height; i++) canvas.pixels[i] = canvas.bg;
}

void SoftView_canvas_set(SZS_String args) {
	SZS_String type = szs_split_left(&args, ' ');
	if (szs_compare_cstr(type, "bg")) {
		platform_log(args.data, args.size);
	} else if (szs_compare_cstr(type, "fg")) {
		platform_log(args.data, args.size);
	}
}

void SoftView_handle_command(char *command, uint32_t len) {
	platform_log(command, len);

	SZS_String str = szs_from_cstr(command);
	SZS_String action = szs_split_left(&str, ' ');

	if (szs_compare_cstr(action, "clear")) {
		SoftView_canvas_clear();
	} else if (szs_compare_cstr(action, "set")) {
		SoftView_canvas_set(str);
	}
}

Color *SoftView_get() {
	return canvas.pixels;
}

void SoftView_set_bg(Color bg) {
	canvas.bg = bg;
}

void SoftView_set_fg(Color fg) {
	canvas.fg = fg;
}
