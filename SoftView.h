#ifndef SOFTVIEW_H
#define SOFTVIEW_H

#ifdef WASM
#define SOFTVIEW_API(foo) __attribute__((export_name(foo)))
#define MALLOC scuffed_malloc
extern unsigned char __heap_base;
unsigned int bump_pointer = &__heap_base;
void *scuffed_malloc(unsigned long long n) {
	unsigned int r = bump_pointer;
	bump_pointer += n;
	return (void *)r;
}
#else
#define SOFTVIEW_API(foo) __attribute__(())
#include <stdlib.h>
#define MALLOC malloc
#endif

#include <stdint.h>
#include <stddef.h>

typedef uint32_t Color;

typedef struct {
	Color *pixels;
	uint32_t width;
	uint32_t height;
	Color bg;
	Color fg;
} Canvas;

void platform_log(char *msg, uint32_t len);

SOFTVIEW_API("init") void SoftView_init(uint32_t width, uint32_t height);
SOFTVIEW_API("handle") void SoftView_handle_command(char *command, uint32_t len);
SOFTVIEW_API("update") Color *SoftView_get();
#endif // SOFTVIEW_H
