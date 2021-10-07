#pragma once
#include "Transform.hpp"
#include "Texture.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "Polygon.hpp"
#include "InputDeviceContainer.hpp"
#include "GameObject.hpp"

class TestObject : public Engine::GameObject {
private:
	Engine::Components::Texture texture;
	Engine::Components::BoxCollider collider;
	Engine::Collision::PointWithPolygon collision;

	void MyDrawBox(Engine::Components::Position pos) 
	{
		Engine::Components::Size size = transform->GetSize();
		DrawBox(pos.x - size.width, pos.y - size.height, pos.x + size.width, pos.y + size.height, GetColor(0, 255, 0), true);
	}

public:
	// 初期化
	TestObject() : texture(*transform,*screenPos,"image/ShortNotes03.png"), collider(*transform), GameObject()
	{
		float width, height;
		texture.GetTextureSize(width, height);
		transform->SetSize(width, height);
		transform->Scaling(1, 1);
		transform->SetPosition(500, 500);
		screenPos->SetPosition(transform->GetPosition().x, transform->GetPosition().y);
	}
	// 更新
	void Update()
	{
		if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_Q))
			transform->Rotate(1.f);
		if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_E))
			transform->Rotate(-1.f);
		if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_W))
			transform->Translate(0.f, -1.f);
		if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_S))
			transform->Translate(0.f, 1.f);
		if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_A))
			transform->Translate(-1.f, 0.f);
		if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_D))
			transform->Translate(1.f, 0.f);

		texture.Update();
		// vertexのリセット
		collider.Update();

		float x, y;
		x = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosX();
		y = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosY();

		if (collision.Collision(x, y, collider))
			DrawFormatString(300, 0, GetColor(0, 255, 0), "当たった");

	}
	// 描画
	void Draw()
	{
		texture.Draw();
		collider.Draw();
		//MyDrawBox(*screenPos);
		DrawFormatString(700, 400, GetColor(0, 255, 0), "screenPosX:%f,screenPosY:%f", screenPos->x, screenPos->y);
	}
	// Transform取得
	Engine::Components::Transform& GetTransform()
	{
		return *transform;
	}
};