#include "common.h"
#include <time.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>


#ifdef _WIN32
	#include <windows.h>
	#ifndef _WIN32_WCE
		#define RtlGenRandom SystemFunction036
		extern "C"
		{
			BOOLEAN NTAPI RtlGenRandom(PVOID RandomBuffer, ULONG RandomBufferLength);
		}
		#pragma comment(lib, "advapi32.lib")
	#endif /*_WIN32_WCE*/
#else
	#if defined __linux__ || defined __CYGWIN__
		#include <fcntl.h>
		#include <unistd.h>
	#endif
#endif /*_WIN32*/


int
random_s(int min, int max, int *err) 
{
	int r = 0;
	int ret = random_mem((u_char*)&r, sizeof(r));
	if (err == nullptr) {
		if (ret == -1) {
			goto ret_zero;
		} else {
			goto ret_int;
		}
	} else {
		*err = ret;
		if (ret != -1) {
			goto ret_int;
		} else {
			goto ret_zero;
		}
	}

ret_int:   return (u_char)r % (max - min) + min;
ret_zero:  return 0;

}


void
uuid(char *_uuid) 
{
	int line[] = {12, 16, 20, 24,};
	u_char *data = (u_char *)malloc(16);
	random_mem(data, 16);

	data[6] = 0x40 | (data[6] & 0xf);
	data[8] = 0x80 | (data[8] & 0x3f);

	bin2hex(data, 16, _uuid);

	int j = 0;
	for (int i = 31; i > 6; i--)
	{
		if (31 - i == line[j])
		{
			_uuid[i + 4 - j] = '-';
			j++;
		}
		_uuid[i + 4 - j] = _uuid[i];
	}
	free(data);
}


int
random_mem(u_char *mem, uint32_t len) 
{
	int i = -1;
#ifdef _WIN32
  #ifdef _WIN32_WCE
	int ret = CeGenRandom(len, (BYTE *)mem);
	ret ? i = 0 : 0;
  #else
	int ret = RtlGenRandom(mem, (ULONG)len);
	ret ? i = 0 : 0;
  #endif	
#else
  #if defined __linux__ || defined __CYGWIN__
	int fd = open("/dev/urandom", O_RDONLY);
	if (fd != -1) {
		read(fd, mem, len);
		close(fd);
		i = 0;
	}
  #endif
#endif
	return i;
}


void
bin2hex(const u_char *data, uint32_t size, char *out) 
{
	for (uint32_t i = 0; i < size; i++){
		u_char low = (u_char)((u_char)(data[i] << 4) >> 4);
		u_char high = (u_char)(data[i] >> 4);

		if (low < 10){
			out[i * 2 + 1] = (char)(low + 0x30);
		}else{
			out[i * 2 + 1] = (char)(low - 10 + 0x41);
		}if (high < 10){
			out[i * 2] = (char)(high + 0x30);
		}else{
			out[i * 2] = (char)(high - 10 + 0x41);
		}
	}
}


u_char
gadd(u_char a, u_char b)
{
	return a ^ b;
}


u_char
gmul(u_char a, u_char b)
{
    u_char p = 0;

    for (int counter = 0; counter < 8; counter++) {
        if ((b & 1) != 0) {
            p ^= a;
        }

        bool hi_bit_set = (a & 0x80) != 0;
        a <<= 1;
        if (hi_bit_set) {
            a ^= 0x1B; /* x^8 + x^4 + x^3 + x + 1 */
        }
        b >>= 1;
    }

    return p;
}
