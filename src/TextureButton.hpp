#pragma once

/*
	テクスチャを持つボタンクラス
*/

namespace Game 
{
	namespace Input 
	{
		class InputDeviceContainer;
	}
	namespace Component 
	{
		class Transform;
		class Texture;
		class Collider;
	}

	namespace Object 
	{
		namespace UI 
		{
			class TextureButton {
			private:
				Component::Transform* transform;
				Component::Texture* texture;
				Component::Collider* collider;
			public:
				TextureButton(const char* filePath);
				virtual ~TextureButton();
				virtual void Draw() = 0;
				virtual void Input(const Game::Input::InputDeviceContainer& inputDeviceContainer) = 0;
			};
		}
	}
}