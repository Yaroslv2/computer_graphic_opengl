#include "Scene.h"

#include <iostream>
#include <cmath>

#include "SceneManager.h"
#include "Window.h"
#include "Constants.h"

Scene::Scene() : activeTaskIdx(0), activeSubTaskIdx(0), objects({}), shader(nullptr) {}

Scene::~Scene() {}

void
Scene::onEntry()
{
	glPointSize(10);
	glLineWidth(5);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	shader = new Shader("matrix_vs.glsl", "mono_fs.glsl");

	projectiveMatrix = glm::ortho(
		-1.0f, //координата плоскости отсечения слева
		0.9f, //координата плоскости отсечения справа
		-0.9f, //координата плоскости отсечения снизу
		1.0f, //координата плоскости отсечения сверху
		2.0f, // координата ближней плоскости отсечения
		9.0f // координата дальней плоскости отсечения
	);

	isPerspective = false;
	
	Window& window = Window::getInstance();
	std::cout << "w/h = " << (float)window.getWidth() / window.getHeight() << std::endl;
	perspectiveMatrix = glm::perspective(
		glm::radians(120.0f), // угол обзора в радианах обычно берётся в диапазоне 30-120 градусов
		(float)window.getWidth() / window.getHeight(), // соотношение сторон экрана
		0.01f, // расстояние от наблюдателя до ближней плоскости отсечения
		10.0f // расстояние от наблюдателя до дальней плоскости отсечения
	);

	cubeVertexes = {// вершины куба
		{-1.0f, -1.0f, -1.0f},  // 0: левый-нижний-задний
		{ 1.0f, -1.0f, -1.0f},  // 1: правый-нижний-задний
		{ 1.0f,  1.0f, -1.0f},  // 2: правый-верхний-задний
		{-1.0f,  1.0f, -1.0f},  // 3: левый-верхний-задний
		{-1.0f, -1.0f,  1.0f},  // 4: левый-нижний-передний
		{ 1.0f, -1.0f,  1.0f},  // 5: правый-нижний-передний
		{ 1.0f,  1.0f,  1.0f},  // 6: правый-верхний-передний
		{-1.0f,  1.0f,  1.0f}   // 7: левый-верхний-передний
	};

	cubeTriangles = { // куб из треугольников
		// Задняя грань (2 треугольника)
		cubeVertexes[0], cubeVertexes[1], cubeVertexes[2],  // Первый треугольник задней грани
		cubeVertexes[0], cubeVertexes[2], cubeVertexes[3],  // Второй треугольник задней грани

		// Передняя грань (2 треугольника)
		cubeVertexes[4], cubeVertexes[5], cubeVertexes[6],  // Первый треугольник передней грани
		cubeVertexes[4], cubeVertexes[6], cubeVertexes[7],  // Второй треугольник передней грани

		// Левая грань (2 треугольника)
		cubeVertexes[0], cubeVertexes[4], cubeVertexes[7],  // Первый треугольник левой грани
		cubeVertexes[0], cubeVertexes[7], cubeVertexes[3],  // Второй треугольник левой грани

		// Правая грань (2 треугольника)
		cubeVertexes[1], cubeVertexes[5], cubeVertexes[6],  // Первый треугольник правой грани
		cubeVertexes[1], cubeVertexes[6], cubeVertexes[2],  // Второй треугольник правой грани

		// Нижняя грань (2 треугольника)
		cubeVertexes[0], cubeVertexes[1], cubeVertexes[5],  // Первый треугольник нижней грани
		cubeVertexes[0], cubeVertexes[5], cubeVertexes[4],  // Второй треугольник нижней грани

		// Верхняя грань (2 треугольника)
		cubeVertexes[3], cubeVertexes[2], cubeVertexes[6],  // Первый треугольник верхней грани
		cubeVertexes[3], cubeVertexes[6], cubeVertexes[7]   // Второй треугольник верхней грани
	};
	cubeIndices = { // куб из линий
		// Задняя грань
		0, 1,  // Левый-нижний-задний -> Правый-нижний-задний
		1, 2,  // Правый-нижний-задний -> Правый-верхний-задний
		2, 3,  // Правый-верхний-задний -> Левый-верхний-задний
		3, 0,  // Левый-верхний-задний -> Левый-нижний-задний

		// Передняя грань
		4, 5,  // Левый-нижний-передний -> Правый-нижний-передний
		5, 6,  // Правый-нижний-передний -> Правый-верхний-передний
		6, 7,  // Правый-верхний-передний -> Левый-верхний-передний
		7, 4,  // Левый-верхний-передний -> Левый-нижний-передний

		// Соединяющие рёбра
		0, 4,  // Левый-нижний-задний -> Левый-нижний-передний
		1, 5,  // Правый-нижний-задний -> Правый-нижний-передний
		2, 6,  // Правый-верхний-задний -> Правый-верхний-передний
		3, 7   // Левый-верхний-задний -> Левый-верхний-передний
	};
	update();
}

void 
Scene::render() 
{
	for (auto object : objects)
	{
		object.render();
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
		std::cout << "w/h = " << (float)Window::getInstance().getWidth() / Window::getInstance().getHeight() << std::endl;
		perspectiveMatrix = glm::perspective(
			glm::radians(120.0f), // угол обзора в радианах обычно берётся в диапазоне 30-120 градусов
			(float)Window::getInstance().getWidth() / Window::getInstance().getHeight(), // соотношение сторон экрана
			0.01f, // расстояние от наблюдателя до ближней плоскости отсечения
			10.0f // расстояние от наблюдателя до дальней плоскости отсечения
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
		isPerspective = !isPerspective;
		break;
	default:
		break;
	}

	update();
}

void 
Scene::update()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);//Режим тестирования буфера глубины
	
	objects.clear();
	switch (activeTaskIdx)
	{
	case 0:
		glDisable(GL_DEPTH_TEST);
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
	Drawable rectangle1 = Drawable(*shader);
	std::vector<glm::vec3> rect1Vertexes = {
		{ -0.6f, -0.6f, -0.2f },
		{ 0.6f, -0.6f, -0.2f },
		{ 0.6f, 0.6f, -0.2f },
		{ -0.6f, 0.6f, -0.2f },
	};
	rectangle1.setVertexes(rect1Vertexes.data(), rect1Vertexes.size());
	std::vector<glm::vec3> rect1Colors = {
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
	};
	rectangle1.setColors(rect1Colors.data(), rect1Colors.size());
	objects.push_back(rectangle1);

	Drawable rectangle2 = Drawable(*shader);
	std::vector<glm::vec3> rect2Vertexes = {
		{ -0.5f, 0.8f, -0.8f },
		{ -0.5f, 0.8f, 0.8f },
		{ -0.5f, -0.8f, 0.8f },
		{ -0.5f, -0.8f, -0.8f },
	};
	rectangle2.setVertexes(rect2Vertexes.data(), rect2Vertexes.size());
	std::vector<glm::vec3> rect2Colors = {
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
	};
	rectangle2.setColors(rect2Colors.data(), rect2Colors.size());
	objects.push_back(rectangle2);

	Drawable triangle = Drawable(*shader);
	std::vector<glm::vec3> triangleVertexes = {
		{ -1.0f, -1.0f, 0.0f },
		{ 0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f },
	};
	triangle.setVertexes(triangleVertexes.data(), triangleVertexes.size());
	std::vector<glm::vec3> triangleColors = {
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },
	};
	triangle.setColors(triangleColors.data(), triangleColors.size());
	objects.push_back(triangle);
}

void
Scene::task2()
{
	task1();
}

void
Scene::task3()
{
	Drawable cube = Drawable(*shader);
	cube.setVertexes(cubeTriangles.data(), cubeTriangles.size());
	cube.setMVPmatrix(projectiveMatrix);
	cube.setMode(GL_TRIANGLES);

	objects.push_back(cube);
}

void 
Scene::task4()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

	Drawable cube = Drawable(*shader);

	cube.setVertexes(cubeVertexes.data(), cubeVertexes.size());
	cube.setIndexes(cubeIndices.data(), cubeIndices.size());
	cube.setMode(GL_LINES);
	cube.setMVPmatrix(perspectiveMatrix * viewMatrix);

	objects.push_back(cube);
}

void 
Scene::task5()
{
	glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(-25.f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(60.f), glm::vec3(0.f, 1.f, 0.f));

	Drawable cube = Drawable(*shader);

	cube.setMVPmatrix(perspectiveMatrix * viewMatrix);
	if (activeSubTaskIdx == 0)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		cube.setVertexes(cubeVertexes.data(), cubeVertexes.size());
		cube.setIndexes(cubeIndices.data(), cubeIndices.size());
		cube.setMode(GL_LINES);
	}
	else if (activeSubTaskIdx == 1)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		cube.setVertexes(cubeTriangles.data(), cubeTriangles.size());
		std::vector<glm::vec3> color;
		for (int i = 0; i < 6; i++) {
			glm::vec3 c = glm::vec3((float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX);
			for (int j = 0; j < 6; j++) {
				color.push_back(c);
			}
		}
		cube.setColors(color.data(), color.size());
		cube.setMode(GL_TRIANGLES);
	}

	objects.push_back(cube);
}

void 
Scene::task6()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));

	Drawable cube = Drawable(*shader);

	cube.setVertexes(cubeVertexes.data(), cubeVertexes.size());
	cube.setIndexes(cubeIndices.data(), cubeIndices.size());
	cube.setMode(GL_LINES);
	glm::mat4 matrix = isPerspective ? perspectiveMatrix : projectiveMatrix;
	cube.setMVPmatrix(matrix * viewMatrix);

	objects.push_back(cube);
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