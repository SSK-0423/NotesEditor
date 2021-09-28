#pragma once
#include "DxLib.h"
#include "GUI.hpp"

// ボタンが押されている間のサイズ縮小幅
const int SIZEDIFF = 2;

/*
	Buttonクラス
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
