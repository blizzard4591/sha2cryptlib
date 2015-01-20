#ifndef SHA2CRYPTLIB_INTERFACEC_SHA2CRYPTLIBCPP_H_
#define SHA2CRYPTLIB_INTERFACEC_SHA2CRYPTLIBCPP_H_

#include "sha2CryptLibCpp_Export.h"
#include "general/sha256crypt.h"
#include "general/sha512crypt.h"

#include <string>

sha2CryptLibCpp_EXPORT std::string sha256_crypt_cpp(std::string const& key, std::string const& salt);

sha2CryptLibCpp_EXPORT std::string sha512_crypt_cpp(std::string const& key, std::string const& salt);

#endif