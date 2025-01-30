#pragma once

#include <vector>

#include "Object.h"
#include "Window.h"

class Scene
{
public:
	Scene();
	void updateSceneContent();
	void display();
	~Scene();

private:
	std::vector<Object> objects;
	Window& window;
	void task1();

	void task2();
	void task3();
	void task4();
	void task5();
	void task6();
	void task7();
	void task8();

	void task5A(std::vector<glm::vec3> colors);
	void task5B(std::vector<glm::vec3> colors);
	void task5C(std::vector<glm::vec3> colors);

	std::vector<glm::vec3> createRegularPolygon(int n, double scaleX, double scaleY, double rotation, double offsetX, double offsetY, bool isNormalized);
};