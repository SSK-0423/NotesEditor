#pragma once
#include "FPS.hpp"
#include "SceneManager.hpp"

namespace Game
{
	class Game
	{
	private:
		Fps fps;
		Scene::SceneManager sceneManager;

		void Input();
		void Draw();
		void Update();
	public:
		Game();
		void MainLoop();
	};
}