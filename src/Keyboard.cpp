#include "Keyboard.hpp"
#include "DxLib.h"

namespace Game {

	namespace Input {

		void Keyboard::UpdateCounter() const
		{
			// ���݂̃L�[�̓��͏�Ԃ��i�[����
			char tmpKey[KEY_NUM];
			// �S�ẴL�[�̓��͏�Ԃ𓾂�
			GetHitKeyStateAll(tmpKey);

			for (int i = 0; i < 256; i++)
			{
				// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
				if (tmpKey[i] != 0)
				{
					// ���Z
					keyPressingCount[i]++;
					keyPressed[i] = true;
				}
				// ������Ă��Ȃ����
				else
				{
					// 0�ɂ���
					keyPressingCount[i] = 0;
				}
			}
		}

		void Keyboard::ReadInput() const
		{
			UpdateCounter();
		}

		int Keyboard::GetPressingCount(KeyCode keyCode) const
		{
			if (IsAvailableCode(keyCode))
				return keyPressingCount[keyCode];
			return -1;
		}

		int Keyboard::GetReleasingCount(KeyCode keyCode) const
		{
			if (IsAvailableCode(keyCode))
				return keyReleasingCount[keyCode];
			return -1;
		}

		bool Keyboard::IsPressKey(KeyCode keyCode) const
		{
			if (GetPressingCount(keyCode) == 1)
				return true;
			return false;
		}

		bool Keyboard::IsReleaseKey(KeyCode keyCode) const
		{
			if (GetPressingCount(keyCode) == 0 && keyPressed[keyCode])
			{
				keyPressed[keyCode] = false;
				return true;
			}
			return false;
		}
	}
}