#include "OpenGLManager.h"
#include <iostream>

GLFWwindow* OpenGLManager::window;

bool
OpenGLManager::init(WindowProperties windowProperties)
{
	window = nullptr;

	std::cout << "Trying to initialize opengl libraries..." << std::endl;

	//----------------------------------------------------------------------------------------

	std::cout << "Initializing glfw..." << std::endl;
	if (!glfwInit()) {
		std::cout << "ERROR OCCURED: Failed to initialize glfw library" << std::endl;
		return false;
	}

	//----------------------------------------------------------------------------------------

	std::cout << "Creating window..." << std::endl;
	window = glfwCreateWindow(windowProperties.width,
							  windowProperties.height,
							  windowProperties.title.c_str(),
							  windowProperties.monitor,
							  windowProperties.share);
	if (!window) {
		std::cout << "ERROR OCCURED: Failed to create a window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	//----------------------------------------------------------------------------------------

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR OCCURED: Failed to create a window" << std::endl;
		glfwTerminate();
		return false;
	}

	//----------------------------------------------------------------------------------------

	return true;
}

GLFWwindow*
OpenGLManager::getWindow()
{
	return OpenGLManager::window;
}

WindowProperties::WindowProperties(int width,
								   int height,
								   std::string title,
								   GLFWmonitor* monitor,
								   GLFWwindow* share)
	: width(width),
	  height(height),
	  title(title),
	  monitor(monitor),
	  share(share)
{}
