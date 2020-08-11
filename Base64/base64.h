#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
typedef unsigned char u_char;

typedef struct Base64 Base64;

struct Base64 {
	char *table;
	char *safeTable;
};

extern Base64 *g_base64_map;// = &base64;

void base64_init();

size_t base64_encode(const u_char *str, size_t in_size, char *out);
size_t base64_decode(const u_char *str, size_t in_size, char *out);

size_t base64_safe_decode(const u_char *str, size_t in_size, char *out);
size_t base64_safe_encode(const u_char *str, size_t in_size, char *out);

size_t base64_sizeof(size_t in_size);

#endif
