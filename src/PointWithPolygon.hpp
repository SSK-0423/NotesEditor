#pragma once
#include "CrossingNumberAlgorithm.hpp"

namespace PolygonObject
{
	struct Point;
}

namespace Component
{
	namespace Collider
	{
		class ICollider;
	}
	namespace Collision
	{
		class PointWithPolygon {
		private:
			CrossingNumberAlgorithm collision;
		public:
			PointWithPolygon();
			bool Collision(const PolygonObject::Point& point, const Collider::ICollider& collider);
		};
	}
}