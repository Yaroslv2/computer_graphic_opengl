#pragma once

#include "opengl_libs.h"

/// <summary>
/// Класс, отвечающий за жизненный цикл программы
/// </summary>
class Program
{
public:
	/// <summary>
	/// Конструктор, инициализирует библиотеки
	/// </summary>
	Program();
	/// <summary>
	/// Деструктор, закрывает библиотеки
	/// </summary>
	~Program();
	/// <summary>
	/// Проверка, была ли запущена программа
	/// </summary>
	/// <returns>true если программа запущена, false если нет</returns>
	bool isRunning();
	/// <summary>
	/// запуск работы программы
	/// </summary>
	void run();
private:
	/// <summary>
	/// Была ли запущена программа
	/// </summary>
	bool running;
	/// <summary>
	/// Окно
	/// </summary>
	GLFWwindow* window;
};

