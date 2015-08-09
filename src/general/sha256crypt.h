#ifndef SHA2CRYPTLIB_GENERAL_SHA256CRYPT_H_
#define SHA2CRYPTLIB_GENERAL_SHA256CRYPT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "sha2CryptLibC_Export.h"

/* Maximum salt string length.  */
#define SALT_LEN_MAX 16

/* Default number of rounds if not explicitly specified.  */
#define ROUNDS_DEFAULT 5000

/* Minimum number of rounds.  */
#define ROUNDS_MIN 1000

/* Maximum number of rounds.  */
#define ROUNDS_MAX 999999999

/* Structure to save state of computation between the single steps.  */
struct sha256_ctx {
	uint32_t H[8];

	uint32_t total[2];
	uint32_t buflen;
	char buffer[128];	/* NB: always correctly aligned for uint32_t.  */
};

/* Process LEN bytes of BUFFER, accumulating context into CTX.
It is assumed that LEN % 64 == 0.  */
sha2CryptLibC_EXPORT void sha256_process_block(const void *buffer, size_t len, struct sha256_ctx *ctx);

/* Initialize structure containing state of computation.
(FIPS 180-2:5.3.2)  */
sha2CryptLibC_EXPORT void sha256_init_ctx(struct sha256_ctx *ctx);

/* Process the remaining bytes in the internal buffer and the usual
prolog according to the standard and write the result to RESBUF.

IMPORTANT: On some systems it is required that RESBUF is correctly
aligned for a 32 bits value.  */
sha2CryptLibC_EXPORT void* sha256_finish_ctx(struct sha256_ctx *ctx, void *resbuf);

sha2CryptLibC_EXPORT void sha256_process_bytes(const void *buffer, size_t len, struct sha256_ctx *ctx);

sha2CryptLibC_EXPORT char* sha256_crypt_r(const char *key, const char *salt, char *buffer, size_t buflen);

/* This entry point is equivalent to the `crypt' function in Unix
libcs.
Warning: This function returns a pointer to static data, and	subsequent
calls to sha256_crypt() will modify the same data.
If you want a pointer to data that will never be modified and
are yours to free(), use sha256_crypt_s
*/
sha2CryptLibC_EXPORT char* sha256_crypt(const char *key, const char *salt);

/* This entry point is equivalent to the `crypt' function in Unix
libcs, BUT it returns a pointer and hands ownership over to the caller.
*/
sha2CryptLibC_EXPORT char* sha256_crypt_s(const char *key, const char *salt);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif // SHA2CRYPTLIB_GENERAL_SHA256CRYPT_H_