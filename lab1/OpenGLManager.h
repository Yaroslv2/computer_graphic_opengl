#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

struct WindowProperties 
{
	int width;
	int height;
	std::string title;
	GLFWmonitor* monitor;
	GLFWwindow* share;

	WindowProperties(int, int, std::string, GLFWmonitor*, GLFWwindow*);
};

class OpenGLManager 
{
public:
	static bool init(WindowProperties);
	static GLFWwindow* getWindow();
private:
	static GLFWwindow* window;
};