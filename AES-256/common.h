#ifndef COMMON_H
#define COMMON_H

#define __OUT__
#define __IN__

#include <stdint.h>

typedef unsigned char u_char;

int random_s(int min, int max, int *err);

int random_mem(u_char *mem, uint32_t len);

void bin2hex(const u_char *data, uint32_t size, char *out);

u_char gadd(u_char a, u_char b);

u_char gmul(u_char a, u_char b);
#endif // COMMON_H
