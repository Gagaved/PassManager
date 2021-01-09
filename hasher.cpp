#include "hasher.h"
#include <stdlib.h>
unsigned long long pseud_exp(unsigned int c, int ex) {
	unsigned long long result = c;
	for (int i = 0; i < ex; i++) {
		result *= c;
		if (result == 0)
		{
			return pseud_exp((c % i) + 1, ex - 1);
		}
	}
	return result;
}
unsigned long long hash(std::string password) {
	unsigned long long mult = 1;
	for (unsigned int i = 0; i < password.size(); i++) {
		unsigned long long power = pseud_exp((int)password[i], (i + 1));
		if (power == 0) {
		}
		unsigned long long mult_old = mult;
		mult = mult + mult * power;
	}
	return mult;
}

std::vector<char> hasher(unsigned long long hash, std::string str_data) {
	std::string strF;
	std::vector<char> strF_hashing;

	char a = char(hash & 0xFF);
	char b = char((hash & 0xFF00) >> 8);
	char c = char((hash & 0xFF0000) >> 16);
	char d = char((hash & 0xFF000000) >> 24);
	char e = char((hash & 0xFF00000000) >> 32);
	char f = char((hash & 0xFF0000000000) >> 40);
	char g = char((hash & 0xFF000000000000) >> 48);
	char h = char((hash & 0xFF00000000000000) >> 56);
	strF = str_data;

	for (unsigned int i = 0; i < strF.size(); i++) {
		char cur = strF[i];
		if (i % 8 == 0) {
			strF_hashing.push_back(cur ^ a);
		}
		else if (i % 8 == 1) {
			strF_hashing.push_back(cur ^ b);
		}
		else if (i % 8 == 2) {
			strF_hashing.push_back(cur ^ c);
		}
	    else if (i % 8 == 3) {
			strF_hashing.push_back(cur ^ d);
		}
		else if (i % 8 == 4) {
			strF_hashing.push_back(cur ^ e);
		}
		else if (i % 8 == 5) {
			strF_hashing.push_back(cur ^ f);
		}
		else if (i % 8 == 6) {
			strF_hashing.push_back(cur ^ g);
		}
		else if (i % 8 == 7) {
			strF_hashing.push_back(cur ^ h);
		}
	}
	return strF_hashing;
}
void de_hasher(unsigned long long hash, std::string path, std::vector<char>& str) {
	std::vector<char> strF;
	char a = char(hash & 0xFF);
	char b = char((hash & 0xFF00) >> 8);
	char c = char((hash & 0xFF0000) >> 16);
	char d = char((hash & 0xFF000000) >> 24);
	char e = char((hash & 0xFF00000000) >> 32);
	char f = char((hash & 0xFF0000000000) >> 40);
	char g = char((hash & 0xFF000000000000) >> 48);
	char h = char((hash & 0xFF00000000000000) >> 56);

	char temp;
	std::ifstream fin(path, std::ifstream::binary);
	while (fin.read(&temp, sizeof(char))) {
		strF.push_back(temp);
	}

	fin.close();
	for (int i = 0; i < strF.size(); i++) {
		char cur = strF[i];
		if (i % 8 == 0) {
			str.push_back(cur ^ a);
		}
		else if (i % 8 == 1) {
			str.push_back(cur ^ b);
		}
		else if (i % 8 == 2) {
			str.push_back(cur ^ c);
		}
		else if (i % 8 == 3) {
			str.push_back(cur ^ d);
		}
		else if (i % 8 == 4) {
			str.push_back(cur ^ e);

		}
		else if (i % 8 == 5) {
			str.push_back(cur ^ f);

		}
		else if (i % 8 == 6) {
			str.push_back(cur ^ g);

		}
		else if (i % 8 == 7) {
			str.push_back(cur ^ h);
		}
	}
	return;
}