#pragma once
#include "DxLib.h"
#include "Delegate.hpp"
#include "GameSymbol.hpp"
#include "GUI.hpp"
#include <vector>

// ボタンが押されている間のサイズ縮小幅
const int SIZEDIFF = 2;

namespace Game
{
	namespace Object
	{
		namespace UI
		{
			class Button : public GUI {
			private:

			public:
				virtual void Draw() = 0;
			};
		}
	}
}