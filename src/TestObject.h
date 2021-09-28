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
	Component::Transform transform;
	Component::Texture texture;
	Component::Collider::BoxCollider collider;
	Component::Collision::PointWithPolygon collision;

public:
	// ������
	// BoxCollider 1��ڂ�UpdatePolygon
	TestObject() : texture(transform,"image/ShortNotes03.png"), collider(transform)
	{
		float width, height;
		texture.GetTextureSize(width,height);
		transform.SetSize(width,height);
		transform.Scalling(10, 10);
		transform.SetPosition(500, 500);
	}
	// �X�V
	void Update()
	{
		if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_Q))
			transform.Rotate(1.f);
		if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_E))
			transform.Rotate(-1.f);
		if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_W))
			transform.Translate(0.f,-1.f);
		if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_S))
			transform.Translate(0.f,1.f);
		if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_A))
			transform.Translate(-1.f,0.f);
		if (Input::InputDeviceContainer::Instance().GetKeyboard().GetPressingCount(KEY_INPUT_D))
			transform.Translate(1.f,0.f);

		texture.Update();
		// vertex�̃��Z�b�g
		collider.Update();
		
		float x, y;
		x = Input::InputDeviceContainer::Instance().GetMouse().GetPosX();
		y = Input::InputDeviceContainer::Instance().GetMouse().GetPosY();

		PolygonObject::Point mousePos(x,y);
		if (collision.Collision(mousePos, collider))
			DrawFormatString(300, 0, GetColor(0, 255, 0), "��������");
	}
	// �`��
	void Draw() 
	{
		texture.Draw();
		collider.Draw();
	}
	// Transform�擾
	Component::Transform& GetTransform() 
	{
		return transform;
	}
};