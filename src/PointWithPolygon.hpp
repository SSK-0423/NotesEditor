#pragma once
namespace Game
{
	namespace Object 
	{

		namespace Polygon 
		{
			class Point;
			class Polygon;
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
			public:
				bool Collision(const Object::Polygon::Point& point, const Collider::ICollider& collider);
			};
		}
	}
}