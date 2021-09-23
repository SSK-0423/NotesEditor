#pragma once
#include "ICollider.hpp"

/*
	四角形の当たり判定のためのオブジェクト
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
				// 当たり判定となるポリゴン
				//Object::Polygon::Rectangle* rect;
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