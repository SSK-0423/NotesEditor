#include "Keyboard.hpp"
#include "DxLib.h"

void Engine::Input::Keyboard::UpdateCounter()
{
	// 現在のキーの入力状態を格納する
	char tmpKey[KEY_NUM];
	// 全てのキーの入力状態を得る
	GetHitKeyStateAll(tmpKey);

	for (KeyCode keyCode = 0; keyCode < KEY_NUM; keyCode++)
	{
		if (tmpKey[keyCode] != 0)
			UpdatePressingCounter(keyCode);
		else
			UpdateReleasingCounter(keyCode);
	}
}

void Engine::Input::Keyboard::UpdatePressingCounter(KeyCode keyCode)
{
	// 離されカウンタ初期化
	if (keyReleasingCount[keyCode] > 0)
	{
		keyReleasingCount[keyCode] = 0;
	}
	keyPressingCount[keyCode]++;
	keyPressed[keyCode] = true;
}

void Engine::Input::Keyboard::UpdateReleasingCounter(KeyCode keyCode)
{
	// 押されカウンタ初期化
	if (keyPressingCount[keyCode] > 0)
	{
		keyPressingCount[keyCode] = 0;
	}
	keyReleasingCount[keyCode]++;
}

void Engine::Input::Keyboard::ReadInput()
{
	UpdateCounter();
}

int Engine::Input::Keyboard::GetPressingCount(KeyCode keyCode) const
{
	if (IsAvailableCode(keyCode))
		return keyPressingCount[keyCode];
	return -1;
}

int Engine::Input::Keyboard::GetReleasingCount(KeyCode keyCode) const
{
	if (IsAvailableCode(keyCode))
		return keyReleasingCount[keyCode];
	return -1;
}

bool Engine::Input::Keyboard::IsPressKey(KeyCode keyCode) const
{
	if (GetPressingCount(keyCode) == 1)
		return true;
	return false;
}

bool Engine::Input::Keyboard::IsReleaseKey(KeyCode keyCode) const
{
	if (GetPressingCount(keyCode) == 0 && keyPressed[keyCode])
	{
		keyPressed[keyCode] = false;
		return true;
	}
	return false;
}
