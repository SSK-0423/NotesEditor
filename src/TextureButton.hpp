#pragma once
#include "Button.hpp"

/*
	�e�N�X�`�������{�^���N���X
*/

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
		enum class COLLIDERTYPE;
		class ICollider;
	}
	namespace Collision
	{
		class PointWithPolygon;
	}
}

namespace UI
{
	class TextureButton : Button {
	protected:
		Component::Transform* transform;
		Component::Texture* texture;
		// �q�b�g�{�b�N�X
		Component::Collider::ICollider* collider;
		// �}�E�X�|�C���^�ƃ|���S���Ƃ̔���
		Component::Collision::PointWithPolygon* collision;
	public:
		TextureButton(const char* filePath, Component::Collider::COLLIDERTYPE type);
		virtual ~TextureButton();
		void Update();
		void Draw();
	};
}
