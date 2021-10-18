#pragma once
#include "Button.hpp"
#include <vector>

/*
* クリック回数によってテクスチャを切り替えるボタンクラス
*/

namespace Engine
{
	namespace Components
	{
		class Texture;
	}

	namespace UI
	{
		class MultiTextureButton : public Button {
		private:
			// ボタンクリック時に呼び出される関数
			DelegateBase<void(void)>* eventFunc;
			std::vector<Components::Texture*> textures;
			int nowTexIndex;
			int clickCount;
			void UpdateNowTexIndex();
			void RunEventFunc();
			void OnClick() override;
			void Release() override;
			void Clicking() override;
			void NotOnButton() override;
		public:
			MultiTextureButton(std::vector<const char*> filePath, Components::COLLIDERTYPE type);
			virtual ~MultiTextureButton();
			void SetEventFunc(DelegateBase<void(void)>* func);
			void Update() override;
			void Draw() override;
		};
	}
}