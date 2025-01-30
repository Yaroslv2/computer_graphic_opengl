#pragma once
#include "Scene.h"

class SceneManager
{
public:
	static SceneManager& getInstanse();

	int getCurrentSceneIdx();
	void setCurrentSceneIdx(int sceneIdx);

	int getCurrentSubSceneIdx();
	void setCurrentSubSceneIdx(int subSceneIdx);

	Scene*& getScene();
	void setScene(Scene*& scene);

	~SceneManager();
private:
	SceneManager();
	static SceneManager instanse;

	int currentSceneIdx;
	int currentSubSceneIdx;
	Scene* scene;
};

