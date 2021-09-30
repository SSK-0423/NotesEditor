#pragma once
#include "FPS.hpp"
#include "SceneManager.hpp"

class Application
{
private:
	Fps fps;
	Engine::Scene::SceneManager sceneManager;

	void Input();
	void Draw();
	void Update();
public:
	Application();
	void MainLoop();
};
