#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "SoftView.h"

void platform_log(char *msg, uint32_t len) {
	printf("%.*s", len, msg);
}

void print_prompt() {
	printf("> ");
}

int main() {
	char command[1024] = {0};
	bool exit = false;

	SoftView_init(800, 600);

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
	}

	return 0;
}
