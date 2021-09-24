#include "BoxCollider.hpp"
#include "Polygon.hpp"
#include "Point.hpp"
#include "Transform.hpp"
#include "Matrix.hpp"
#include "Rotator.hpp"

void Game::Component::Collider::BoxCollider::UpdatePolygon()
{
	// ポリゴンの頂点初期化
	rect->ResetVertex();

	// 中心座標
	float posX, posY;
	// 高さ
	float width, height;
	// 角度
	float angle;

	posX = parentTransform.GetPosition().GetPosX();
	posY = parentTransform.GetPosition().GetPosY();
	width = parentTransform.GetSize().GetWidth();
	height = parentTransform.GetSize().GetHeight();
	angle = parentTransform.GetRotation().GetAngle();

	// boxの頂点(左上から反時計回り)
	Object::Polygon::Point p1(posX - width / 2.f, posY - height / 2.f);
	Object::Polygon::Point p2(posX - width / 2.f, posY + height / 2.f);
	Object::Polygon::Point p3(posX + width / 2.f, posY + height / 2.f);
	Object::Polygon::Point p4(posX + width / 2.f, posY - height / 2.f);

	// 回転処理
	// 回転移動を行うクラス
	Rotator rotator;

	// 回転後の位置
	Math::Matrix rotated(2, 1);
	
	// 回転対象の点
	Math::Matrix colVec(2, 1);
	colVec.SetValue({ p1.x,p1.y });
	rotated = rotator.Rotate(colVec, angle);
	// 頂点として登録
	rect->AddPoint(rotated.myMatrix[0][0],rotated.myMatrix[1][0]);
	
	colVec.SetValue({ p2.x,p2.y });
	rotated = rotator.Rotate(colVec, angle);
	// 頂点として登録
	rect->AddPoint(rotated.myMatrix[0][0], rotated.myMatrix[1][0]);
	
	colVec.SetValue({ p3.x,p3.y });
	rotated = rotator.Rotate(colVec, angle);
	// 頂点として登録
	rect->AddPoint(rotated.myMatrix[0][0], rotated.myMatrix[1][0]);
	
	colVec.SetValue({ p4.x,p4.y });
	rotated = rotator.Rotate(colVec, angle);
	// 頂点として登録
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
