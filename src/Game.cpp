#include "Game.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "DxLib.h"

Game::Game::Game()
{
}

void Game::Game::MainLoop()
{
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		// “ü—Í“Ç‚İæ‚è
		Input();
		// XV
		Update();
		// •`‰æ
		Draw();

		fps.Update();
		fps.Draw();
		fps.Wait();
	}
}

void Game::Game::Input()
{
	Input::Mouse::Instance().ReadInput();
	Input::Keyboard::Instance().ReadInput();
}

void Game::Game::Update()
{
	sceneManager.Update();
}

void Game::Game::Draw()
{
	sceneManager.Draw();
}
