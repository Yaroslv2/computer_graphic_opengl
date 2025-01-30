#include "Callbacks.h"
#include "Window.h"
#include "SceneManager.h"

#include <iostream>

Callbacks Callbacks::instance = Callbacks();

Callbacks::Callbacks()
{}

Callbacks&
Callbacks::getInstance()
{
	return instance;
}

void
Callbacks::windowResize(GLFWwindow* window,
	int height,
	int width)
{

	Window::getInstanse().resize(height, width);
}

void
Callbacks::keyAction(GLFWwindow* window,
	int key,
	int scancode,
	int action,
	int mods)
{
	switch (action) {
	case GLFW_PRESS:
		std::cout << "key pressed: " << key << std::endl;
		Callbacks::keyPress(key);
		break;
	default:
		break;
	}
}

void Callbacks::keyPress(int key)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		Window::getInstanse().close();
		break;
	case GLFW_KEY_A:
		SceneManager::getInstanse().setCurrentSubSceneIdx(0);
		break;
	case GLFW_KEY_B:
		SceneManager::getInstanse().setCurrentSubSceneIdx(1);
		break;
	case GLFW_KEY_C:
		SceneManager::getInstanse().setCurrentSubSceneIdx(2);
		break;
	default:
		if (key >= GLFW_KEY_1 && key <= GLFW_KEY_8)
			SceneManager::getInstanse().setCurrentSceneIdx(key - GLFW_KEY_1);
		break;
	}
}