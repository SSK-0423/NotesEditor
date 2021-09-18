#include "Keyboard.hpp"
#include "DxLib.h"

namespace Game {

	namespace Input {

		void Keyboard::UpdateCounter() const
		{
			// 現在のキーの入力状態を格納する
			char tmpKey[KEY_NUM];
			// 全てのキーの入力状態を得る
			GetHitKeyStateAll(tmpKey);

			for (int i = 0; i < 256; i++)
			{
				// i番のキーコードに対応するキーが押されていたら
				if (tmpKey[i] != 0)
				{
					// 加算
					keyPressingCount[i]++;
					keyPressed[i] = true;
				}
				// 押されていなければ
				else
				{
					// 0にする
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