#include "Game.hpp"
#include "WindowSize.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "DxLib.h"

Game::Game::Game()
{
	//�E�B���h�E���[�h�A�������A����ʐݒ�
	SetGraphMode(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, 16);
	ChangeWindowMode(true), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(true);
}

void Game::Game::MainLoop()
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
	DxLib_End();
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
