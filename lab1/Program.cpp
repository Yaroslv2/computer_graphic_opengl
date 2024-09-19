#include "Program.h"

#include "OpenGLManager.h"

void
Program::pollEvents()
{
	glfwPollEvents();
}

Program::Program()
{
	colors.push_back(RED_COLOR);
	colors.push_back(BLUE_COLOR);
	colors.push_back(GREEN_COLOR);

	triangles.push_back(Triangle({
		 -0.3f, 0.0f, 0.0f,
		 0.0f, -0.6f, 0.0f,
		 -0.6f, -0.6f, 0.0f
		}, colors[0]));

	triangles.push_back(Triangle({
		 0.3f, 0.0f, 0.0f,
		 0.0f, -0.6f, 0.0f,
		 0.6f, -0.6f, 0.0f
		}, colors[1]));

	triangles.push_back(Triangle({
		 0.0f, 0.6f, 0.0f,
		 -0.3f, 0.0f, 0.0f,
		 0.3f, 0.0f, 0.0f
		}, colors[2]));
}

void
Program::run()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(OpenGLManager::getWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < triangles.size(); i++)
		{
			triangles[i].draw();
			pollEvents();
		}
		glfwSwapBuffers(OpenGLManager::getWindow());
	}

	glfwTerminate();
}