#pragma once
#include "DxLib.h"
#include "GUI.hpp"

// �{�^����������Ă���Ԃ̃T�C�Y�k����
const int SIZEDIFF = 2;

/*
	Button�N���X
*/

namespace UI
{
	class Button : public GUI {
	private:

	public:
		virtual void Update() = 0;
		virtual void Draw() = 0;
	};
}
