#include "ProgramLoop.h"

#include <iostream>

int main()
{
	srand((unsigned)time(0));
	
	try {
		ProgramLoop programLoop;
		programLoop.run();
	}
	catch (std::exception& e) {
		std::cout << "EXCEPTION: " << e.what() << std::endl;
	}

	return 0;
}