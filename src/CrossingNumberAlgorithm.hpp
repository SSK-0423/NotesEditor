#pragma once

/*
	点と多角形の内外判定を実際に行うクラス
*/

namespace Engine
{
	namespace PrimitiveObj
	{
		class Polygon;
		struct Point;
	}
	namespace Collision
	{
		class CrossingNumberAlgorithm {
		private:
		public:
			bool Collision(const PrimitiveObj::Point& point, const PrimitiveObj::Polygon& polygon);
		};
	}
}
