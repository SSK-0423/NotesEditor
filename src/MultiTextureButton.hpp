#pragma once
#include "Button.hpp"

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
		class MultiTextureButton : public Button{
		private:
			Components::Texture* texture;
			Components::ICollider* collider;
			// マウスポインタとポリゴンとの判定
			Collision::PointWithPolygon* collision;
			void RunEventFunc();
		public:
			MultiTextureButton(const char* filePath, Components::COLLIDERTYPE type);
			virtual ~MultiTextureButton();
			void Update();
			void Draw();

		};
	}
}