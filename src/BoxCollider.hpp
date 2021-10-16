#pragma once
#include "ICollider.hpp"

/*
* 四角形のヒットボックスクラス
*/

namespace Engine
{
	namespace PrimitiveObj
	{
		class Polygon;
	}
	namespace Components
	{
		class Transform;
		class Position;

		class BoxCollider : public ICollider {
		private:
			PrimitiveObj::Polygon* rectHitBox;
			const Transform& parentTransform;

			void UpdatePolygon();
		public:
			BoxCollider(const Transform& transform);
			~BoxCollider();
			void Update() override;
			void Draw() override;
			PrimitiveObj::Polygon GetPolygon() const;
			COLLIDERTYPE GetColliderType() const;
		};
	}
}