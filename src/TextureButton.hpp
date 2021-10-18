#pragma once
#include "Button.hpp"
#include "Delegate.hpp"

/*
	テクスチャを持つボタンクラス
*/

namespace Engine
{
	namespace Input
	{
		class InputDeviceContainer;
	}

	namespace Components
	{
		class Texture;

		enum class COLLIDERTYPE;
		class ICollider;
	}

	namespace Collision
	{
		class PointWithPolygon;
	}

	namespace UI
	{
		class TextureButton : public Button {
		private:
			// ボタンクリック時に呼び出される関数
			DelegateBase<void(void)>* eventFunc;
			Components::Texture* texture;
			void RunEventFunc();
			void OnClick() override;
			void Release() override;
			void Clicking() override;
			void NotOnButton() override;
		public:
			TextureButton(const char* filePath, Components::COLLIDERTYPE type);
			virtual ~TextureButton();
			void SetEventFunc(DelegateBase<void(void)>* func);
			void Update();
			void Draw();
		};
	}
}
