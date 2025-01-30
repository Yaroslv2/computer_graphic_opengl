#include "Program.h"

#include <iostream>

#include "Window.h"
#include "Input.h"
#include "SceneManager.h"

Program::Program() : running(true), window(nullptr)
{
	//---------------------------------------------------------------------------------------------------

	// инициализируем библиотеки GLFW
	if (glfwInit() != GLFW_TRUE)
	{
		std::cout << "Cannot initialize GLFW library." << std::endl;
		running = false;
		return;
	}

	//---------------------------------------------------------------------------------------------------
	
	// создаем окно
	Window::getInstance().createWindow(1000, 800, "title");
	
	/// команда для установки контекста
	Window::getInstance().setActive();

	//---------------------------------------------------------------------------------------------------

	// инициализация библиотеки GLEW
	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Cannot intialize GLEW library. Error: " << glewGetErrorString(err) << std::endl;
		running = false;
		return;
	}

	//---------------------------------------------------------------------------------------------------

	// установка цвета очистки экрана
	glClearColor(255.0f, 255.0f, 255.0f, 1.0f);

	SceneManager::getInstanse().changeScene(new Scene());

	Input::getInstance().setCallbacks();
}

Program::~Program()
{
	/// закрывает библиотеку, удаляет все окна, и пр
	glfwTerminate(); 
}

bool 
Program::isRunning()
{
	return running;
}

void 
Program::run()
{
	// основной цикл программы
	while (!Window::getInstance().isClosed()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// обработка событий
		glfwPollEvents();

		// TODO: отрисовка объектов
		SceneManager::getInstanse().render();

		// замена отображаемого буфера на тот, который подготавливается за экраном
		glfwSwapBuffers(Window::getInstance().getGLFWwindow());
	}
}
