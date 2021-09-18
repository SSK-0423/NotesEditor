#include <DxLib.h>
#include "Mouse.hpp"

namespace Game {

	namespace Input {

		//�X�V
		void Mouse::ReadInput() const 
		{
			GetMousePoint(&mousePos.x, &mousePos.y);
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
			if (GetReleasingCount(keyCode) != 0 && buttonPressed[keyCode])
			{
				buttonPressed[keyCode] = false;
				return true;
			}
			return false;
		}

		void Mouse::UpdateCounter() const
		{
			int nowButtonState = GetMouseInput();

			for (int i = 0; i < KEY_NUM; i++) 
			{
				// i�Ԃ̃{�^����������Ă�����
				if ((nowButtonState >> i) & 1) 
				{            
					// ������J�E���^��0���傫�����
					if (buttonReleasingCount[i] > 0) 
					{
						// 0�ɖ߂�
						buttonReleasingCount[i] = 0;   
					}
					// ������J�E���^�𑝂₷
					buttonPressingCount[i]++;          
					buttonPressed[i] = true;
				}
				// i�Ԃ̃L�[��������Ă�����
				else 
				{                             
					// ������J�E���^��0���傫�����
					if (buttonPressingCount[i] > 0) 
					{ 
						// 0�ɖ߂�
						buttonPressingCount[i] = 0;    
					}
					// ������J�E���^�𑝂₷
					buttonReleasingCount[i]++;         
				}
			}
		}
	}
}