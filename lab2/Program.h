#pragma once

#include "Window.h"
#include "Scene.h"

class Program
{
public:
	Program();
	/// <summary>
	/// run program
	/// </summary>
	void run();
private:
	Window& window;
};

