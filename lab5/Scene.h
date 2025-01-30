#pragma once

#include <vector>
#include "opengl_libs.h"


#include "Events.hpp"
#include "Drawable.h"

/// <summary>
/// класс, отвечающий за сцену
/// </summary>
class Scene
{
public:
	Scene();
	~Scene();

	/// <summary>
	/// Функция, вызываемая при входе на сцену
	/// </summary>
	void onEntry();
	
	/// <summary>
	/// Функция отрисовки
	/// </summary>
	void render();

	void processEvents(Event* event);
	
	/// <summary>
	/// Выход со сцены
	/// </summary>
	void onExit();

private:
	/// <summary>
	/// Метод обработки ивентов нажатия на клавиши
	/// </summary>
	/// <param name="key"></param>
	void processKeyPressEvent(KeyPressEvent* event);

	/// <summary>
	/// Функция обновления сцены
	/// </summary>
	void update();

	void task1();

	void task2();

	void task3();

	void task4();
	
	void task5();

	void task6();

	std::vector<glm::vec3> genPolygonNormalize(int n, int scaleX, int scaleY, float offsetX = 0, float offsetY = 0, float rotation = 0);
	std::vector<glm::vec3> genPolygon(int n, int scaleX, int scaleY, float offsetX = 0, float offsetY = 0, float rotation = 0);

	/// <summary>
	/// Индекс активной задачи
	/// </summary>
	int activeTaskIdx;
	
	/// <summary>
	/// Индекс подзадачи
	/// </summary>
	int activeSubTaskIdx;

	/// <summary>
	/// Массив объектов
	/// </summary>
	std::vector<Drawable*> objects;

	Shader* shader;

	glm::mat4 perspectiveMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 modelScaleMatrix;

	float distanation;
	float speed;
	float dt;
	float lt;
	float angle;
	float offset;
};