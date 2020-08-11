#ifndef AES_EX_H
#define AES_EX_H

#include <cstring>
#include "common.h"
#include <map>

class AesEx
{
public:
	AesEx();
	
	~AesEx();

	void
	generate_s_box();

	inline void
	set_plaintext(const std::string &s)
	{
		this->_plaintext.append(s.c_str(), s.size());
	};

	void
	set_key(const std::string &key);

	void
	encrypt(std::string __OUT__ &out);

private:
	void
	filling();

	void
	sub_bytes();

	void
	shift_rows();

	void
	mix_columns();

	void
	add_round_key(int i);

	std::string
	gadd(int a, int b);

	std::string
	gadd(int a, std::string b);

	std::string
	gadd(std::string a, u_char b);

	std::string
	sub_word(int a);

	std::string
	sub_word(std::string a);

	std::string
	rot_word(int a);

private:
	std::map<int, u_char> _s_box;

	std::map<int, u_char> _inverse_s_box;
	
	std::map<int, u_char> _rcon;

	std::string _plaintext;

	std::string _key;

	std::string _ciphertext;
};


#endif 
