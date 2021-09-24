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
				static CrossingNumberAlgorithm collision;
			public:
				bool Collision(const Object::Polygon::Point& point, const Collider::ICollider& collider);
			};
		}
	}
}