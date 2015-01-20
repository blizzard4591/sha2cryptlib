#include "src/interface-c/sha2cryptLibC.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const struct {
	const char *input;
	const char result[32];
} tests[] =
{
	/* Test vectors from FIPS 180-2: appendix B.1.  */
	{ "abc",
	"\xba\x78\x16\xbf\x8f\x01\xcf\xea\x41\x41\x40\xde\x5d\xae\x22\x23"
	"\xb0\x03\x61\xa3\x96\x17\x7a\x9c\xb4\x10\xff\x61\xf2\x00\x15\xad" },
	/* Test vectors from FIPS 180-2: appendix B.2.  */
	{ "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
	"\x24\x8d\x6a\x61\xd2\x06\x38\xb8\xe5\xc0\x26\x93\x0c\x3e\x60\x39"
	"\xa3\x3c\xe4\x59\x64\xff\x21\x67\xf6\xec\xed\xd4\x19\xdb\x06\xc1" },
	/* Test vectors from the NESSIE project.  */
	{ "",
	"\xe3\xb0\xc4\x42\x98\xfc\x1c\x14\x9a\xfb\xf4\xc8\x99\x6f\xb9\x24"
	"\x27\xae\x41\xe4\x64\x9b\x93\x4c\xa4\x95\x99\x1b\x78\x52\xb8\x55" },
	{ "a",
	"\xca\x97\x81\x12\xca\x1b\xbd\xca\xfa\xc2\x31\xb3\x9a\x23\xdc\x4d"
	"\xa7\x86\xef\xf8\x14\x7c\x4e\x72\xb9\x80\x77\x85\xaf\xee\x48\xbb" },
	{ "message digest",
	"\xf7\x84\x6f\x55\xcf\x23\xe1\x4e\xeb\xea\xb5\xb4\xe1\x55\x0c\xad"
	"\x5b\x50\x9e\x33\x48\xfb\xc4\xef\xa3\xa1\x41\x3d\x39\x3c\xb6\x50" },
	{ "abcdefghijklmnopqrstuvwxyz",
	"\x71\xc4\x80\xdf\x93\xd6\xae\x2f\x1e\xfa\xd1\x44\x7c\x66\xc9\x52"
	"\x5e\x31\x62\x18\xcf\x51\xfc\x8d\x9e\xd8\x32\xf2\xda\xf1\x8b\x73" },
	{ "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
	"\x24\x8d\x6a\x61\xd2\x06\x38\xb8\xe5\xc0\x26\x93\x0c\x3e\x60\x39"
	"\xa3\x3c\xe4\x59\x64\xff\x21\x67\xf6\xec\xed\xd4\x19\xdb\x06\xc1" },
	{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
	"\xdb\x4b\xfc\xbd\x4d\xa0\xcd\x85\xa6\x0c\x3c\x37\xd3\xfb\xd8\x80"
	"\x5c\x77\xf1\x5f\xc6\xb1\xfd\xfe\x61\x4e\xe0\xa7\xc8\xfd\xb4\xc0" },
	{ "123456789012345678901234567890123456789012345678901234567890"
	"12345678901234567890",
	"\xf3\x71\xbc\x4a\x31\x1f\x2b\x00\x9e\xef\x95\x2d\xd8\x3c\xa8\x0e"
	"\x2b\x60\x02\x6c\x8e\x93\x55\x92\xd0\xf9\xc3\x08\x45\x3c\x81\x3e" }
};
#define ntests (sizeof (tests) / sizeof (tests[0]))


static const struct {
	const char *salt;
	const char *input;
	const char *expected;
} tests2[] =
{
	{ "$5$saltstring", "Hello world!",
	"$5$saltstring$5B8vYYiY.CVt1RlTTf8KbXBH3hsxY/GNooZaBBGWEc5" },
	{ "$5$rounds=10000$saltstringsaltstring", "Hello world!",
	"$5$rounds=10000$saltstringsaltst$3xv.VbSHBb41AL9AvLeujZkZRBAwqFMz2."
	"opqey6IcA" },
	{ "$5$rounds=5000$toolongsaltstring", "This is just a test",
	"$5$rounds=5000$toolongsaltstrin$Un/5jzAHMgOGZ5.mWJpuVolil07guHPvOW8"
	"mGRcvxa5" },
	{ "$5$rounds=1400$anotherlongsaltstring",
	"a very much longer text to encrypt.  This one even stretches over more"
	"than one line.",
	"$5$rounds=1400$anotherlongsalts$Rx.j8H.h8HjEDGomFU8bDkXm3XIUnzyxf12"
	"oP84Bnq1" },
	{ "$5$rounds=77777$short",
	"we have a short salt string but not a short password",
	"$5$rounds=77777$short$JiO1O3ZpDAxGJeaDIuqCoEFysAe1mZNJRs3pw0KQRd/" },
	{ "$5$rounds=123456$asaltof16chars..", "a short string",
	"$5$rounds=123456$asaltof16chars..$gP3VQ/6X7UUEW3HkBn2w1/Ptq2jxPyzV/"
	"cZKmF/wJvD" },
	{ "$5$rounds=10$roundstoolow", "the minimum number is still observed",
	"$5$rounds=1000$roundstoolow$yfvwcWrQ8l/K0DAWyuPMDNHpIVlTQebY9l/gL97"
	"2bIC" },
};
#define ntests2 (sizeof (tests2) / sizeof (tests2[0]))


int main(void) {
	printf("SHA-256 Test Utility\nUsing Test Vectors from:\n - FIPS 180-2: appendix B.1.\n - FIPS 180-2: appendix B.2.\n - the NESSIE project\n plus additional tests for the SHA-256-CRYPT functionality.\n\n");
	struct sha256_ctx ctx;
	char sum[32];
	int result = 0;
	int cnt;

	for (cnt = 0; cnt < (int)ntests; ++cnt) {
		sha256_init_ctx(&ctx);
		sha256_process_bytes(tests[cnt].input, strlen(tests[cnt].input), &ctx);
		sha256_finish_ctx(&ctx, sum);
		if (memcmp(tests[cnt].result, sum, 32) != 0) {
			printf("test %d run %d failed\n", cnt, 1);
			result = 1;
		}

		sha256_init_ctx(&ctx);
		for (int i = 0; tests[cnt].input[i] != '\0'; ++i) {
			sha256_process_bytes(&tests[cnt].input[i], 1, &ctx);
		}
		sha256_finish_ctx(&ctx, sum);
		if (memcmp(tests[cnt].result, sum, 32) != 0) {
			printf("test %d run %d failed\n", cnt, 2);
			result = 1;
		}
	}

	/* Test vector from FIPS 180-2: appendix B.3.  */
	char buf[1000];
	memset(buf, 'a', sizeof(buf));
	sha256_init_ctx(&ctx);
	for (int i = 0; i < 1000; ++i) {
		sha256_process_bytes(buf, sizeof(buf), &ctx);
	}
	sha256_finish_ctx(&ctx, sum);
	static const char expected[32] =
		"\xcd\xc7\x6e\x5c\x99\x14\xfb\x92\x81\xa1\xc7\xe2\x84\xd7\x3e\x67"
		"\xf1\x80\x9a\x48\xa4\x97\x20\x0e\x04\x6d\x39\xcc\xc7\x11\x2c\xd0";
	if (memcmp(expected, sum, 32) != 0) {
		printf("test %d failed\n", cnt);
		result = 1;
	}

	for (cnt = 0; cnt < ntests2; ++cnt) {
		char *cp = sha256_crypt_s(tests2[cnt].input, tests2[cnt].salt);

		if ((cp == NULL) || strcmp(cp, tests2[cnt].expected) != 0) {
			printf("test %d: expected \"%s\", got \"%s\"\n", cnt, tests2[cnt].expected, cp);
			result = 1;
		}

		if (cp != NULL) {
			free(cp);
		}
	}

	if (result == 0) {
		printf("Result: all tests OK\n");
	} else {
		printf("Result: some (%i) tests FAILED\n", result);
	}

	return result;
}