#include "SceneManager.h"

#include <iostream>

SceneManager SceneManager::instanse = SceneManager::SceneManager();

SceneManager& 
SceneManager::getInstanse()
{
	return instanse;
}

void 
SceneManager::changeScene(Scene* scene)
{
	if (activeScene != nullptr) 
	{
		activeScene->onExit();
		delete activeScene;
	}
	activeScene = scene;
	scene->onEntry();
}

void 
SceneManager::processEvents(Event* event)
{
	if (activeScene == nullptr)
		return;

	activeScene->processEvents(event);
}

void 
SceneManager::render()
{
	if (activeScene == nullptr)
		return;
	activeScene->render();
}

SceneManager::~SceneManager()
{
	activeScene->onExit();
	delete activeScene;
}

SceneManager::SceneManager() : activeScene(nullptr) {}