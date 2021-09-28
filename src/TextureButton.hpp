#pragma once
#include "Button.hpp"

/*
	テクスチャを持つボタンクラス
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
		// ヒットボックス
		Component::Collider::ICollider* collider;
		// マウスポインタとポリゴンとの判定
		Component::Collision::PointWithPolygon* collision;
	public:
		TextureButton(const char* filePath, Component::Collider::COLLIDERTYPE type);
		virtual ~TextureButton();
		void Update();
		void Draw();
	};
}
