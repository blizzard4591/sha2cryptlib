#include <iostream>
#include <QtWidgets/QApplication>
#include "shacrypt.h"

#include "sodium.h"

int main(int argc, char* argv[]) {
	int sodiumInitRet = sodium_init();
	if (sodiumInitRet == -1) {
		std::cerr << "Could not initialize LibSodium! Return code was " << sodiumInitRet << std::endl;
		return 1;
	}

	int result = 0;
	try {
		QApplication app(argc, argv);
		ShaCrypt shaCrypt;
		shaCrypt.show();
		result = app.exec();
	} catch (std::exception e) {
		std::cerr << "An exception was raised: " << e.what() << std::endl;
		result = -1;
	}

	return result;
}

#ifdef _MSC_VER
int __stdcall
WinMain(struct HINSTANCE__ *hInstance,
struct HINSTANCE__ *hPrevInstance,
	char               *lpszCmdLine,
	int                 nCmdShow) {
	return main(__argc, __argv);
}

#endif