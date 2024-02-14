#ifndef SZ_STRING_H
#define SZ_STRING_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	char *data;
	uint32_t size;
} SZS_String;

#define SZS_Arg(str) (int) (str).size, (str).data

SZS_String szs_from_cstr(char *cstr);

SZS_String szs_take_first(SZS_String str);
SZS_String szs_take_first_n(SZS_String str, uint32_t n);
SZS_String szs_take_last(SZS_String str);
SZS_String szs_take_last_n(SZS_String str, uint32_t n);

SZS_String szs_drop_first(SZS_String str);
SZS_String szs_drop_first_n(SZS_String str, uint32_t n);
SZS_String szs_drop_last(SZS_String str);
SZS_String szs_drop_last_n(SZS_String str, uint32_t n);

SZS_String szs_drop_whitespace_left(SZS_String str);
SZS_String szs_drop_whitespace_right(SZS_String str);
SZS_String szs_drop_whitespace(SZS_String str);

int32_t szs_find_first(SZS_String str, char c);
int32_t szs_find_last(SZS_String str, char c);

SZS_String szs_split_left(SZS_String *str, char c);
SZS_String szs_split_right(SZS_String *str, char c);

bool szs_compare(SZS_String str1, SZS_String str2);
bool szs_compare_cstr(SZS_String str1, char *str2);

#ifdef SZ_STRING_IMPLEMENTATION

SZS_String szs_from_cstr(char *cstr) {
	uint32_t size = 0;
	while (cstr && cstr[size] != '\0') size++;
	return (SZS_String) {
		.data = cstr,
		.size = size
	};
}


SZS_String szs_take_first(SZS_String str) {
	return szs_take_first_n(str, 1);
}

SZS_String szs_take_first_n(SZS_String str, uint32_t n) {
	uint32_t take = n < str.size ? n : str.size;
	return (SZS_String) {
		.data = str.data,
		.size = take
	};
}

SZS_String szs_take_last(SZS_String str) {
	return szs_take_last_n(str, 1);
}

SZS_String szs_take_last_n(SZS_String str, uint32_t n) {
	uint32_t take = n < str.size ? n : str.size;
	return (SZS_String) {
		.data = str.data + str.size - take,
		.size = take
	};
}


SZS_String szs_drop_first(SZS_String str) {
	return szs_drop_first_n(str, 1);
}

SZS_String szs_drop_first_n(SZS_String str, uint32_t n) {
	uint32_t drop = n < str.size ? n : str.size;
	return (SZS_String) {
		.data = str.data + drop,
		.size = str.size - drop
	};
}

SZS_String szs_drop_last(SZS_String str) {
	return szs_drop_last_n(str, 1);
}

SZS_String szs_drop_last_n(SZS_String str, uint32_t n) {
	uint32_t drop = n < str.size ? n : str.size;
	return (SZS_String) {
		.data = str.data,
		.size = str.size - drop
	};
}


SZS_String szs_drop_whitespace_left(SZS_String str) {
	uint32_t off = 0;
	uint32_t done = 0;
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
	uint32_t off = str.size - 1;
	uint32_t done = 0;
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


int32_t szs_find_first(SZS_String str, char c) {
	uint32_t off = 0;
	while (off < str.size && str.data[off] != c) off++;
	return off >= str.size ? -1 : (int32_t)off;
}

int32_t szs_find_last(SZS_String str, char c) {
	int32_t off = str.size - 1;
	while (off >= 0 && str.data[off] != c) off--;
	return off;
}


SZS_String szs_split_left(SZS_String *str, char c) {
	int32_t split = szs_find_first(*str, c);
	if (split < 0) return *str;
	str->data[split] = '\0';
	str->data += split + 1;
	str->size -= split + 1;
	
	return (SZS_String) {
		.data = str->data - split - 1,
		.size = split
	};
}

SZS_String szs_split_right(SZS_String *str, char c) {
	int32_t split = szs_find_last(*str, c);
	if (split < 0) return *str;
	str->data[split] = '\0';
	str->size -= split + 1;

	return (SZS_String) {
		.data = str->data + split + 1,
		.size = str->size - split - 1
	};
}

bool szs_compare(SZS_String str1, SZS_String str2) {
	if (str1.size != str2.size) return false;

	for (uint32_t i = 0; i < str1.size; i++) {
		if (str1.data[i] != str2.data[i]) return false;
	}

	return true;
}

bool szs_compare_cstr(SZS_String str1, char *cs) {
	SZS_String str2 = szs_from_cstr(cs);
	return szs_compare(str1, str2);
}

#endif // SZ_STRING_IMPLEMENTATION

#endif // SZ_STRING_H
