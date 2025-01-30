#pragma once

#include "libsInclude.h"
#include <string>

class Window
{
public:
	static Window& getInstanse();

	/// <summary>
	/// Create MyWindow
	/// </summary>
	/// <param name="width">window width</param>
	/// <param name="height">window height</param>
	/// <param name="title">window title</param>
	/// <returns>true - window was created, false - smth went wrong</returns>
	bool createWindow(int width, int height, std::string title);

	/// <summary>
	/// Get GLFWwindow pointer
	/// </summary>
	/// <returns>pointer of openGL window</returns>
	GLFWwindow*& getGLFWwindow();

	/// <summary>
	/// resize window
	/// </summary>
	/// <param name="width">new width window</param>
	/// <param name="height">new height window</param>
	void resize(int width, int height);

	/// <summary>
	/// close window
	/// </summary>
	void close();

	/// <summary>
	/// chacking whether the window needs to be closed
	/// </summary>
	/// <returns>boolean</returns>
	bool isWindowClosed();

	/// <summary>
	/// set window active
	/// </summary>
	void setActive();

	int getHeight();

	int getWidth();
private:
	// opengl window
	GLFWwindow* window;
	// window height
	int height;
	// window width
	int width;
	// window title
	std::string title;

	Window();
	static Window instanse;
};

