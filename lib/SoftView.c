#include "../include/SoftView.h"

#include <stdbool.h>

#define MIN(a, b) (a) < (b) ? (a) : (b)


static Canvas canvas = {0};

bool str_eq(char *str, uint32_t len, const char check[], uint32_t other_len) {
	if (len != other_len) return false;

	for (size_t i = 0; i < len; i++) {
		if (str[i] != check[i]) return false;
	}

	return true;
}

bool is_hex_digit(char c) {
	return ('0' <= c && c <= '9') || ('A' <= c && c <= 'F');
}

uint32_t read_hex_value(char **str_ptr) {
	char *str = *str_ptr;
	if (str[0] != '0' || str[1] != 'x') return 0;
	str += 2;

	uint32_t val = 0;
	uint32_t len = 0;
	for (len = 0; len < 8; len++) {
		char c = str[len];
		if (!is_hex_digit(c)) break;

		val *= 16;
		if (c >= '0' && c <= '9') {
			val += c - '0';
		} else {
			val += c - 'A' + 10;
		}
	}

	*str_ptr += len + 2;

	return val;
}


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

void SoftView_canvas_set_bg(Color bg) {
	canvas.bg = bg;
}

void SoftView_canvas_set_fg(Color fg) {
	canvas.fg = fg;
}

void SoftView_canvas_set(char *args, uint32_t len) {
	if (str_eq(args, MIN(len, 3), "bg ", 3)) {
		args += 3;
		uint32_t val = read_hex_value(&args);
		SoftView_canvas_set_bg(val);
	} else if (str_eq(args, MIN(len, 3), "fg ", 3)) {
		args += 3;
		uint32_t val = read_hex_value(&args);
		SoftView_canvas_set_fg(val);
	}
}

void SoftView_handle_command(char *command, uint32_t len) {
	if (str_eq(command, MIN(len, 5), "clear", 5)) {
		SoftView_canvas_clear();
	} else if (str_eq(command, MIN(len, 4), "set ", 4)) {
		SoftView_canvas_set(command + 4, len - 4);
	}
}

Color *SoftView_get() {
	return canvas.pixels;
}
