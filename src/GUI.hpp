#pragma once
#include "GameSymbol.hpp"
#include "Transform.hpp"

namespace Engine
{
	namespace UI
	{
		class GUI {
		protected:
			Components::Transform transform;

		public:
			virtual void Draw() = 0;
			virtual void Update() = 0;
		};
	}

}