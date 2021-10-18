#include "Button.hpp"
#include "InputDeviceContainer.hpp"
#include "Transform.hpp"
#include "ICollider.hpp"
#include "ColliderCreator.hpp"
#include "PointWithPolygon.hpp"

Engine::UI::Button::Button(Components::COLLIDERTYPE type) : isPressed(false)
{
	transform = new Components::Transform();
	collision = new Collision::PointWithPolygon();
	collider = Engine::ColliderCreator::Instance().CreateCollider(type, *transform);
	collider->Update();
}

Engine::UI::Button::~Button()
{
	delete collider;
	delete collision;
}

bool Engine::UI::Button::IsClicked()
{
	if (IsOnButton())
	{
		if (IsClicking())
		{
			Clicking(); return false;
		}
		if (IsRelease())
		{
			Release(); return true;
		}
	}
	NotOnButton();
	return false;
}

bool Engine::UI::Button::IsRelease()
{
	bool isReleaseLeftClick = Engine::Input::InputDeviceContainer::Instance().GetMouse().IsReleaseKey(Engine::Input::Mouse::LEFT_CLICK);
	return isReleaseLeftClick && isPressed;
}

bool Engine::UI::Button::IsClicking()
{
	return Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPressingCount(Engine::Input::Mouse::LEFT_CLICK);
}

bool Engine::UI::Button::IsOnButton()
{
	// マウスポインタの座標取得
	float x, y;
	x = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosX();
	y = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosY();

	// マウスポインタがボタンの上にあるか
	return collision->Collision(x, y, *collider);
}
