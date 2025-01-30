#include <iostream>
#include "Program.h"

int main()
{
	Program program;

	if (program.isRunning()) {
		program.run();
	}
	return 0;
}