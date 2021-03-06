#pragma once
#include "DxLib.h"
#include "ICanvas.hpp"
#include <vector>

/*
* シーンの全GUIの更新・描画・入力関連処理を実行するクラス
*/

namespace Engine
{
	namespace UI
	{
		class GUI;

		class Canvas : public ICanvas {
		protected:
			std::vector<GUI*> guiList;
		public:
			Canvas();
			virtual ~Canvas();
			virtual void Update() = 0;
			virtual void Draw() = 0;
			void AddGUIObj(GUI& obj);
		};
	}
}