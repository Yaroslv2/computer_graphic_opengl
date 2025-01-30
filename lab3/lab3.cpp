#include <iostream>

#include "OpenGLManager.h"
#include "Program.h"

#include <ctime>

int main()
{
	std::srand(std::time(NULL));

	OpenGLManager openGLManager = OpenGLManager::getInstanse();

	if (!openGLManager.init())
	{
		std::cout << "Exiting..." << std::endl;
		return 0;
	}

	Program program;
	program.run();

	return 0;
}