#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//#define SZ_STRING_IMPLEMENTATION
#include "SoftView.h"

#include "sz_string.h"

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

		SZS_String str = szs_from_cstr(command);

		// Get rid of the trailing newline
		str = szs_drop_last(str);

		SZS_String action = szs_split_left(&str, ' ');
		if (szs_compare_cstr(action, "exit")) {
			printf("Goodbye!\n");
			exit = true;
		}

		SoftView_handle_command(str.data, str.size);
	}

	return 0;
}
