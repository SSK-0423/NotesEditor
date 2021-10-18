#include "Application.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "DxLib.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::MainLoop()
{
	while (ScreenFlip() == 0 && ClearDrawScreen() == 0)
	{
		if (ProcessMessage() != 0)
			break;

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

void Application::Input()
{
	Engine::Input::Mouse::Instance().ReadInput();
	Engine::Input::Keyboard::Instance().ReadInput();
}

void Application::Update()
{
	sceneManager.Update();
}

void Application::Draw()
{
	sceneManager.Draw();
}
