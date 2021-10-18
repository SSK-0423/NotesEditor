#pragma once
#include <vector>

/*
* ëΩäpå`ÉNÉâÉX
*/

using Color = unsigned int;

namespace Engine
{
	namespace PrimitiveObj
	{
		struct Point;

		class Polygon {
		private:
			std::vector<Point*> vertex;
			Color color;

		public:
			Polygon();
			Polygon(const Polygon& polygon);
			~Polygon();
			void Draw();
			void AddPoint(float x, float y);
			void ChangedColor(Color color);
			std::vector<Point> GetVertexList() const;
			void ResetVertex();
		};
	}
}