#include "Keyboard.hpp"
#include "DxLib.h"

void Game::Input::Keyboard::UpdateCounter() const
{
	// ���݂̃L�[�̓��͏�Ԃ��i�[����
	char tmpKey[KEY_NUM];
	// �S�ẴL�[�̓��͏�Ԃ𓾂�
	GetHitKeyStateAll(tmpKey);

	for (KeyCode keyCode = 0; keyCode < KEY_NUM; keyCode++)
	{
		// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
		if (tmpKey[keyCode] != 0)
			UpdatePressingCounter(keyCode);
		// ������Ă��Ȃ����
		else
			UpdateReleasingCounter(keyCode);
	}
}

void Game::Input::Keyboard::UpdatePressingCounter(KeyCode keyCode) const
{
	// ������J�E���^��0���傫�����
	if (keyReleasingCount[keyCode] > 0)
	{
		// 0�ɖ߂�
		keyReleasingCount[keyCode] = 0;
	}
	// ���Z
	keyPressingCount[keyCode]++;
	keyPressed[keyCode] = true;
}

void Game::Input::Keyboard::UpdateReleasingCounter(KeyCode keyCode) const
{
	// ������J�E���^��0���傫�����
	if (keyPressingCount[keyCode] > 0)
	{
		// 0�ɖ߂�
		keyPressingCount[keyCode] = 0;
	}
	// ������J�E���^�𑝂₷
	keyReleasingCount[keyCode]++;
}

void Game::Input::Keyboard::ReadInput()
{
	UpdateCounter();
}

int Game::Input::Keyboard::GetPressingCount(KeyCode keyCode) const
{
	if (IsAvailableCode(keyCode))
		return keyPressingCount[keyCode];
	return -1;
}

int Game::Input::Keyboard::GetReleasingCount(KeyCode keyCode) const
{
	if (IsAvailableCode(keyCode))
		return keyReleasingCount[keyCode];
	return -1;
}

bool Game::Input::Keyboard::IsPressKey(KeyCode keyCode) const
{
	if (GetPressingCount(keyCode) == 1)
		return true;
	return false;
}

bool Game::Input::Keyboard::IsReleaseKey(KeyCode keyCode) const
{
	if (GetPressingCount(keyCode) == 0 && keyPressed[keyCode])
	{
		keyPressed[keyCode] = false;
		return true;
	}
	return false;
}
