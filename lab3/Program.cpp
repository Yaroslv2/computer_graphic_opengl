#include "Program.h"

#include "OpenGLManager.h"
#include "SceneManager.h"

Program::Program() : window(Window::getInstanse())
{}

void
Program::run()
{
	glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
	while (!window.isWindowClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();

		SceneManager::getInstanse().getScene()->display();

		glfwSwapBuffers(window.getGLFWwindow());
	}

	glfwTerminate();
}


