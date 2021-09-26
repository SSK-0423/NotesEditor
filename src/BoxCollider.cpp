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

	Object::Polygon::Point p1(-width / 2.f, -height / 2.f);
	Object::Polygon::Point p2(-width / 2.f, height / 2.f);
	Object::Polygon::Point p3(width / 2.f, height / 2.f);
	Object::Polygon::Point p4(width / 2.f, -height / 2.f);

	// ��]����
	// ��]�ړ����s���N���X
	Rotator rotator;

	// ��]��̈ʒu
	Math::Matrix rotatedP1(2, 1);
	Math::Matrix rotatedP2(2, 1);
	Math::Matrix rotatedP3(2, 1);
	Math::Matrix rotatedP4(2, 1);

	// ��]�Ώۂ̓_
	Math::Matrix colVec(2, 1);
	colVec.SetValue({ p1.x,p1.y });
	rotatedP1 = rotator.Rotate(colVec, angle);
	colVec.SetValue({ p2.x,p2.y });
	rotatedP2 = rotator.Rotate(colVec, angle);
	colVec.SetValue({ p3.x,p3.y });
	rotatedP3 = rotator.Rotate(colVec, angle);
	colVec.SetValue({ p4.x,p4.y });
	rotatedP4 = rotator.Rotate(colVec, angle);

	// ���s�ړ�
	// TODO:�A�t�B���ϊ��̎������������悢����
	Math::Matrix translator(2, 1);
	translator.SetValue({posX, posY});
	rotatedP1 += translator;
	rotatedP2 += translator;
	rotatedP3 += translator;
	rotatedP4 += translator;

	// ���_�Ƃ��ēo�^
	rect->AddPoint(rotatedP1.myMatrix[0][0], rotatedP1.myMatrix[1][0]);
	// ���_�Ƃ��ēo�^
	rect->AddPoint(rotatedP2.myMatrix[0][0], rotatedP2.myMatrix[1][0]);
	// ���_�Ƃ��ēo�^
	rect->AddPoint(rotatedP3.myMatrix[0][0], rotatedP3.myMatrix[1][0]);
	// ���_�Ƃ��ēo�^
	rect->AddPoint(rotatedP4.myMatrix[0][0], rotatedP4.myMatrix[1][0]);
}

Game::Component::Collider::BoxCollider::BoxCollider(const Component::Transform& transform) : parentTransform(transform)
{
	rect = new Object::Polygon::Polygon();
	UpdatePolygon();
}

Game::Component::Collider::BoxCollider::~BoxCollider()
{
	//delete rect;
}

void Game::Component::Collider::BoxCollider::Draw()
{
	rect->Draw();
}

void Game::Component::Collider::BoxCollider::Update()
{
	UpdatePolygon();
}

Game::Object::Polygon::Polygon Game::Component::Collider::BoxCollider::GetPolygon() const
{
	return *rect;
}

Game::Component::Collider::COLLIDERTYPE Game::Component::Collider::BoxCollider::GetColliderType() const
{
	return COLLIDERTYPE::COLLIDERTYPE_BOX;
}
