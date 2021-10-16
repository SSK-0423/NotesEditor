#include <DxLib.h>
#include "Mouse.hpp"

void Engine::Input::Mouse::UpdateCounter()
{
	// マウスの入力状態取得
	KeyCode nowButtonState = GetMouseInput();

	for (KeyCode keyCode = 0; keyCode < KEY_NUM; keyCode++)
	{
		// i番のボタンが押されていたら
		if ((nowButtonState >> keyCode) & 1)
			UpdatePressingCounter(keyCode);
		else
			UpdateReleasingCounter(keyCode);
	}
}

void Engine::Input::Mouse::UpdatePressingCounter(KeyCode keyCode)
{
	// 離されカウンタ初期化
	if (buttonReleasingCount[keyCode] > 0)
	{
		buttonReleasingCount[keyCode] = 0;
	}
	buttonPressingCount[keyCode]++;
	buttonPressed[keyCode] = true;
}

void Engine::Input::Mouse::UpdateReleasingCounter(KeyCode keyCode)
{			
	// 押されカウンタ初期化
	if (buttonPressingCount[keyCode] > 0)
	{
		buttonPressingCount[keyCode] = 0;
	}
	buttonReleasingCount[keyCode]++;
}

void Engine::Input::Mouse::GetMousePosition() const
{
	int x, y;
	GetMousePoint(&x, &y);
	mousePos.SetPosition(static_cast<float>(x), static_cast<float>(y));
}

void Engine::Input::Mouse::ReadInput()
{
	GetMousePosition();
	UpdateCounter();
}

int Engine::Input::Mouse::GetPressingCount(KeyCode keyCode) const
{
	if (IsAvailableCode(keyCode))
		return buttonPressingCount[keyCode];
	return -1;
}

int Engine::Input::Mouse::GetReleasingCount(KeyCode keyCode) const
{
	if (IsAvailableCode(keyCode))
		return buttonReleasingCount[keyCode];
	return -1;
}

bool Engine::Input::Mouse::IsPressKey(KeyCode keyCode) const
{
	if (GetPressingCount(keyCode) == 1)
		return true;
	return false;
}

bool Engine::Input::Mouse::IsReleaseKey(KeyCode keyCode) const
{
	if (GetPressingCount(keyCode) == 0 && buttonPressed[keyCode])
	{
		buttonPressed[keyCode] = false;
		return true;
	}
	return false;
}
