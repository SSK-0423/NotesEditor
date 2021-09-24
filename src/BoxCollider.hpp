#pragma once
#include "ICollider.hpp"

/*
	四角形のヒットボックス
*/

namespace Game
{
	namespace Object
	{
		namespace Polygon
		{
			class Polygon;
		}
	}

	namespace Component
	{
		class Transform;

		namespace Collider
		{
			class BoxCollider : public ICollider{
			private:
				// 当たり判定枠となるポリゴン
				Object::Polygon::Polygon* rect;
				// 親のTransform
				const Component::Transform& parentTransform;

				void UpdatePolygon();
			public:
				BoxCollider(const Component::Transform& transform);
				~BoxCollider();
				void Draw();
				void Update();
				Object::Polygon::Polygon GetPolygon() const;
				COLLIDERTYPE GetColliderType() const;
			};
		}
	}
}

/*
	Polygonの機能
	・ポリゴンの生成・描画

	BoxColliderの機能
	・四角形のヒットボックスを親オブジェクトにつける機能(責任)
	・ヒットボックスの描画
	・四角形のポリゴンを生成するという機能は含まれている

	判定で用いるのは四角形のポリゴン
	ポリゴンを継承したRectangleを作る理由
	・BoxColliderが四角形のポリゴンになるように、点の調整などを行っている
	・他で四角形のポリゴンを作ろうとしたとき、毎回Pointオブジェクトを生成して、
	AddPointで代入する必要がある。→追加点が多かったり少なかったりする可能性がある。
	また、PointとPolygonをincludeする必要性が出てくる。→includeが多くなる
	単純にめんどくさい
	当たり判定で必要なのは、GetVertexList()のみ
	そもそもこの当たり判定以外でわざわざ四角形ポリゴン使う機会ある？

*/