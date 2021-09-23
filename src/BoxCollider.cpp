#include "BoxCollider.hpp"
#include "Polygon.hpp"
#include "Point.hpp"
#include "Transform.hpp"
#include "Matrix.hpp"
#include <cmath>

void Game::Component::Collider::BoxCollider::UpdatePolygon()
{
	// 親オブジェクトの位置
	Position parentPos = parentTransform.GetPosition();
	// 親オブジェクトのサイズ
	Size parentSize = parentTransform.GetSize();
	// 親オブジェクトの角度
	Rotation parentRot = parentTransform.GetRotation();

	// boxの頂点(左上から反時計回り)
	Object::Polygon::Point p1(parentPos.GetPosX() - parentSize.GetWidth() / 2.f, parentPos.GetPosY() - parentSize.GetHeight() / 2.f);
	Object::Polygon::Point p2(parentPos.GetPosX() - parentSize.GetWidth() / 2.f, parentPos.GetPosY() + parentSize.GetHeight() / 2.f);
	Object::Polygon::Point p3(parentPos.GetPosX() + parentSize.GetWidth() / 2.f, parentPos.GetPosY() + parentSize.GetHeight() / 2.f);
	Object::Polygon::Point p4(parentPos.GetPosX() + parentSize.GetWidth() / 2.f, parentPos.GetPosY() - parentSize.GetHeight() / 2.f);

	// 回転行列
	Math::Matrix rotMat(2, 2);
	rotMat.SetValue({

		cosf(parentRot.GetAngle()), -sinf(parentRot.GetAngle()),
		sinf(parentRot.GetAngle()), cosf(parentRot.GetAngle())
		});

	// 回転

}

Game::Component::Collider::BoxCollider::BoxCollider(const Component::Transform& transform) : parentTransform(transform)
{
	rect = new Object::Polygon::Polygon();
	UpdatePolygon();
}

Game::Component::Collider::BoxCollider::~BoxCollider()
{
	delete rect;
}

void Game::Component::Collider::BoxCollider::Draw()
{
	rect->Draw();
}

void Game::Component::Collider::BoxCollider::Update()
{
}

Game::Object::Polygon::Polygon Game::Component::Collider::BoxCollider::GetPolygon() const
{
	return *rect;
}

Game::Component::Collider::COLLIDERTYPE Game::Component::Collider::BoxCollider::GetColliderType() const
{
	return COLLIDERTYPE::COLLIDERTYPE_BOX;
}
