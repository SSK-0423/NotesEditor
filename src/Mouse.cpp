#include <DxLib.h>
#include "Mouse.hpp"

void Input::Mouse::UpdateCounter()
{
	KeyCode nowButtonState = GetMouseInput();

	for (KeyCode keyCode = 0; keyCode < KEY_NUM; keyCode++)
	{
		// i�Ԃ̃{�^����������Ă�����
		if ((nowButtonState >> keyCode) & 1)
			UpdatePressingCounter(keyCode);
		// i�Ԃ̃L�[��������Ă�����
		else
			UpdateReleasingCounter(keyCode);
	}
}

void Input::Mouse::UpdatePressingCounter(KeyCode keyCode) const
{			
	// ������J�E���^��0���傫�����
	if (buttonReleasingCount[keyCode] > 0)
	{
		// 0�ɖ߂�
		buttonReleasingCount[keyCode] = 0;
	}
	// ������J�E���^�𑝂₷
	buttonPressingCount[keyCode]++;
	buttonPressed[keyCode] = true;
}

void Input::Mouse::UpdateReleasingCounter(KeyCode keyCode) const
{			
	// ������J�E���^��0���傫�����
	if (buttonPressingCount[keyCode] > 0)
	{
		// 0�ɖ߂�
		buttonPressingCount[keyCode] = 0;
	}
	// ������J�E���^�𑝂₷
	buttonReleasingCount[keyCode]++;
}

void Input::Mouse::GetMousePosition() const
{
	int x, y;
	GetMousePoint(&x, &y);
	mousePos.SetPosition(static_cast<float>(x), static_cast<float>(y));
}

void Input::Mouse::ReadInput()
{
	GetMousePosition();
	UpdateCounter();
}

int Input::Mouse::GetPressingCount(KeyCode keyCode) const
{
	if (IsAvailableCode(keyCode))
		return buttonPressingCount[keyCode];
	return -1;
}

int Input::Mouse::GetReleasingCount(KeyCode keyCode) const
{
	if (IsAvailableCode(keyCode))
		return buttonReleasingCount[keyCode];
	return -1;
}

bool Input::Mouse::IsPressKey(KeyCode keyCode) const
{
	if (GetPressingCount(keyCode) == 1)
		return true;
	return false;
}

bool Input::Mouse::IsReleaseKey(KeyCode keyCode) const
{
	if (GetPressingCount(keyCode) == 0 && buttonPressed[keyCode])
	{
		buttonPressed[keyCode] = false;
		return true;
	}
	return false;
}
