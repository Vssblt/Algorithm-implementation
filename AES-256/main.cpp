#include "aes-ex.h"
#include <cstring>

int 
main()
{
	std::string out;
	AesEx aes;

	aes.set_key(std::string("\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 32));
	aes.set_plaintext(std::string("\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16));
	aes.encrypt(out);

	for (int i = 0; i < out.size(); i++)
	{

		printf("%x ", (u_char)out.at(i));

	}

	printf("\n");

	return 0;
}
