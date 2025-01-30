#include "Input.h"

#include <iostream>

#include "Window.h"
#include "SceneManager.h"
#include "Events.hpp"


Input Input::instance = Input::Input();

Input& Input::getInstance()
{
	return instance;
}

void Input::setCallbacks()
{
	glfwSetKeyCallback(Window::getInstance().getGLFWwindow(), Input::keyCallback);
	glfwSetWindowSizeCallback(Window::getInstance().getGLFWwindow(), Input::windowResizeCallback);
}

Input::Input() {}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		instance.keyPressAction(key, scancode, mods);
		break;
	default:
		break;
	}
}

void Input::windowResizeCallback(GLFWwindow* window, int width, int height)
{
	Event* e = new WindowResizeEvent(width, height);
	Window::getInstance().resize(width, height);
	SceneManager::getInstanse().processEvents(e);
	delete e;
}

void Input::keyPressAction(int key, int scancode, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		Window::getInstance().close();
		break;
	default:
		KeyPressEvent* e = new KeyPressEvent(key, scancode, mods);
		SceneManager::getInstanse().processEvents(e);
		delete e;
		break;
	}
}
