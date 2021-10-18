#pragma once
#include "DxLib.h"
#include "GUI.hpp"
#include "Delegate.hpp"

/*
* ボタンの基底クラス
*/

namespace Engine
{
	namespace Components
	{
		enum class COLLIDERTYPE;
		class ICollider;
	}
	namespace Collision
	{
		class PointWithPolygon;
	}
	namespace UI
	{
		const float CLICKEDSIZE = 0.98f;

		class Button : public GUI {
		private:
			bool IsRelease();
			bool IsClicking();
			bool IsOnButton();
		protected:
			Components::ICollider* collider;
			Collision::PointWithPolygon* collision;
			bool isPressed;
			bool IsClicked();
			virtual void OnClick() = 0;
			virtual void Release() = 0;
			virtual void Clicking() = 0;
			virtual void NotOnButton() = 0;
		public:
			Button(Components::COLLIDERTYPE type);
			virtual ~Button();
			virtual void Update() = 0;
			virtual void Draw() = 0;
		};
	}
}
