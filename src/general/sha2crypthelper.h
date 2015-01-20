#ifndef SHA2CRYPTLIB_GENERAL_SHA2CRYPTHELPER_H_
#define SHA2CRYPTLIB_GENERAL_SHA2CRYPTHELPER_H_

// Generated config file
#include "sha2cryptLibConfig.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>

#ifdef SHA2CRYPTLIB_CONFIG_HAVE_ENDIAN_H
#	include <endian.h>
#endif
#include "portable_endian.h"

#	define __alignof__(x) __alignof(x)
#	define __ALIGNOF_UINT32_T SHA2CRYPTLIB_CONFIG_TYPEALIGNMENT_UINT32
#	define __ALIGNOF_UINT64_T SHA2CRYPTLIB_CONFIG_TYPEALIGNMENT_UINT64
#	define snprintf _snprintf_c
#	define __stpncpy stpncpy


#ifndef SHA2CRYPTLIB_CONFIG_HAVE_MEMPCPY
	void* mempcpy(void *to, const void *from, size_t size);
#endif

#ifndef SHA2CRYPTLIB_CONFIG_HAVE_STPNCPY
	char *stpncpy(char *dest, const char *src, size_t n);
#endif

#ifndef MIN
#	define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef MAX
#	define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#endif