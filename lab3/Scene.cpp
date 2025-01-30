#include "Scene.h"

#include <cmath>
#include <random>

#include "SceneManager.h"
#include "ShadersManager.h"
#include "constants.h"

#include <glm/gtc/matrix_transform.hpp>

#define N 8
#define SCALE 100
#define LEN_UNIT 100

Scene::Scene() : objects(std::vector<Object>()),
window(Window::getInstanse())
{}

void
Scene::updateSceneContent()
{
	objects.clear();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	switch (SceneManager::getInstanse().getCurrentSceneIdx())
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
	case 6:
		task7();
		break;
	case 7:
		task8();
		break;
	default:
		break;
	}
}

void
Scene::display()
{
	for (Object& object : objects) {
		object.render();
	}
}

Scene::~Scene()
{}

void
Scene::task1()
{
	Object object = Object();
	std::vector<glm::vec3> points = createRegularPolygon(N, 4 * SCALE, 4 * SCALE, 0, 0, 0, true);

	std::vector<glm::vec3> colors;
	std::vector<GLuint> indexes;
	glLineWidth(3);
	int l, r;
	switch (SceneManager::getInstanse().getCurrentSubSceneIdx())
	{
	case 0:
		l = 0; r = points.size();
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
		for (int i = 0; i < points.size(); i++) {
			for (int j = i + 2; j < points.size(); j++) {
				if ((i == 0) && (j == points.size() - 1))
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
		for (int i = 0; i < points.size(); i++) {
			indexes.push_back(i);
		}
		object.setMode(GL_LINE_LOOP);
		break;
	case 3:
		for (int i = 0; i < points.size(); i++) {
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

	if (!colors.empty()) {
		object.loadColors(colors.data(), colors.size());
	}
	object.loadCoords(points.data(), points.size());
	object.loadIndexes(indexes.data(), indexes.size());
	object.setShaderProgram(ShadersManager::getInstanse().getShaderProgram("mono"));

	objects.push_back(object);
}

void
Scene::task2()
{
	Object triangle = Object();
	Object rectangle = Object();
	Object line = Object();

	glm::mat4 projection = glm::ortho(0.0f, 
									  static_cast<float>(window.getWidth()), 
									  0.0f, 
									  static_cast<float>(window.getHeight()), 
									  -1.0f, 
									  1.0f);

	std::vector<glm::vec3> red = {
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
	};

	std::vector<glm::vec3> trianglePoints = createRegularPolygon(3, 0.3, 0.3, -PI / 6, 0, 0.6, false);
	std::vector<glm::vec3> rectanglePoints = createRegularPolygon(4, 0.3, 0.3, PI/4, 0, 0.0, false);
	std::vector<glm::vec3> linePoints = createRegularPolygon(2, 0.3, 0.3, 0, 0, -0.6f, false);

	triangle.loadCoords(trianglePoints.data(), trianglePoints.size());
	rectangle.loadCoords(rectanglePoints.data(), rectanglePoints.size());
	line.loadCoords(linePoints.data(), linePoints.size());

	triangle.setShaderProgram(ShadersManager::getInstanse().getShaderProgram("matrix"));
	rectangle.setShaderProgram(ShadersManager::getInstanse().getShaderProgram("matrix"));
	line.setShaderProgram(ShadersManager::getInstanse().getShaderProgram("matrix"));
	
	rectangle.setMode(GL_LINE_LOOP);
	triangle.setMode(GL_LINE_LOOP);
	line.setMode(GL_LINE_LOOP);

	triangle.loadColors(red.data(), red.size());
	rectangle.loadColors(red.data(), red.size());
	line.loadColors(red.data(), red.size());
	
	objects.push_back(triangle);
	objects.push_back(rectangle);
	objects.push_back(line);
}

void
Scene::task3()
{
	Object object = Object();
	std::vector<glm::vec3> points = {
		{-0.7f, 0.1f, 0.0f},
		{-0.5f, 0.6f, 0.0f},
		{-0.4f, -0.5f, 0.0f},
		{-0.4f, 0.2f, 0.0f},
		{0.2f, 0.2f, 0.0f},
		{0.2f, 0.6f, 0.0f},
		{0.6f, -0.3f, 0.0f},
	};

	object.loadCoords(points.data(), points.size());
	object.loadShaders("mono_vs.glsl", "mono_fs.glsl");
	glLineWidth(3);
	glEnable(GL_LINE_SMOOTH);

	object.setMode(GL_LINE_STRIP);
	objects.push_back(object);
}

void
Scene::task4()
{
	Object object = Object();

	std::vector<glm::vec3> points = {
		{-0.7f, -0.5f, 0.0f},
		{-0.5f, 0.7f, 0.0f},
		{0.4f, 0.9f, 0.0f},
		{0.3f, 0.3f, 0.0f},
		{0.7f, 0.5f, 0.0f},
		{0.7f, -0.2f, 0.0f},
		{0.3f, -0.2f, 0.0f},
		{0.3f, -0.9f, 0.0f},
		{-0.2f, -0.2f, 0.0f},
	};

	object.loadCoords(points.data(), points.size());
	object.loadShaders("mono_vs.glsl", "mono_fs.glsl");
	glLineWidth(3);
	glEnable(GL_LINE_SMOOTH);

	object.setMode(GL_LINE_LOOP);
	objects.push_back(object);
}

void
Scene::task5()
{
	std::vector<glm::vec3> colors;

	for (int i = 0; i < 10; i++) {
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
	}

	switch (SceneManager::getInstanse().getCurrentSubSceneIdx())
	{
	case 0:
		task5A(colors);
		break;
	case 1:
		task5B(colors);
		break;
	case 2:
		task5C(colors);
		break;
	default:
		task5A(colors);
		break;
	}
}

void
Scene::task6()
{
	Object object = Object();

	std::vector<glm::vec3> points;

	double offsetAngle = (360. / N) / 180. * PI;

	for (int i = 0; i < N; i++) {
		double x = SCALE * std::cos(offsetAngle * i) / window.getWidth();
		double y = SCALE * std::sin(offsetAngle * i) / window.getHeight();
		points.push_back(glm::vec3(x, y, 0));
		std::cout << x << " " << y << std::endl;
	}

	std::vector<glm::vec3> colors;
	for (int i = 0; i < 10; i++) {
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
	}

	object.loadCoords(points.data(), points.size());
	object.loadColors(colors.data(), colors.size());
	object.setMode(GL_TRIANGLE_FAN);

	objects.push_back(object);
}

void
Scene::task7()
{
	Object object = Object();

	std::vector<glm::vec3> points = {
		{-0.5f, 0.1f, 0.0f},
		{-0.5f, 0.7f, 0.0f},
		{-0.2f, 0.1f, 0.0f},

		{-0.5f, 0.7f, 0.0f},
		{-0.2f, 0.1f, 0.0f},
		{-0.2f, 0.4f, 0.0f},

		{-0.5f, 0.7f, 0.0f},
		{-0.2f, 0.4f, 0.0f},
		{0.7f, 0.5f, 0.0f},

		{-0.2f, 0.4f, 0.0f},
		{0.7f, 0.5f, 0.0f},
		{0.1f, -0.4f, 0.0f},

		{0.7f, 0.5f, 0.0f},
		{0.1f, -0.4f, 0.0f},
		{0.5f, -0.7f, 0.0f},

		{0.1f, -0.4f, 0.0f},
		{0.5f, -0.7f, 0.0f},
		{-0.2f, -0.4f, 0.0f},

		{0.5f, -0.7f, 0.0f},
		{-0.2f, -0.4f, 0.0f},
		{-0.6f, -0.5f, 0.0f},

		{-0.2f, -0.4f, 0.0f},
		{-0.6f, -0.5f, 0.0f},
		{-0.35f, 0.1f, 0.0f}
	};

	object.loadCoords(points.data(), points.size());

	std::vector<glm::vec3> colors;

	for (int i = 0; i < 10; i++) {
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
	}

	object.loadColors(colors.data(), colors.size());

	switch (SceneManager::getInstanse().getCurrentSubSceneIdx())
	{
	case 0:
		object.loadShaders("mono_vs.glsl", "mono_fs.glsl");
		break;
	case 1:
		object.loadShaders("grad_vs.glsl", "grad_fs.glsl");
		break;
	default:
		object.loadShaders("mono_vs.glsl", "mono_fs.glsl");
		break;
	}

	object.setMode(GL_TRIANGLES);

	objects.push_back(object);
}

void
Scene::task8()
{
	Object object = Object();

	std::vector<glm::vec3> points = {
		{-0.5f, 0.1f, 0.0f},
		{-0.5f, 0.7f, 0.0f},
		{-0.2f, 0.1f, 0.0f},

		{-0.5f, 0.7f, 0.0f},
		{-0.2f, 0.1f, 0.0f},
		{-0.2f, 0.4f, 0.0f},

		{-0.5f, 0.7f, 0.0f},
		{-0.2f, 0.4f, 0.0f},
		{0.7f, 0.5f, 0.0f},

		{-0.2f, 0.4f, 0.0f},
		{0.7f, 0.5f, 0.0f},
		{0.1f, -0.4f, 0.0f},

		{0.7f, 0.5f, 0.0f},
		{0.1f, -0.4f, 0.0f},
		{0.5f, -0.7f, 0.0f},

		{0.1f, -0.4f, 0.0f},
		{0.5f, -0.7f, 0.0f},
		{-0.2f, -0.4f, 0.0f},

		{0.5f, -0.7f, 0.0f},
		{-0.2f, -0.4f, 0.0f},
		{-0.6f, -0.5f, 0.0f},

		{-0.2f, -0.4f, 0.0f},
		{-0.6f, -0.5f, 0.0f},
		{-0.35f, 0.1f, 0.0f}
	};

	object.loadCoords(points.data(), points.size());

	std::vector<glm::vec3> colors;

	for (int i = 0; i < 10; i++) {
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
	}

	object.loadColors(colors.data(), colors.size());

	object.loadShaders("mono_vs.glsl", "mono_fs.glsl");
	switch (SceneManager::getInstanse().getCurrentSubSceneIdx())
	{
	case 0:
		glPolygonMode(GL_FRONT, GL_POINT);
		break;
	case 1:
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_LINE);
		break;
	case 2:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	default:
		glPolygonMode(GL_FRONT, GL_POINT);
		break;
	}
	object.setMode(GL_TRIANGLES);

	objects.push_back(object);
}

void
Scene::task5A(std::vector<glm::vec3> colors)
{
	Object object = Object();

	std::vector<glm::vec3> points = {
		{-0.7f, -0.5f, 0.0f},
		{-0.5f, 0.7f, 0.0f},
		{-0.2f, -0.2f, 0.0f},

		{-0.5f, 0.7f, 0.0f},
		{-0.2f, -0.2f, 0.0f},
		{0.4f, 0.9f, 0.0f},

		{0.4f, 0.9f, 0.0f},
		{0.3f, 0.3f, 0.0f},
		{-0.2f, -0.2f, 0.0f},

		{0.3f, 0.3f, 0.0f},
		{0.7f, 0.5f, 0.0f},
		{0.7f, -0.2f, 0.0f},

		{0.7f, -0.2f, 0.0f},
		{0.3f, -0.2f, 0.0f},
		{0.3f, 0.3f, 0.0f},

		{0.3f, -0.2f, 0.0f},
		{0.3f, -0.9f, 0.0f},
		{-0.2f, -0.2f, 0.0f},

		{0.3f, 0.3f, 0.0f},
		{0.3f, -0.2f, 0.0f},
		{-0.2f, -0.2f, 0.0f},
	};

	object.loadCoords(points.data(), points.size());
	object.loadColors(colors.data(), colors.size());
	object.setMode(GL_TRIANGLES);

	objects.push_back(object);
}

void
Scene::task5B(std::vector<glm::vec3> colors)
{
	Object object1 = Object();
	Object object2 = Object();

	std::vector<glm::vec3> points1 = {
		{-0.7f, -0.5f, 0.0f}, // 1
		{-0.5f, 0.7f, 0.0f}, // 2
		{-0.2f, -0.2f, 0.0f}, // 9
		{0.4f, 0.9f, 0.0f}, // 3
		{0.3f, 0.3f, 0.0f}, // 4
	};

	std::vector<glm::vec3> points2 = {
		{0.3f, -0.9f, 0.0f}, // 8
		{-0.2f, -0.2f, 0.0f}, // 9
		{0.3f, -0.2f, 0.0f}, // 7
		{0.3f, 0.3f, 0.0f}, // 4
		{0.7f, -0.2f, 0.0f}, // 6
		{0.7f, 0.5f, 0.0f}, // 5
	};

	object1.loadCoords(points1.data(), points1.size());
	object1.loadColors(colors.data(), colors.size());
	object1.setMode(GL_TRIANGLE_STRIP);
	objects.push_back(object1);

	colors.clear();
	for (int i = 0; i < 10; i++) {
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
	}

	object2.loadCoords(points2.data(), points2.size());
	object2.loadColors(colors.data(), colors.size());
	object2.setMode(GL_TRIANGLE_STRIP);
	objects.push_back(object2);
}

void
Scene::task5C(std::vector<glm::vec3> colors)
{
	Object object1 = Object();
	Object object2 = Object();

	std::vector<glm::vec3> points1 = {
		{-0.7f, -0.5f, 0.0f}, // 1
		{-0.5f, 0.7f, 0.0f}, // 2
		{0.4f, 0.9f, 0.0f}, // 3
		{0.3f, 0.3f, 0.0f}, // 4
		{-0.2f, -0.2f, 0.0f}, // 9
	};

	std::vector<glm::vec3> points2 = {
		{0.3f, -0.2f, 0.0f}, // 7
		{0.3f, -0.9f, 0.0f}, // 8
		{-0.2f, -0.2f, 0.0f}, // 9
		{0.3f, 0.3f, 0.0f}, // 4
		{0.7f, 0.5f, 0.0f}, // 5
		{0.7f, -0.2f, 0.0f}, // 6
	};

	object1.loadCoords(points1.data(), points1.size());
	object1.loadColors(colors.data(), colors.size());
	object1.setMode(GL_TRIANGLE_FAN);
	objects.push_back(object1);

	colors.clear();
	for (int i = 0; i < 10; i++) {
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
		colors.push_back({ (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX });
	}

	object2.loadCoords(points2.data(), points2.size());
	object2.loadColors(colors.data(), colors.size());
	object2.setMode(GL_TRIANGLE_FAN);
	objects.push_back(object2);
}

std::vector<glm::vec3> 
Scene::createRegularPolygon(int n, 
							double scaleX, 
							double scaleY, 
							double rotation, 
							double offsetX, 
							double offsetY, 
							bool isNormalized)
{
	std::vector<glm::vec3> points;

	double offsetAngle = (360. / n) / 180. * PI;

	for (int i = 0; i < N; i++) {
		double x = scaleX * std::cos(offsetAngle * i + rotation);
		if (isNormalized)
			x /= Window::getInstanse().getWidth();
		x += offsetX;
		double y = scaleY * std::sin(offsetAngle * i + rotation);
		if (isNormalized)
			y /= Window::getInstanse().getHeight();
		y += offsetY;
		points.push_back(glm::vec3(x, y, 0));
	}

	return points;
}