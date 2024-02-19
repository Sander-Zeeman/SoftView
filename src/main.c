#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/SoftView.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

void platform_log(char *msg, uint32_t len) {
	printf("%.*s", len, msg);
}

void print_prompt() {
	printf("> ");
}

int main() {
	char command[1024] = {0};
	bool exit = false;

	size_t width = 800;
	size_t height = 600;
	SoftView_init(width, height);

	while (!exit) {
		print_prompt();

		if (fgets(command, 1024, stdin) == NULL) {
			printf("End of File reached.\n");
			exit = true;
			continue;
		}

		if (command[0] == 'e' && command[1] == 'x' && command[2] == 'i' && command[3] == 't') {
			printf("Goodbye!\n");
			exit = true;
		}

		uint32_t len = 0;
		while (command[len++] != '\0');

		SoftView_handle_command(command, len);

		const char *name = "test.png";
		Color *data = SoftView_get();
		if (!stbi_write_png(name, width, height, 4, data, width * sizeof(Color))) {
			printf("Could not write image to file.\n");
			exit = true;
			continue;
		}
	}

	return 0;
}
