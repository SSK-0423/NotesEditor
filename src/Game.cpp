#include "Game.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "DxLib.h"

Game::Game()
{
}

void Game::MainLoop()
{
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		// ���͓ǂݎ��
		Input();
		// �X�V
		Update();
		// �`��
		Draw();

		fps.Update();
		fps.Draw();
		fps.Wait();
	}
}

void Game::Input()
{
	Input::Mouse::Instance().ReadInput();
	Input::Keyboard::Instance().ReadInput();
}

void Game::Update()
{
	sceneManager.Update();
}

void Game::Draw()
{
	sceneManager.Draw();
}
