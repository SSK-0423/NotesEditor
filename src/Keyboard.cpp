#include "Keyboard.hpp"
#include "DxLib.h"

void Input::Keyboard::UpdateCounter() const
{
	// 現在のキーの入力状態を格納する
	char tmpKey[KEY_NUM];
	// 全てのキーの入力状態を得る
	GetHitKeyStateAll(tmpKey);

	for (KeyCode keyCode = 0; keyCode < KEY_NUM; keyCode++)
	{
		// i番のキーコードに対応するキーが押されていたら
		if (tmpKey[keyCode] != 0)
			UpdatePressingCounter(keyCode);
		// 押されていなければ
		else
			UpdateReleasingCounter(keyCode);
	}
}

void Input::Keyboard::UpdatePressingCounter(KeyCode keyCode) const
{
	// 離されカウンタが0より大きければ
	if (keyReleasingCount[keyCode] > 0)
	{
		// 0に戻す
		keyReleasingCount[keyCode] = 0;
	}
	// 加算
	keyPressingCount[keyCode]++;
	keyPressed[keyCode] = true;
}

void Input::Keyboard::UpdateReleasingCounter(KeyCode keyCode) const
{
	// 押されカウンタが0より大きければ
	if (keyPressingCount[keyCode] > 0)
	{
		// 0に戻す
		keyPressingCount[keyCode] = 0;
	}
	// 離されカウンタを増やす
	keyReleasingCount[keyCode]++;
}

void Input::Keyboard::ReadInput()
{
	UpdateCounter();
}

int Input::Keyboard::GetPressingCount(KeyCode keyCode) const
{
	if (IsAvailableCode(keyCode))
		return keyPressingCount[keyCode];
	return -1;
}

int Input::Keyboard::GetReleasingCount(KeyCode keyCode) const
{
	if (IsAvailableCode(keyCode))
		return keyReleasingCount[keyCode];
	return -1;
}

bool Input::Keyboard::IsPressKey(KeyCode keyCode) const
{
	if (GetPressingCount(keyCode) == 1)
		return true;
	return false;
}

bool Input::Keyboard::IsReleaseKey(KeyCode keyCode) const
{
	if (GetPressingCount(keyCode) == 0 && keyPressed[keyCode])
	{
		keyPressed[keyCode] = false;
		return true;
	}
	return false;
}
