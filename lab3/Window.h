#pragma once

#include <string>
#include "opengl_libs.h"

/// <summary>
/// синглтон для получения доступа к окну
/// </summary>
class Window
{
public:
	/// <summary>
	/// Получение синглтона
	/// </summary>
	/// <returns>экземпляр синглтона</returns>
	static Window& getInstance();
	/// <summary>
	/// Создание окна
	/// </summary>
	/// <param name="width">Ширина</param>
	/// <param name="height">Высота</param>
	/// <param name="title">Заголовок</param>
	/// <returns>true если создано, false если нет</returns>
	bool createWindow(int width, int height, std::string title);
	/// <summary>
	/// Получение GLFWwindow*
	/// </summary>
	GLFWwindow*& getGLFWwindow();
	/// <summary>
	/// Закрытие окна
	/// </summary>
	void close();
	/// <summary>
	/// Проверка, закрыто ли окно
	/// </summary>
	/// <returns>true если да, false если нет</returns>
	bool isClosed();
	/// <summary>
	/// Установка контекста на окно и callback
	/// </summary>
	void setActive();
	/// <summary>
	/// Получение высоты окна
	/// </summary>
	int getHeight();
	/// <summary>
	/// Получение ширины окна
	/// </summary>
	int getWidth();
	void resize(int height, int width);

	~Window();
private:
	/// <summary>
	/// синглтон
	/// </summary>
	static Window instanse;

	Window();
	
	int height; /// Высота
	int width; /// Ширина
	std::string title; /// Заголовок
	GLFWwindow* window; /// Указатель для работы с GLFW

};

