#pragma once
#include "Button.hpp"
#include <vector>

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
		class TextureButton;
		class MultiTextureButton : public Button {
		private:
			// ボタンクリック時に呼び出される関数
			DelegateBase<void(void)>* eventFunc;
			std::vector<Components::Texture*> texture;

			std::vector<TextureButton*> textureButtonList;
			Components::ICollider* collider;
			// マウスポインタとポリゴンとの判定
			Collision::PointWithPolygon* collision;
			// 現在表示中のボタン
			TextureButton* nowButton;
			int clickCount;

			void RunEventFunc();
		public:
			MultiTextureButton();
			MultiTextureButton(std::vector<const char*> filePath,Components::COLLIDERTYPE type);
			virtual ~MultiTextureButton();
			void AddTextureButton(TextureButton* button);
			void SetEventFunc(DelegateBase<void(void)>* func);
			void Update();
			void Draw();
		};
	}
}