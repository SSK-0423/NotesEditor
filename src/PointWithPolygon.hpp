#pragma once
#include "CrossingNumberAlgorithm.hpp"

/*
* 点と多角形の内外判定機能を提供するラッパークラス
*/
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
			static CrossingNumberAlgorithm collision;
		public:
			PointWithPolygon();
			bool Collision(float x, float y, const Components::ICollider& collider);
		};
	}
}