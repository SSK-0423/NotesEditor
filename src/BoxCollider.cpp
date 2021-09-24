#include "BoxCollider.hpp"
#include "Polygon.hpp"
#include "Point.hpp"
#include "Transform.hpp"
#include "Matrix.hpp"
#include "Rotator.hpp"

void Game::Component::Collider::BoxCollider::UpdatePolygon()
{
	// �|���S���̒��_������
	rect->ResetVertex();

	// ���S���W
	float posX, posY;
	// ����
	float width, height;
	// �p�x
	float angle;

	posX = parentTransform.GetPosition().GetPosX();
	posY = parentTransform.GetPosition().GetPosY();
	width = parentTransform.GetSize().GetWidth();
	height = parentTransform.GetSize().GetHeight();
	angle = parentTransform.GetRotation().GetAngle();

	// box�̒��_(���ォ�甽���v���)
	Object::Polygon::Point p1(posX - width / 2.f, posY - height / 2.f);
	Object::Polygon::Point p2(posX - width / 2.f, posY + height / 2.f);
	Object::Polygon::Point p3(posX + width / 2.f, posY + height / 2.f);
	Object::Polygon::Point p4(posX + width / 2.f, posY - height / 2.f);

	// ��]����
	// ��]�ړ����s���N���X
	Rotator rotator;

	// ��]��̈ʒu
	Math::Matrix rotated(2, 1);
	
	// ��]�Ώۂ̓_
	Math::Matrix colVec(2, 1);
	colVec.SetValue({ p1.x,p1.y });
	rotated = rotator.Rotate(colVec, angle);
	// ���_�Ƃ��ēo�^
	rect->AddPoint(rotated.myMatrix[0][0],rotated.myMatrix[1][0]);
	
	colVec.SetValue({ p2.x,p2.y });
	rotated = rotator.Rotate(colVec, angle);
	// ���_�Ƃ��ēo�^
	rect->AddPoint(rotated.myMatrix[0][0], rotated.myMatrix[1][0]);
	
	colVec.SetValue({ p3.x,p3.y });
	rotated = rotator.Rotate(colVec, angle);
	// ���_�Ƃ��ēo�^
	rect->AddPoint(rotated.myMatrix[0][0], rotated.myMatrix[1][0]);
	
	colVec.SetValue({ p4.x,p4.y });
	rotated = rotator.Rotate(colVec, angle);
	// ���_�Ƃ��ēo�^
	rect->AddPoint(rotated.myMatrix[0][0], rotated.myMatrix[1][0]);
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
