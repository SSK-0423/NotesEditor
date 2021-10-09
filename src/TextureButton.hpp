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
		class ButtonImpl;

		class TextureButton : public Button {
		private:
			// ボタンクリック時に呼び出される関数
			DelegateBase<void(void)>* eventFunc;
			
			Components::Texture* texture;
			Components::ICollider* collider;
			// マウスポインタとポリゴンとの判定
			Collision::PointWithPolygon* collision;
			bool isPressed;
			void RunEventFunc();
			bool IsOnButton();
		public:
			TextureButton(const char* filePath, Components::COLLIDERTYPE type);
			virtual ~TextureButton();
			void SetEventFunc(DelegateBase<void(void)>* func);
			void Update();
			void Draw();
			bool IsClick();
		};
	}
}
