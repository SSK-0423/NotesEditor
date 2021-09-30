#pragma once
#include "DxLib.h"
#include "GUI.hpp"
#include "Delegate.hpp"

const float CLICKEDSIZE = 0.98f;

/*
	Button�N���X
*/

namespace Engine
{
	namespace UI
	{
		class Button : public GUI {
		protected:
			// �{�^���N���b�N���ɌĂяo�����֐�
			DelegateBase<void(void)>* eventFunc;

		public:
			virtual void Update() = 0;
			virtual void Draw() = 0;
			void SetEventFunc(DelegateBase<void(void)>* func)
			{
				eventFunc = func;
			}
		};
	}
}
