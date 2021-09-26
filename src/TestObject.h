#pragma once
#include "Transform.hpp"
#include "Texture.hpp"
#include "BoxCollider.hpp"
#include "PointWithPolygon.hpp"
#include "Point.hpp"
#include "Polygon.hpp"
#include "InputDeviceContainer.hpp"

class TestObject {
private:
	Game::Component::Transform transform;
	Game::Component::Texture texture;
	Game::Component::Collider::BoxCollider collider;
	Game::Component::Collision::PointWithPolygon collision;

public:
	// 初期化
	// BoxCollider 1回目のUpdatePolygon
	TestObject() : texture(transform,"image/ShortNotes03.png"), collider(transform)
	{
		float width, height;
		texture.GetTextureSize(width,height);
		transform.SetSize(width,height);
		transform.Scalling(10, 10);
		transform.SetPosition(500, 500);
	}
	// 更新
	void Update()
	{
		if (Game::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_Q))
			transform.Rotate(1.f);
		if (Game::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_E))
			transform.Rotate(-1.f);
		if (Game::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_W))
			transform.Translate(0.f,-1.f);
		if (Game::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_S))
			transform.Translate(0.f,1.f);
		if (Game::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_A))
			transform.Translate(-1.f,0.f);
		if (Game::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_D))
			transform.Translate(1.f,0.f);

		texture.Update();
		// vertexのリセット
		collider.Update();
		
		float x, y;
		x = Game::Input::InputDeviceContainer::Instance().GetMouse().GetPosX();
		y = Game::Input::InputDeviceContainer::Instance().GetMouse().GetPosY();

		Game::Object::Polygon::Point mousePos(x,y);
		if (collision.Collision(mousePos, collider))
			DrawFormatString(300, 0, GetColor(0, 255, 0), "当たった");
	}
	// 描画
	void Draw() 
	{
		texture.Draw();
		collider.Draw();
	}
	// Transform取得
	Game::Component::Transform& GetTransform() 
	{
		return transform;
	}
};