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
		
		namespace Collider 
		{
			class ICollider;
		}
		namespace Collision 
		{
			class PointWithPolygon;
		}
	}

	namespace Object 
	{
		namespace UI 
		{
			class TextureButton {
			protected:
				Component::Transform* transform;
				Component::Texture* texture;
				Component::Collider::ICollider* collider;

			public:
				TextureButton(const char* filePath);
				virtual ~TextureButton();
				virtual void Draw() = 0;
				virtual void Input(const Game::Input::InputDeviceContainer& inputDeviceContainer) = 0;
			};
		}
	}
}