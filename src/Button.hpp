#pragma once
#include "DxLib.h"
#include "GUI.hpp"
#include "Delegate.hpp"

const float CLICKEDSIZE = 0.98f;

/*
	ButtonƒNƒ‰ƒX
*/

namespace Engine
{
	namespace UI
	{
		class Button : public GUI {
		public:
			virtual void Update() = 0;
			virtual void Draw() = 0;
		};
	}
}
