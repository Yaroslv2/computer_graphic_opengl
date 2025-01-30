#pragma once

#include "opengl_libs.h"

class Input
{
public:
	static Input& getInstance();
	/// <summary>
	/// Подписка на события
	/// </summary>
	void setCallbacks();
private:
	Input();
	static Input instance;
	/// <summary>
	/// Обработка событий клавиш
	/// </summary>
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void windowResizeCallback(GLFWwindow* window, int width, int height);
	/// <summary>
	/// Обработка события нажатия на клавишу
	/// </summary>
	void keyPressAction(int key, int scancode, int mods);
};

