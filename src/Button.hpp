#pragma once
#include "DxLib.h"
#include "GUI.hpp"
#include "Delegate.hpp"

const float CLICKEDSIZE = 0.98f;

/*
	Buttonクラス
*/

namespace Engine
{
	namespace UI
	{
		class Button : public GUI {
		protected:
			// ボタンクリック時に呼び出される関数
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
