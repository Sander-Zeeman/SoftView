#include "../include/SoftView.h"

#include <stdbool.h>

#define MIN(a, b) ((int32_t)(a) < (int32_t)(b) ? (a) : (b))
#define MAX(a, b) ((int32_t)(a) > (int32_t)(b) ? (a) : (b))
#define ABS_DIFF(a, b) (MAX(a, b) - MIN(a, b))

#define COMPARE_TEST(args, len, name, body) {			\
	size_t size = sizeof(name) / sizeof(char) - 1; 	\
	if (str_eq(args, MIN(len, size), name, size)) { \
		body 																					\
		return; 																			\
	} 																							\
}

static Canvas canvas = {0};

bool str_eq(char *str, uint32_t len, const char check[], uint32_t other_len) {
	if (len != other_len) return false;

	for (size_t i = 0; i < len; i++) {
		if (str[i] != check[i]) return false;
	}

	return true;
}

bool is_digit(char c) {
	return '0' <= c && c <= '9';
}

bool is_hex_digit(char c) {
	return is_digit(c) || ('A' <= c && c <= 'F');
}

uint32_t read_hex_value(char *str, uint32_t *len) {
	if (str[0] != '0' || str[1] != 'x') return 0;

	uint32_t val = 0;
	for (*len = 2; *len < 10; (*len)++) {
		char c = str[*len];
		if (!is_hex_digit(c)) break;

		val *= 16;
		if (is_digit(c)) {
			val += c - '0';
		} else {
			val += c - 'A' + 10;
		}
	}

	return val;
}

uint32_t read_uint32(char *str, uint32_t *len) {
	uint32_t val = 0;

	for (*len = 0; is_digit(str[*len]); (*len)++) {
		val *= 10;
		val += str[*len] - '0';
	}

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

void SoftView_canvas_set_bg(char *args, uint32_t len) {
	uint32_t val = read_hex_value(args, &len);
	canvas.bg = val;
}

void SoftView_canvas_set_fg(char *args, uint32_t len) {
	uint32_t val = read_hex_value(args, &len);
	canvas.fg = val;
}

void SoftView_canvas_set(char *args, uint32_t len) {
	COMPARE_TEST(args, len, "bg ", SoftView_canvas_set_bg(args + 3, len - 3);)
	COMPARE_TEST(args, len, "fg ", SoftView_canvas_set_fg(args + 3, len - 3);)
}

void SoftView_canvas_draw_rect(char *args, uint32_t len) {
	uint32_t read;

	uint32_t x = read_uint32(args, &read);
	if (len < read) return;
	args += read + 1;
	len -= read;

	uint32_t y = read_uint32(args, &read);
	if (len < read) return;
	args += read + 1;
	len -= read;

	uint32_t w = read_uint32(args, &read);
	if (len < read) return;
	args += read + 1;
	len -= read;

	uint32_t h = read_uint32(args, &read);
	if (len < read) return;
	args += read + 1;
	len -= read;

	for (uint32_t pos_y = y; pos_y < y + h; pos_y++) {
		for (uint32_t pos_x = x; pos_x < x + w; pos_x++) {
			canvas.pixels[pos_y * canvas.width + pos_x] = canvas.fg;
		}
	}

	return;
}

void SoftView_canvas_draw_circle(char *args, uint32_t len) {
	uint32_t read;

	uint32_t x = read_uint32(args, &read);
	if (len < read) return;
	args += read + 1;
	len -= read;

	uint32_t y = read_uint32(args, &read);
	if (len < read) return;
	args += read + 1;
	len -= read;

	uint32_t r = read_uint32(args, &read);
	if (len < read) return;
	args += read + 1;
	len -= read;

	uint32_t r2 = r*r;
	for (uint32_t pos_y = MAX(0, y - r); pos_y < MIN(canvas.height, y + r); pos_y++) {
		for (uint32_t pos_x = MAX(0, x - r); pos_x < MIN(canvas.width, x + r); pos_x++) {
			uint32_t x_dist = ABS_DIFF(pos_x, x);
			uint32_t y_dist = ABS_DIFF(pos_y, y);
			if ((x_dist * x_dist + y_dist * y_dist) <= r2) 
				canvas.pixels[pos_y * canvas.width + pos_x] = canvas.fg;
		}
	}	

	return;
}

void SoftView_canvas_draw(char *args, uint32_t len) {
	COMPARE_TEST(args, len, "rect ", SoftView_canvas_draw_rect(args + 5, len - 5);)
	COMPARE_TEST(args, len, "circle ", SoftView_canvas_draw_circle(args + 7, len - 7);)
}

void SoftView_handle_command(char *command, uint32_t len) {
	COMPARE_TEST(command, len, "clear", SoftView_canvas_clear();)
	COMPARE_TEST(command, len, "set ", SoftView_canvas_set(command + 4, len - 4);)
	COMPARE_TEST(command, len, "draw ", SoftView_canvas_draw(command + 5, len - 5);)
}

Color *SoftView_get() {
	return canvas.pixels;
}
