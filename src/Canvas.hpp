#pragma once
#include "DxLib.h"
#include "ICanvas.hpp"
#include <vector>

/*
	シーンの全GUIの更新・描画・入力関連処理を実行するクラス
*/

namespace Game
{

	namespace Object
	{

		namespace UI
		{
			class GUI;

			class Canvas : public ICanvas{
			protected:
				std::vector<GUI*> guiList;

			public:
				Canvas() noexcept;
				virtual ~Canvas() noexcept;
				virtual void Init() override;
				virtual void Update() override;
				virtual void Draw() override;
				virtual void Input(const Input::InputDeviceContainer&) override;
				void AddGUIObj(GUI& obj);
			};
		}
	}
}