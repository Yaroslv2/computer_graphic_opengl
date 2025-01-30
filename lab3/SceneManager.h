#pragma once

#include "Scene.h"
#include "Events.hpp"

/// <summary>
/// Синглтон. Отвечает за работу со сценами извне
/// </summary>
class SceneManager
{
public:
	static SceneManager& getInstanse();
	/// <summary>
	/// Открытие новой сцены
	/// </summary>
	/// <param name="scene">Указатель на новую сцену, которую необходимо открыть</param>
	void changeScene(Scene* scene);
	/// <summary>
	/// Функция обработки событй, временно недоступно
	/// </summary>
	void processEvents(Event* event);
	/// <summary>
	/// Функция отрисовки сцены
	/// </summary>
	void render();
	~SceneManager();
private:
	SceneManager();
	static SceneManager instanse;
	/// <summary>
	/// Активная сцена
	/// </summary>
	Scene* activeScene;
};