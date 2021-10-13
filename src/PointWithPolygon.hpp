#pragma once
#include "CrossingNumberAlgorithm.hpp"


namespace Engine
{
	namespace PrimitiveObj
	{
		struct Point;
	}

	namespace Components
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
			bool Collision(float x, float y, const Components::ICollider& collider);
		};
	}
}