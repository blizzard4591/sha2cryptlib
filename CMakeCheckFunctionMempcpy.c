#include <stdlib.h>
#include <string.h>

// Test whether MEMPCPY is available.

int main(int argc, char* argv[]) {
	char testData[4];
	testData[0] = 0;
	testData[1] = 1;
	testData[2] = 2;
	testData[3] = 3;
	mempcpy(&testData[2], &testData[0], 2);
	
	return 0;
}