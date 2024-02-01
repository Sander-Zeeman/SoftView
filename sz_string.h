#ifndef SZ_STRING_H
#define SZ_STRING_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
	char *data;
	size_t size;
} SZS_String;

#define SZS_Arg(str) (int) (str).size, (str).data

SZS_String szs_from_cstr(char *cstr);

SZS_String szs_take_first(SZS_String str);
SZS_String szs_take_first_n(SZS_String str, size_t n);
SZS_String szs_take_last(SZS_String str);
SZS_String szs_take_last_n(SZS_String str, size_t n);

SZS_String szs_drop_first(SZS_String str);
SZS_String szs_drop_first_n(SZS_String str, size_t n);
SZS_String szs_drop_last(SZS_String str);
SZS_String szs_drop_last_n(SZS_String str, size_t n);

SZS_String szs_drop_whitespace_left(SZS_String str);
SZS_String szs_drop_whitespace_right(SZS_String str);
SZS_String szs_drop_whitespace(SZS_String str);

ssize_t szs_find_first(SZS_String str, char c);
ssize_t szs_find_last(SZS_String str, char c);

SZS_String szs_split_left(SZS_String str, char c);
SZS_String szs_split_right(SZS_String str, char c);
SZS_String* szs_split(SZS_String str, char c);

#ifdef SZ_STRING_IMPLEMENTATION

SZS_String szs_from_cstr(char *cstr) {
	size_t size = 0;
	while (cstr && cstr[size] != '\0') size++;
	return (SZS_String) {
		.data = cstr,
		.size = size
	};
}


SZS_String szs_take_first(SZS_String str) {
	return szs_take_first_n(str, 1);
}

SZS_String szs_take_first_n(SZS_String str, size_t n) {
	size_t take = n < str.size ? n : str.size;
	return (SZS_String) {
		.data = str.data,
		.size = take
	};
}

SZS_String szs_take_last(SZS_String str) {
	return szs_take_last_n(str, 1);
}

SZS_String szs_take_last_n(SZS_String str, size_t n) {
	size_t take = n < str.size ? n : str.size;
	return (SZS_String) {
		.data = str.data + str.size - take,
		.size = take
	};
}


SZS_String szs_drop_first(SZS_String str) {
	return szs_drop_first_n(str, 1);
}

SZS_String szs_drop_first_n(SZS_String str, size_t n) {
	size_t drop = n < str.size ? n : str.size;
	return (SZS_String) {
		.data = str.data + drop,
		.size = str.size - drop
	};
}

SZS_String szs_drop_last(SZS_String str) {
	return szs_drop_last_n(str, 1);
}

SZS_String szs_drop_last_n(SZS_String str, size_t n) {
	size_t drop = n < str.size ? n : str.size;
	return (SZS_String) {
		.data = str.data,
		.size = str.size - drop
	};
}


SZS_String szs_drop_whitespace_left(SZS_String str) {
	size_t off = 0;
	size_t done = 0;
	while (!done) {
		switch (str.data[off]) {
			case ' ':
			case '\t':
			case '\n':
				off++;
				break;
			default:
				done = 1;
				break;
		}
	}

	return (SZS_String) {
		.data = str.data + off,
		.size = str.size - off
	};
}

SZS_String szs_drop_whitespace_right(SZS_String str) {
	size_t off = str.size - 1;
	size_t done = 0;
	while (!done) {
		switch (str.data[off]) {
			case ' ':
			case '\t':
			case '\n':
				off--;
				break;
			default:
				done = 1;
				break;
		}
	}

	return (SZS_String) {
		.data = str.data,
		.size = off + 1
	};
}

SZS_String szs_drop_whitespace(SZS_String str) {
	return szs_drop_whitespace_right(
		szs_drop_whitespace_left(str)
	);
}


ssize_t szs_find_first(SZS_String str, char c) {
	size_t off = 0;
	while (off < str.size && str.data[off] != c) off++;
	return off >= str.size ? -1 : (ssize_t)off;
}

ssize_t szs_find_last(SZS_String str, char c) {
	ssize_t off = str.size - 1;
	while (off >= 0 && str.data[off] != c) off--;
	return off;
}


SZS_String szs_split_left(SZS_String str, char c) {
	ssize_t split = szs_find_first(str, c);
	if (split < 0) return str;
	return (SZS_String) {
		.data = str.data,
		.size = split
	};
}

SZS_String szs_split_right(SZS_String str, char c) {
	ssize_t split = szs_find_last(str, c);
	if (split < 0) return str;
	return (SZS_String) {
		.data = str.data + split + 1,
		.size = str.size - split - 1
	};
}

SZS_String* szs_split(SZS_String str, char c) {
	size_t counter = 0;
	for (size_t i = 0; i < str.size; i++) {
		if (str.data[i] == c) counter++;
	}

	SZS_String *parts = malloc(sizeof(SZS_String) * (counter + 2));
	for (size_t idx = 0; idx < counter; idx++) {
		ssize_t split = szs_find_first(str, c);
		assert(split >= 0);
		parts[idx] = (SZS_String){
			.data = str.data,
			.size = split
		};
		str = szs_drop_first_n(str, split + 1);
	}

	parts[counter] = (SZS_String){
		.data = str.data,
		.size = str.size
	};
	parts[counter + 1] = (SZS_String){
		.data = NULL,
		.size = 0
	};
	return parts;
}

#endif // SZ_STRING_IMPLEMENTATION

#endif // SZ_STRING_H
