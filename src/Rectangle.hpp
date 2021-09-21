#pragma once
#include "Transform.hpp"

namespace Game
{
	namespace Object
	{
		namespace Polygon
		{
			class Rectangle {
			private:
				Component::Transform transform;

			public:
				Rectangle(const Component::Transform& transform) : transform(transform){}

			};
		}
	}
}