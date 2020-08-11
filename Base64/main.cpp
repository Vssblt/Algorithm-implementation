#include "base64.h"
#include <malloc.h>
#include <string.h>

int 
main()
{
	char *out = (char *)malloc(sizeof(char) * 21);
	memset(out, 0, 21);
	
	char *out_origin = (char *)malloc(sizeof(char) * 14);
	memset(out_origin, 0, 14);

	const char *test_char = "1234567777777";

	base64_init();

	base64_encode((const u_char *)test_char, 14, out);
	
	base64_decode((const u_char *)out, 20, out_origin);

	printf("base64: %s\n", out);
	
	printf("origin string: %s\n", out_origin);

	delete out;

	return 0;
}
