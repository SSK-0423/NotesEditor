#pragma once
#include "DxLib.h"
#include "Delegate.hpp"
#include "GameSymbol.hpp"
#include "GUI.hpp"
#include <vector>

// �{�^����������Ă���Ԃ̃T�C�Y�k����
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