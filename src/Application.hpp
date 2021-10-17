#pragma once
#include "FPS.hpp"
#include "SceneManager.hpp"

class Application
{
private:
	Fps fps;
	Engine::Scene::SceneManager sceneManager;

	void Input();
	void Update();
	void Draw();
public:
	Application();
	~Application();
	void MainLoop();
};
