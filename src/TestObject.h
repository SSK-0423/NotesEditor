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
	Engine::Components::Transform transform;
	Engine::Components::Texture texture;
	Engine::Components::BoxCollider collider;
	Engine::Collision::PointWithPolygon collision;

public:
	// ������
	// BoxCollider 1��ڂ�UpdatePolygon
	TestObject() : texture(transform, "image/ShortNotes03.png"), collider(transform)
	{
		float width, height;
		texture.GetTextureSize(width, height);
		transform.SetSize(width, height);
		transform.Scalling(10, 10);
		transform.SetPosition(500, 500);
	}
	// �X�V
	void Update()
	{
		if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_Q))
			transform.Rotate(1.f);
		if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_E))
			transform.Rotate(-1.f);
		if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_W))
			transform.Translate(0.f, -1.f);
		if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_S))
			transform.Translate(0.f, 1.f);
		if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_A))
			transform.Translate(-1.f, 0.f);
		if (Engine::Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_D))
			transform.Translate(1.f, 0.f);

		texture.Update();
		// vertex�̃��Z�b�g
		collider.Update();

		float x, y;
		x = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosX();
		y = Engine::Input::InputDeviceContainer::Instance().GetMouse().GetPosY();

		if (collision.Collision(x, y, collider))
			DrawFormatString(300, 0, GetColor(0, 255, 0), "��������");
	}
	// �`��
	void Draw()
	{
		texture.Draw();
		collider.Draw();
	}
	// Transform�擾
	Engine::Components::Transform& GetTransform()
	{
		return transform;
	}
};