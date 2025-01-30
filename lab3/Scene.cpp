#include "Scene.h"

#include <iostream>
#include <cmath>

#include "SceneManager.h"
#include "Window.h"
#include "Constants.h"

Scene::Scene() : activeTaskIdx(0), activeSubTaskIdx(0), objects({}) {}

Scene::~Scene() {}

void
Scene::onEntry()
{
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
	std::cout << "event come to Scene" << std::endl;
	switch (event->type)
	{
	case Event::Type::KEY_PRESS:
		processKeyPressEvent((KeyPressEvent*)event);
		break;
	case Event::Type::WINDOW_RESIZE:
		update();
		break;
	default:
		break;
	}
}

void 
Scene::onExit() 
{	
}

void 
Scene::processKeyPressEvent(KeyPressEvent* event)
{
	if (GLFW_KEY_1 <= event->key && GLFW_KEY_3 >= event->key)
	{
		activeTaskIdx = event->key - GLFW_KEY_1;
		std::cout << "activeTaskIdx = " << activeTaskIdx << std::endl;
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
		activeSubTaskIdx = 2;
		break;
	case GLFW_KEY_D:
		activeSubTaskIdx = 3;
		break;
	default:
		break;
	}

	update();
}

void 
Scene::update()
{
	objects.clear();
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
	default:
		break;
	}
}

void 
Scene::task1()
{
	int n = 8;
	Shader shader = Shader("mono_vs.glsl", "mono_fs.glsl");

	std::vector<glm::vec3> vertexes = genPolygonNormalize(n, 400, 400);

	Drawable object = Drawable(shader);

	object.setVertexes(vertexes.data(), vertexes.size());

	std::vector<GLuint> indexes;
	std::vector<glm::vec3> colors;
	int l, r;
	switch (activeSubTaskIdx)
	{
	case 0:
		l = 0; r = vertexes.size();
		indexes.push_back(0);
		while (l != r && l != r - 1)
		{
			l++;
			r--;

			indexes.push_back(l);
			indexes.push_back(r);
			colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
			colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		}
		object.setMode(GL_TRIANGLE_STRIP);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 1:
		for (int i = 0; i < vertexes.size(); i++) {
			for (int j = i + 2; j < vertexes.size(); j++) {
				if ((i == 0) && (j == vertexes.size() - 1))
					continue;
				if ((j != i - 1) && (j != i + 1)) {
					indexes.push_back(i);
					indexes.push_back(j);
					colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
				}
			}
		}
		object.setMode(GL_LINES);
		break;
	case 2:
		for (int i = 0; i < vertexes.size(); i++) {
			indexes.push_back(i);
		}
		object.setMode(GL_LINE_LOOP);
		break;
	case 3:
		for (int i = 0; i < vertexes.size(); i++) {
			if (i % 2 == 0)
			{
				indexes.push_back(i);
				colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
				colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
			}
		}
		glLineWidth(7);
		object.setMode(GL_LINE_STRIP);
		break;
	default:
		break;
	}

	if (!colors.empty())
		object.setColors(colors.data(), colors.size());
	object.setIndexes(indexes.data(), indexes.size());

	objects.push_back(object);

	glLineWidth(3);
}

void
Scene::task2()
{
	if (activeSubTaskIdx >= 2)
	{
		activeSubTaskIdx = 0;
	}

	Shader shader = Shader("matrix_vs.glsl", "mono_fs.glsl");

	Drawable rectangle = Drawable(shader);
	Drawable triangle = Drawable(shader);
	Drawable line = Drawable(shader);

	Window& window = Window::getInstance();

	glm::mat4 ortho = glm::ortho(0.0f, (float)window.getWidth(), 0.0f, (float)window.getHeight(), -1.0f, 1.0f);

	// создание вершин для треугольника
	glm::vec2 triangleCenter(window.getWidth() * 0.2, window.getHeight() / 2.f);
	std::vector<glm::vec3> triangleVertexes = genPolygon(3, 100, 100, triangleCenter.x, triangleCenter.y, -M_PI/6);
	triangle.setVertexes(triangleVertexes.data(), triangleVertexes.size());
	triangle.setMode(GL_LINE_LOOP);

	// создание вершин для прямоугольника
	glm::vec2 rectangleCenter(window.getWidth() * 0.8f, window.getHeight() / 2.f);
	std::vector<glm::vec3> rectangleVertexes = genPolygon(4, 150, 100, rectangleCenter.x, rectangleCenter.y, M_PI / 4);
	rectangle.setVertexes(rectangleVertexes.data(), rectangleVertexes.size());
	rectangle.setMode(GL_LINE_LOOP);

	// cоздание вершин для линии
	glm::vec2 lineCenter(window.getWidth() / 2.f, window.getHeight() / 2.f);
	std::vector<glm::vec3> lineVertexes = genPolygon(2, 100, 100, lineCenter.x, lineCenter.y);
	line.setVertexes(lineVertexes.data(), lineVertexes.size());
	line.setMode(GL_LINE_LOOP);

	std::vector<glm::vec3> red = {
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f}
	};

	std::vector<glm::vec3> green = {
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f}
	};

	switch (activeSubTaskIdx)
	{
	case 1:
		// Поворот линии
		glm::mat4 transformMatrix = 
			glm::translate(glm::mat4(1.0f), glm::vec3(lineCenter, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians<float>(40), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::translate(glm::mat4(1.0f), glm::vec3(-lineCenter, 0.0f));

		line.setMVPmatrix(ortho * transformMatrix);
		line.setColors(green.data(), green.size());

		// Поворот прямоугольника относительно точки
		glm::vec2 rectanglePointOfRotate = glm::vec2(-3., -8.);
		transformMatrix =
			glm::translate(glm::mat4(1.0f), glm::vec3(rectanglePointOfRotate, 0)) *
			glm::rotate(glm::mat4(1.0f), glm::radians<float>(-25), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::translate(glm::mat4(1.0f), glm::vec3(-rectanglePointOfRotate, 0.));

		rectangle.setMVPmatrix(ortho * transformMatrix);
		rectangle.setColors(green.data(), green.size());

		// треугольник
		transformMatrix =
			glm::translate(glm::mat4(1.0f), glm::vec3(0.3f * (window.getWidth() / 2.f), 0.5f * (window.getHeight() / 2.f), 0.f)) *
			glm::translate(glm::mat4(1.0f), glm::vec3(triangleCenter, 0.)) *
			glm::scale(glm::mat4(1.f), glm::vec3(1.2, 1.5, 1.0)) *
			glm::translate(glm::mat4(1.0f), glm::vec3(-triangleCenter, 0.));

		triangle.setMVPmatrix(ortho * transformMatrix);
		triangle.setColors(green.data(), green.size());
		break;
	default:
		triangle.setMVPmatrix(ortho);
		triangle.setColors(red.data(), red.size());

		rectangle.setMVPmatrix(ortho);
		rectangle.setColors(red.data(), red.size());

		line.setMVPmatrix(ortho);
		line.setColors(red.data(), red.size());
		break;
	}

	objects.push_back(triangle);
	objects.push_back(rectangle);
	objects.push_back(line);
}

void
Scene::task3()
{
	Shader shader("matrix_vs.glsl", "mono_fs.glsl");

	Window window = Window::getInstance();
	glm::vec2 center = glm::vec2(window.getWidth() / 2.f, window.getHeight() / 2.f);

	glm::mat4 ortho = glm::ortho(0.0f, (float)window.getWidth(), 0.0f, (float)window.getHeight(), -1.0f, 1.0f);

	std::vector<glm::vec3> red = {
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
	};

	float angle = 135, step = 45;
	for (int i = 0; i < 3; i++)
	{
		Drawable line = Drawable(shader);
		line.setMode(GL_LINE_LOOP);
		std::vector<glm::vec3> vertexes = genPolygon(2, 100, 100, center.x, center.y);
		line.setVertexes(vertexes.data(), vertexes.size());
		glm::mat4 transformMatrix =
			glm::translate(glm::mat4(1.0f), glm::vec3(center, 0.f)) *
			glm::rotate(glm::mat4(1.f), glm::radians<float>(angle), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::translate(glm::mat4(1.0f), glm::vec3(-center, 0.f));
		line.setMVPmatrix(ortho * transformMatrix);
		line.setColors(red.data(), red.size());

		angle -= step;
		objects.push_back(line);
	}
}

std::vector<glm::vec3> 
Scene::genPolygonNormalize(int n, int scaleX, int scaleY, float offsetX, float offsetY, float rotation)
{
	std::vector<glm::vec3> points;
	float offsetAngle = (360. / (float)n) / 180. * M_PI;

	Window& window = Window::getInstance();
	std::cout << window.getWidth() << " " << window.getHeight();
	for (int i = 0; i < n; i++)
	{
		float x = scaleX * cos(offsetAngle * i + rotation) / window.getWidth() + offsetX;
		float y = scaleY * sin(offsetAngle * i + rotation) / window.getHeight() + offsetY;
		std::cout << x << " " << y << std::endl;
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
	std::cout << window.getWidth() << " " << window.getHeight();
	for (int i = 0; i < n; i++) 
	{
		float x = scaleX * cos(offsetAngle * i + rotation) + offsetX;
		float y = scaleY * sin(offsetAngle * i + rotation) + offsetY;
		std::cout << x << " " << y << std::endl;
		points.push_back({ x, y, 0.0f });
	}

	return points;
}