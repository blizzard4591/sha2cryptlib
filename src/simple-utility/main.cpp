#include <iostream>
#include <string>
#include <random>

#include "interface-cpp/sha2cryptLibCpp.h"

#if defined(_WIN32) && defined(_MSC_VER)
#	define NOMINMAX
#	include <windows.h>
#else
#	include <termios.h>
#	include <unistd.h>
#endif

std::string readPassword() {
#if defined(_WIN32) && defined(_MSC_VER)	
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
#else
	termios oldt;
	tcgetattr(STDIN_FILENO, &oldt);
	termios newt = oldt;
	newt.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif

	std::string passwordA;
	std::string passwordB;
	bool repeat = false;
	do {
		std::cout << "Enter password: ";
		std::getline(std::cin, passwordA);
		std::cout << std::endl << "Repeat password: ";
		std::getline(std::cin, passwordB);
		std::cout << std::endl;
		if (passwordB != passwordA) {
			std::cout << "Incorrect password. Please try again!" << std::endl;
			repeat = true;
		} else {
			repeat = false;
		}
	} while (repeat);
	return passwordA;
}

void printHelp(char const* executableName) {
	std::cout << std::endl;
	std::cout << "Usage: " << executableName << " -s scheme [-r rounds]" << std::endl;
	std::cout << "Possible schemes: SHA256-CRYPT, SHA512-CRYPT" << std::endl;
	std::cout << "Possible rounds: 1000 - 999999999 (default: 5000)" << std::endl;
	std::cout << std::endl;
}

int main(int argc, char* argv[]) {
	int result = 0;
	
	if (argc < 3) {
		printHelp(argv[0]);
		return -1;
	} else {
		std::string scheme = "SHA512-CRYPT";
		size_t rounds = 5000;
		for (int i = 1; (i + 1) < argc; i += 2) {
			std::string optA = argv[i];
			std::string optB = argv[i + 1];
			if (optA == "-s" || optA == "--scheme") {
				if (optB == "SHA512-CRYPT") {
					scheme = "SHA512-CRYPT";
				} else if (optB == "SHA256-CRYPT") {
					scheme = "SHA256-CRYPT";
				} else {
					std::cout << "Error: Invalid value for scheme." << std::endl;
					printHelp(argv[0]);
					return -2;
				}
			} else if (optA == "-r" || optA == "--rounds") {
				int newRounds = std::stoi(optB, nullptr, 10);
				if ((1000 <= newRounds) && (newRounds <= 999999999)) {
					rounds = static_cast<size_t>(newRounds);
				} else {
					std::cout << "Error: Value for rounds is out of range." << std::endl;
					printHelp(argv[0]);
					return -3;
				}
			}
		}

		std::string userPassword = readPassword();

		// Seed with a real random value, if available
		std::random_device rd;

		std::default_random_engine generator(rd());
		std::uniform_int_distribution<int> distribution(0, 63);

		// Generate a 16 characters Salt
		static const char saltCharacters[65] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz./";
		std::string userSalt;
		userSalt.reserve(16);
		for (int i = 0; i < 16; ++i) {
			int randValue = distribution(generator);
			userSalt.push_back(saltCharacters[randValue]);
		}

		std::string finalHash = "";
		if (scheme == "SHA256-CRYPT") {
			std::string finalSalt = "$5$rounds=";
			finalSalt.append(std::to_string(rounds)).append("$").append(userSalt);
			finalHash = sha256_crypt_cpp(userPassword, finalSalt);
		} else if (scheme == "SHA512-CRYPT") {
			std::string finalSalt = "$6$rounds=";
			finalSalt.append(std::to_string(rounds)).append("$").append(userSalt);
			finalHash = sha512_crypt_cpp(userPassword, finalSalt);
		}

		std::cout << "Using scheme " << scheme << " with " << rounds << " rounds." << std::endl;
		std::cout << std::endl;
		std::cout << "Hash: " << finalHash << std::endl;
	}

	return result;
}