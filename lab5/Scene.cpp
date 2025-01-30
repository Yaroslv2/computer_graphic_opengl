#include "Scene.h"

#include <iostream>
#include <cmath>

#include "SceneManager.h"
#include "Window.h"
#include "Constants.h"
#include "Vase.h"

Scene::Scene() 
	: activeTaskIdx(0), activeSubTaskIdx(0), objects({}), shader(nullptr), dt(0), speed(1.5f), lt(0), offset(0) {}

Scene::~Scene() {}

void
Scene::onEntry()
{
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH); 
	glPointSize(10);
	glLineWidth(5);
	shader = new Shader("matrix_vs.glsl", "mono_fs.glsl");

	viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3({ 0.0f, 0.0f, -5.0f }));
	distanation = -5.0f;
	modelScaleMatrix =
		glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3({ 0.05f, 0.05f, 0.05f }));
	
	Window& window = Window::getInstance();
	perspectiveMatrix = glm::perspective(
		glm::radians(35.0f), // угол обзора в радианах обычно берётся в диапазоне 30-120 градусов
		(float)window.getWidth() / window.getHeight(), // соотношение сторон экрана
		2.0f, // расстояние от наблюдателя до ближней плоскости отсечения
		9.0f // расстояние от наблюдателя до дальней плоскости отсечения
	);

	objects.push_back(new Vase(*shader));

	update();
}

void 
Scene::render() 
{
	float time = glfwGetTime();
	dt = lt - time;
	lt = time;

	if (activeTaskIdx >= 3)
		update();

	for (auto object : objects)
	{
		object->render();
	}
}

void 
Scene::processEvents(Event* event)
{
	switch (event->type)
	{
	case Event::Type::KEY_PRESS:
		processKeyPressEvent((KeyPressEvent*)event);
		break;
	case Event::Type::WINDOW_RESIZE:
		perspectiveMatrix = glm::perspective(
			glm::radians(35.0f), // угол обзора в радианах обычно берётся в диапазоне 30-120 градусов
			(float)Window::getInstance().getWidth() / Window::getInstance().getHeight(), // соотношение сторон экрана
			2.f, // расстояние от наблюдателя до ближней плоскости отсечения
			9.0f // расстояние от наблюдателя до дальней плоскости отсечения
		);
		update();
		break;
	default:
		break;
	}
}

void 
Scene::onExit() 
{	
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
	delete shader;
}

void 
Scene::processKeyPressEvent(KeyPressEvent* event)
{
	if (GLFW_KEY_1 <= event->key && GLFW_KEY_6 >= event->key)
	{
		activeTaskIdx = event->key - GLFW_KEY_1;
		activeSubTaskIdx = 0;
	}

	switch (event->key)
	{
	case GLFW_KEY_A:
		activeSubTaskIdx = 0;
		break;
	case GLFW_KEY_B:
		activeSubTaskIdx = 1;
		break;
	case GLFW_KEY_C:
		break;
	default:
		break;
	}

	update();
}

void 
Scene::update()
{
	glEnable(GL_DEPTH_TEST);//Режим тестирования буфера глубины
	glDepthFunc(GL_LESS);
	switch (activeTaskIdx)
	{
	case 0:
		task1();
		break;
	case 1:
		task2();
		break;
	case 2:
		task3();
		break;
	case 3:
		task4();
		break;
	case 4:
		task5();
		break;
	case 5:
		task6();
		break;
	default:
		break;
	}
}

void 
Scene::task1()
{
	objects[0]->setMVPmatrix(perspectiveMatrix * viewMatrix * modelScaleMatrix);
}

void
Scene::task2()
{
}

void
Scene::task3()
{
	glm::mat4 cameraMatrix = glm::lookAt(glm::vec3({ 0.0f, 0.0f, -7.f }), glm::vec3({ 0.0f, 0.0f, 0.0f }), glm::vec3({ 0.0f, 1.0f, 0.0f }));
	objects[0]->setMVPmatrix(perspectiveMatrix * cameraMatrix * modelScaleMatrix);
}

void 
Scene::task4()
{
	if (activeSubTaskIdx > 1)
		activeSubTaskIdx = 0;
	
	glm::mat4 cameraMatrix;

	if (activeSubTaskIdx == 0)
	{
		angle += speed * 0.2;
		cameraMatrix = glm::lookAt(
			glm::vec3({ distanation * sin(glm::radians(angle)), 0.0f, distanation * cos(glm::radians(angle)) }),
			glm::vec3({ 0.0f, 0.0f, 0.0f }),
			glm::vec3({ 0.0f, 1.0f, 0.0f }));
	}


	if (activeSubTaskIdx == 1)
	{
		float transform = speed * dt;
		if (distanation + transform >= 12.f)
		{
			distanation = 12.f;
			speed = 1.f;
		}
		else if (distanation + transform <= 3.f)
		{
			distanation = 3.f;
			speed = -1.f;
		}
		else
		{
			distanation += transform;
		}

		cameraMatrix = glm::lookAt(glm::vec3({ 0.0f, 0.0f, distanation }), glm::vec3({ 0.0f, 0.0f, 0.0f }), glm::vec3({ 0.0f, 1.0f, 0.0f }));

	}
	objects[0]->setMVPmatrix(perspectiveMatrix * cameraMatrix * modelScaleMatrix);
}

void 
Scene::task5()
{
	float transform = speed * dt;
	switch (activeSubTaskIdx)
	{
	case 0:
		if (offset + transform >= 2.f)
		{
			offset = 2.f;
			speed = 2.f;
		}
		else if (offset + transform <= -2.f)
		{
			offset = -2.f;
			speed = -2.f;
		}
		else
		{
			offset += transform;
		}

		glm::mat4 cameraMatrix = glm::lookAt(glm::vec3({ 0.0f, 0.0f, -7.0f }), glm::vec3({ 0.0f, 0.0f, 0.0f }), glm::vec3({ 0.0f, 1.0f, 0.0f }));
		glm::mat4 modelTranslateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3({ offset, 0.0f, 0.0f }));
		objects[0]->setMVPmatrix(perspectiveMatrix * cameraMatrix * modelTranslateMatrix * modelScaleMatrix);
		break;
	case 1:
	{
		angle += speed * dt * 3;

		glm::mat4 cameraMatrix = glm::lookAt(glm::vec3({ 0.0f, 0.0f, -7.0f }), glm::vec3({ 0.0f, 0.0f, 0.0f }), glm::vec3({ 0.0f, 1.0f, 0.0f }));
		glm::mat4 modelRotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3({ 0.0f, 1.0f, 0.0f }));
		objects[0]->setMVPmatrix(perspectiveMatrix * cameraMatrix * modelRotateMatrix * modelScaleMatrix);
	}
		break;
	default:
		break;
	}
}

void 
Scene::task6()
{
	
}

std::vector<glm::vec3> 
Scene::genPolygonNormalize(int n, int scaleX, int scaleY, float offsetX, float offsetY, float rotation)
{
	std::vector<glm::vec3> points;
	float offsetAngle = (360. / (float)n) / 180. * M_PI;

	Window& window = Window::getInstance();
	for (int i = 0; i < n; i++)
	{
		float x = scaleX * cos(offsetAngle * i + rotation) / window.getWidth() + offsetX;
		float y = scaleY * sin(offsetAngle * i + rotation) / window.getHeight() + offsetY;
		points.push_back({ x, y, 0.0f });
	}

	return points;
}

std::vector<glm::vec3>
Scene::genPolygon(int n, int scaleX, int scaleY, float offsetX, float offsetY, float rotation)
{
	std::vector<glm::vec3> points;
	float offsetAngle = (360. / (float)n) / 180. * M_PI;

	Window& window = Window::getInstance();
	for (int i = 0; i < n; i++) 
	{
		float x = scaleX * cos(offsetAngle * i + rotation) + offsetX;
		float y = scaleY * sin(offsetAngle * i + rotation) + offsetY;
		points.push_back({ x, y, 0.0f });
	}

	return points;
}