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
		class MultiTextureButton : public Button{
		private:
			std::vector<Components::Texture*> texture;
			Components::ICollider* collider;
			// マウスポインタとポリゴンとの判定
			Collision::PointWithPolygon* collision;
			void RunEventFunc();
		public:
			MultiTextureButton(const char* filePath, Components::COLLIDERTYPE type);
			virtual ~MultiTextureButton();
			void AddTexture(const char* filePath);
			void Update();
			void Draw();

		};
	}
}