#include <iostream>

#include "OpenGlManager.h";
#include "Program.h"

int main() 
{
	WindowProperties props = WindowProperties(680, 420, "Triangels", NULL, NULL);
	if (!OpenGLManager::init(props)) {
		std::cout << "Exiting..." << std::endl;
	}
	
	Program program = Program();

	program.run();

	return 0;
}