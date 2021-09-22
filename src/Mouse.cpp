#include <DxLib.h>
#include "Mouse.hpp"

namespace Game {

	namespace Input {

		//�X�V
		void Mouse::ReadInput() const 
		{
			GetMousePosition();
			UpdateCounter();
		}

		//keyCode�̃L�[��������Ă���t���[������Ԃ�
		int Mouse::GetPressingCount(KeyCode keyCode) const
		{
			if (IsAvailableCode(keyCode)) 
				return buttonPressingCount[keyCode];
			return -1;
		}

		//keyCode�̃L�[��������Ă���t���[������Ԃ�
		int Mouse::GetReleasingCount(KeyCode keyCode) const
		{
			if (IsAvailableCode(keyCode)) 
				return buttonReleasingCount[keyCode];
			return -1;
		}

		bool Mouse::IsPressKey(KeyCode keyCode) const
		{
			if (GetPressingCount(keyCode) == 1)
				return true;
			return false;
		}

		bool Mouse::IsReleaseKey(KeyCode keyCode) const
		{
			if (GetPressingCount(keyCode) == 0 && buttonPressed[keyCode])
			{
				buttonPressed[keyCode] = false;
				return true;
			}
			return false;
		}

		void Mouse::UpdateCounter() const
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

		void Mouse::UpdatePressingCounter(KeyCode keyCode) const
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

		void Mouse::UpdateReleasingCounter(KeyCode keyCode) const
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
		void Mouse::GetMousePosition() const
		{
			int x, y;
			GetMousePoint(&x,&y);
			mousePos.SetPosition(static_cast<float>(x), static_cast<float>(y));
		}
	}
}