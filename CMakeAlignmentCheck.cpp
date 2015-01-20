#include <cstdint>
#include <iostream>
 
// This test is only relevant for MSVC
#ifdef _MSC_VER
#	define testAlignment(x) __alignof(x)
#else
#	define testAlignment(x) (0)
#endif
 
 int main(int argc, char* argv[]) {
	int resultUint32 = static_cast<int>(testAlignment(uint32_t));
	std::cout << "Alignment of type uint32_t: " << resultUint32 << std::endl;

	int resultUint64 = static_cast<int>(testAlignment(uint64_t));
	std::cout << "Alignment of type uint64_t: " << resultUint64 << std::endl;
	
	return 0;
 }