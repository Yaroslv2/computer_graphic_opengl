#pragma once

#include "libsInclude.h"

/// <summary>
/// class, contained OpenGl callbacks
/// </summary>
class Callbacks
{
public:
	static Callbacks& getInstance();
	static void windowResize(GLFWwindow* window, int height, int width);
	static void keyAction(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void keyPress(int key);
private:
	Callbacks();
	static Callbacks instance;
};

