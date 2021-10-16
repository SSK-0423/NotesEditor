#include "BoxCollider.hpp"
#include "Polygon.hpp"
#include "Point.hpp"
#include "Transform.hpp"
#include "Matrix.hpp"
#include "Rotator.hpp"

void Engine::Components::BoxCollider::UpdatePolygon()
{
	// タスク
	// 頂点初期化
	// 親の座標・サイズ・角度取得
	// 原点を中心とする点作成
	// 回転処理
	// 並行移動
	// 変換後の頂点をポリゴンの頂点として登録
	
	// ポリゴンの頂点初期化
	rectHitBox->ResetVertex();

	// 中心座標
	float posX, posY;
	// 高さ
	float width, height;
	// 角度
	float angle;

	posX = parentTransform.GetPosition().x;
	posY = parentTransform.GetPosition().y;
	width = parentTransform.GetSize().width * parentTransform.GetSize().scaleWidth;
	height = parentTransform.GetSize().height * parentTransform.GetSize().scaleHeight;
	angle = parentTransform.GetRotation().angle;

	PrimitiveObj::Point p1(-width / 2.f, -height / 2.f);
	PrimitiveObj::Point p2(-width / 2.f, height / 2.f);
	PrimitiveObj::Point p3(width / 2.f, height / 2.f);
	PrimitiveObj::Point p4(width / 2.f, -height / 2.f);

	// 回転処理
	// 回転移動を行うクラス
	Rotator rotator;

	// 回転後の位置
	Math::Matrix rotatedP1(2, 1);
	Math::Matrix rotatedP2(2, 1);
	Math::Matrix rotatedP3(2, 1);
	Math::Matrix rotatedP4(2, 1);

	// 回転対象の点
	Math::Matrix colVec(2, 1);
	colVec.SetValue({ p1.x,p1.y });
	rotatedP1 = rotator.Rotate(colVec, angle);
	colVec.SetValue({ p2.x,p2.y });
	rotatedP2 = rotator.Rotate(colVec, angle);
	colVec.SetValue({ p3.x,p3.y });
	rotatedP3 = rotator.Rotate(colVec, angle);
	colVec.SetValue({ p4.x,p4.y });
	rotatedP4 = rotator.Rotate(colVec, angle);

	// 平行移動
	// TODO:アフィン変換の実装した方がよいかも
	Math::Matrix translator(2, 1);
	translator.SetValue({posX, posY});
	rotatedP1 += translator;
	rotatedP2 += translator;
	rotatedP3 += translator;
	rotatedP4 += translator;

	// 頂点として登録
	rectHitBox->AddPoint(rotatedP1.myMatrix[0][0], rotatedP1.myMatrix[1][0]);
	rectHitBox->AddPoint(rotatedP2.myMatrix[0][0], rotatedP2.myMatrix[1][0]);
	rectHitBox->AddPoint(rotatedP3.myMatrix[0][0], rotatedP3.myMatrix[1][0]);
	rectHitBox->AddPoint(rotatedP4.myMatrix[0][0], rotatedP4.myMatrix[1][0]);
}

Engine::Components::BoxCollider::BoxCollider(const Components::Transform& transform) : parentTransform(transform)
{
	rectHitBox = new PrimitiveObj::Polygon();
	UpdatePolygon();
}

Engine::Components::BoxCollider::~BoxCollider()
{
	delete rectHitBox;
}

void Engine::Components::BoxCollider::Draw()
{
	rectHitBox->Draw();
}

void Engine::Components::BoxCollider::Update()
{
	UpdatePolygon();
}

Engine::PrimitiveObj::Polygon Engine::Components::BoxCollider::GetPolygon() const
{
	return *rectHitBox;
}

Engine::Components::COLLIDERTYPE Engine::Components::BoxCollider::GetColliderType() const
{
	return COLLIDERTYPE::COLLIDERTYPE_BOX;
}
