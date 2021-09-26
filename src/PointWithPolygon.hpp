#pragma once
#include "CrossingNumberAlgorithm.hpp"

namespace Game
{
	namespace Object 
	{

		namespace Polygon 
		{
			struct Point;
		}
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
				bool Collision(const Object::Polygon::Point& point, const Collider::ICollider& collider);
			};
		}
	}
}