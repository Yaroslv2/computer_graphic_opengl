#pragma once

#include <vector>

#include "Triangle.h"

class Program
{
private:
	std::vector<Triangle> triangles;
	std::vector<Color> colors;
	void pollEvents();
public:
	Program();
	void run();
};