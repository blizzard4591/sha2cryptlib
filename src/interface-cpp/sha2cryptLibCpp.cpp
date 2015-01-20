#include "sha2cryptLibCpp.h"

std::string sha256_crypt_cpp(std::string const& key, std::string const& salt) {
	return std::string(sha256_crypt_s(key.c_str(), salt.c_str()));
}

std::string sha512_crypt_cpp(std::string const& key, std::string const& salt) {
	return std::string(sha512_crypt_s(key.c_str(), salt.c_str()));
}