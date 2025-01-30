#include "SceneManager.h"

SceneManager SceneManager::instanse = SceneManager();

SceneManager&
SceneManager::getInstanse()
{
	return SceneManager::instanse;
}

int
SceneManager::getCurrentSceneIdx()
{
	return currentSceneIdx;
}

void
SceneManager::setCurrentSceneIdx(int sceneIdx)
{
	currentSceneIdx = sceneIdx;
	scene->updateSceneContent();
}

int
SceneManager::getCurrentSubSceneIdx()
{
	return currentSubSceneIdx;
}

void
SceneManager::setCurrentSubSceneIdx(int subSceneIdx)
{
	currentSubSceneIdx = subSceneIdx;
	scene->updateSceneContent();
}

Scene*&
SceneManager::getScene()
{
	return scene;
}

void
SceneManager::setScene(Scene*& scene)
{
	this->scene = scene;
}

SceneManager::SceneManager() : currentSceneIdx(0),
currentSubSceneIdx(0),
scene(new Scene())
{}

SceneManager::~SceneManager()
{
	delete scene;
}