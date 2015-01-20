#include <stdlib.h>
#include <string.h>

// Test whether STPNCPY is available.

int main(int argc, char* argv[]) {
	char testData[4];
	testData[0] = 'A';
	testData[1] = 'B';
	testData[2] = 'C';
	testData[3] = '\0';
	stpncpy(&testData[0], &testData[2], 2);
	
	return 0;
}