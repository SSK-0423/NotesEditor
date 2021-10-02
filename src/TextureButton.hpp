#pragma once
#include "Button.hpp"

/*
	�e�N�X�`�������{�^���N���X
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
			Components::Texture* texture;
			Components::ICollider* collider;
			// �}�E�X�|�C���^�ƃ|���S���Ƃ̔���
			Collision::PointWithPolygon* collision;
			ButtonImpl* impl;
			void RunEventFunc();
			bool IsOnButton();
			void CheckClick();
		public:
			TextureButton(const char* filePath, Components::COLLIDERTYPE type);
			virtual ~TextureButton();
			void Update();
			void Draw();
		};
	}
}
