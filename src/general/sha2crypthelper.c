#include "sha2crypthelper.h"

#ifndef SHA2CRYPTLIB_CONFIG_HAVE_MEMPCPY

void* mempcpy(void *to, const void *from, size_t size) {
	memcpy(to, from, size);
	return (char *)to + size;
}

#endif

#ifndef SHA2CRYPTLIB_CONFIG_HAVE_STPNCPY

char *stpncpy(char *dest, const char *src, size_t n) {
	memset(dest, 0, n);
	const size_t srcLength = strlen(src);
	if (srcLength >= n) {
		memcpy(dest, src, n);
		return (char *)dest + n;
	} else {
		memcpy(dest, src, srcLength);
		return (char *)dest + srcLength;
	}
}

#endif